
#include <effect_overdrive.h>

#include <limits> //for int32_t limits

//=========================== STATIC MEMBER VARIABLES =======================

/** TODO: icon */
const Effect_Icon_t Effect_Overdrive::icon = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x01, 0x06, 0x00, 0x00, 0x03, 
    0x03, 0x00, 0x00, 0x06, 0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 
    0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 
    0x01, 0x00, 0x00, 0x04, 0xE1, 0x87, 0x3F, 0x04, 0x71, 0x8E, 0x79, 0x04, 
    0x39, 0x8C, 0x61, 0x04, 0x19, 0x9C, 0x61, 0x04, 0x19, 0x98, 0x61, 0x04, 
    0x19, 0x98, 0x61, 0x04, 0x19, 0x9C, 0x61, 0x04, 0x39, 0x8C, 0x61, 0x04, 
    0xF1, 0x8F, 0x7F, 0x04, 0xE1, 0x87, 0x1F, 0x04, 0x01, 0x00, 0x00, 0x04, 
    0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 
    0x01, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00, 0x03, 
    0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//=========================== OVERRIDDEN PUBLIC FUNCTIONS =========================

//save the name and effect theme color during initialization
Effect_Overdrive::Effect_Overdrive():
    name("Overdrive"),
    theme_color(RGB_LED::RED),
    gain("Gain", 0.01, 1, 100, 1),
    effect_edit(to_return_page, leds, encs) //initialize our edit page implementation
{
    //set the header text and theme color for the effects edit menu
    effect_edit.set_display_text("Edit Gain");
    effect_edit.set_LED_color(theme_color);

    //set the parameters to edit/render in the edit menu
    effect_edit.set_render_parmeter(&gain, 2);
}

//copy constructor that invokes the default constructor above
Effect_Overdrive::Effect_Overdrive(const Effect_Overdrive& other):
    Effect_Overdrive()
{}

//################# CORE OF THE EFFECT ###################

void Effect_Overdrive::audio_update(const Audio_Block_t& block_in, Audio_Block_t& block_out) {
    //synchronize our parameter for reading/rendering
    gain.synchronize();

    //if volume frequency has been adjusted --> recompute the fixed-point value
    if(gain.get() != prev_gain) {
        /**
         * Convert the floating point volume to a Q1.31 fixed point representation
         * A gain of `1` should correspond to the maximum value of an int32_t
         *      \--> can use std::numeric_limits<int32_t>::max()
         * A gain of `0` should correspond to 0
         * Should be a relatively simple one-line conversion
         */        
        gain_fp = (int32_t)(std::numeric_limits<int32_t>::max()) * gain.get();
        
        //update the previous volume value such that we only run this `if` statement
        //if the volume knob was adjusted
        prev_gain = gain.get();
    }

    //actually run our effect, having computed our constants
    for(size_t i = 0; i < block_in.size(); i++) {
        //create references to our memory elements for the particular sample
        const auto& sample_in = block_in[i];
        auto& sample_out = block_out[i];
        
        /**
         * INTERPOLATION STAGE --> INCREASE THE EFFECTIVE SAMPLE RATE OF THE SIGNAL
         *  - Run the signal through an interpolating CIC filter
         *  - this starts with a couple comb stages
         *  - then runs through a zero-stuffer
         *  - and finally runs through an integrator
        */
        //comb filter stage of the interpolator
        int32_t interp_combed_sample = (int32_t)sample_in;
        for(auto& interp_comb_memory : inter_comb_memories) {
            int32_t interp_comb_output = interp_combed_sample - interp_comb_memory; //run the comb filter computation
            interp_comb_memory = interp_combed_sample; //save the previous sample input
            
            //the output of this stage of the comb filter will be the input of the next comb stage
            //as such we'll update the value of `combed_sample` with the value of `comb_output`
            interp_combed_sample = interp_comb_output;
        }
        
        //zero stuffer stage of the interpolator --> baked into the high sample rate section
        //also define a variable for the decimator stage --> picks out a single sample after the integrator
        int32_t high_rate_sample_in = interp_combed_sample;
        int32_t high_sample_rate_out;
        for(size_t j = 0; j < RATE_INCREASE_MULT; j++) {
            //======================= ENTERING HIGH SAMPLE RATE SECTION =======================
            //integrator stage of the interpolator
            int32_t interp_int_sample = high_rate_sample_in;
            for(auto& interp_integrator_value : interp_integrator_values) {
                interp_integrator_value += interp_int_sample; //integrate the input sample stream

                //the output of this stage of the integrator will be the input of the next integrator stage
                //as such we'll update the vaue of `interp_int_sample` with the value of `integrator_output`
                interp_int_sample = interp_integrator_value;
            }

            //a part of the zero-stuffer from the previous stage --> next sample coming in will be zero
            high_rate_sample_in = 0;

            //final rescaling of our sample value due to gain of our interpolating filter
            int32_t high_rate_sample_filt = interp_int_sample >> ((CIC_FILTER_ORDER-1)*RATE_INCREASE_LOG2);
            //############# RUN THE DISTORTION EFFECT #################
            int32_t distorted_sample = diode_clip_od(high_rate_sample_filt, gain_fp);
            //################ end DISTORTION EFFECT ##################

            /**
             * DECIMATION STAGE --> INCREASE THE EFFECTIVE SAMPLE RATE OF THE SIGNAL
             *  - Run the signal through an decimating CIC filter
             *  - this starts with a couple integrator stages
             *  - then runs through a decimator
             *  - and finally runs through a couple comb filters
            */
            //start the decimation process with the integrators
            int32_t decim_int_sample = distorted_sample;
            for(auto& decim_integrator_value : decim_integrator_values) {
                decim_integrator_value += decim_int_sample; //integrate current sample

                //the output of this stage of the integrator will be the input of the next integrator stage
                //as such we'll update the vaue of `int_sample` with the value of `integrator_output`
                decim_int_sample = decim_integrator_value;
            }

            //set the low-rate sample output to the most recent integrator output
            //has the effect of outputting the single latest sample after decimating by the appropriate ratio
            high_sample_rate_out = decim_int_sample; 

            //========================= end HIGH SAMPLE RATE SECTION ========================
        }
        //decimator stage happens basically just by leaving this `for` loop
        //decimated sample will be stored in `high_sample_rate_out`

        //comb filter of the decimator
        int32_t decim_combed_sample = high_sample_rate_out;
        for(auto& decim_comb_memory : decim_comb_memories) {
            int32_t decim_comb_output = decim_combed_sample - decim_comb_memory; //run the comb filter computation
            decim_comb_memory = decim_combed_sample; //save the previous sample input
            
            //the output of this stage of the comb filter will be the input of the next comb stage
            //as such we'll update the value of `combed_sample` with the value of `comb_output`
            decim_combed_sample = decim_comb_output;
        }

        //scale the output of the decimator appropriately
        //and write it to the sample output
        sample_out = (int16_t)(decim_combed_sample >> (CIC_FILTER_ORDER*RATE_INCREASE_LOG2));
    }
}

//################# end CORE OF THE EFFECT ###################

//function we call to actually instantiate a new effect on the heap
//return a unique pointer to automatically manage this heap memory
std::unique_ptr<Effect_Interface> Effect_Overdrive::clone() {
    return std::make_unique<Effect_Overdrive>(*new Effect_Overdrive(*this));
}

std::string Effect_Overdrive::get_name() { return name; }
Effect_Icon_t Effect_Overdrive::get_icon() { return icon; }
RGB_LED::COLOR Effect_Overdrive::get_theme_color() { return theme_color; }
Effect_Parameter* Effect_Overdrive::get_quick_edit_param() { return effect_edit.get_quick_edit_param(); }

//=========================== PRIVATE + OVERRIDDEN FUNCTIONS =========================

//diode overdrive approximation from 
//not using gain just yet
//https://baltic-lab.com/2023/08/dsp-diode-clipping-algorithm-for-overdrive-and-distortion-effects/
int32_t Effect_Overdrive::diode_clip_od(int32_t sample, int32_t gain_q131) {
    
    //easy way to make this symmetric 
    int32_t sample_sign = sample >= 0 ? 1 : -1;
    sample = abs(sample);
    
    if(sample < 10922)
        return sample_sign * sample * 2;
    else if(sample < 21845) {
        //-3x^2 + 4x - 1/3
        return sample_sign * ((-10921) + 4*sample - 3 * sample * sample / 32768);
    }
    else
        return sample_sign * 32767;
}

//override our entry function --> call our default implementation
//configuration of render resources
void Effect_Overdrive::impl_on_entry() {
    //run the entry function in our edit menu implementation
    effect_edit.configure_render_resources();
}

//override our exit function --> call our default implementation
//release all the render resources
void Effect_Overdrive::impl_on_exit() {
    //run the exit function in our edit menu implementation 
    effect_edit.release_render_resources();
}


void Effect_Overdrive::draw() {
    //call the render function of our edit menu implemenation
    //pass it the global graphics handle
    effect_edit.render(graphics_handle);
}
