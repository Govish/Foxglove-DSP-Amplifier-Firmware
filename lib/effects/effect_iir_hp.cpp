
#include <effect_iir_hp.h>

#include <limits> //for int32_t limits

//=========================== STATIC MEMBER VARIABLES =======================

const Effect_Icon_t Effect_IIR_HP::icon = {
    0xFC, 0xFF, 0xFF, 0x01, 0x06, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x06, 
    0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 0x11, 0x00, 0x00, 0x04, 
    0x11, 0x00, 0x00, 0x04, 0x11, 0x00, 0x00, 0x04, 0x11, 0xC0, 0xFF, 0x04, 
    0x11, 0xE0, 0x00, 0x04, 0x11, 0x70, 0x00, 0x04, 0x11, 0xB8, 0x00, 0x04, 
    0x11, 0x1C, 0x00, 0x04, 0x11, 0x0E, 0x00, 0x04, 0x11, 0x87, 0x00, 0x04, 
    0x91, 0x03, 0x00, 0x04, 0xD1, 0x81, 0x00, 0x04, 0xD1, 0x00, 0x00, 0x04, 
    0x11, 0x00, 0x00, 0x04, 0x11, 0x80, 0x00, 0x04, 0xF9, 0xFF, 0xFF, 0x04, 
    0x11, 0x00, 0x00, 0x04, 0x11, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 
    0x01, 0x00, 0x00, 0x04, 0x71, 0xE6, 0x0F, 0x04, 0x71, 0xE6, 0x1F, 0x04, 
    0x71, 0x66, 0x38, 0x04, 0x71, 0x66, 0x38, 0x04, 0x71, 0xE6, 0x1F, 0x04, 
    0x71, 0xE6, 0x0F, 0x04, 0x71, 0x66, 0x0E, 0x04, 0x71, 0x66, 0x1C, 0x04, 
    0x71, 0x66, 0x18, 0x04, 0x71, 0x66, 0x38, 0x04, 0x01, 0x00, 0x00, 0x04, 
    0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x02, 
    0x06, 0x00, 0x00, 0x03, 0xFC, 0xFF, 0xFF, 0x00
};

//=========================== OVERRIDDEN PUBLIC FUNCTIONS =========================

//save the name and effect theme color during initialization
Effect_IIR_HP::Effect_IIR_HP():
    name("IIR High-pass"),
    theme_color(RGB_LED::PURPLE),
    f_cutoff("Cutoff", 100, 5000, 60, 1000),
    effect_edit(to_return_page, leds, encs) //initialize our edit page implementation
{
    //set the header text and theme color for the effects edit menu
    effect_edit.set_display_text("Edit Cutoff Freq");
    effect_edit.set_LED_color(theme_color);

    //set the parameters to edit/render in the edit menu
    effect_edit.set_render_parmeter(&f_cutoff, 2);
}

//copy constructor that invokes the default constructor above
Effect_IIR_HP::Effect_IIR_HP(const Effect_IIR_HP& other):
    Effect_IIR_HP()
{}

//################# CORE OF THE EFFECT ###################

void Effect_IIR_HP::audio_update(const Audio_Block_t& block_in, Audio_Block_t& block_out) {
    //synchronize our parameter for reading/rendering
    f_cutoff.synchronize();

    //if cutoff frequency has been adjusted --> recompute some filter constants
    if(f_cutoff.get() != sync_cutoff_freq) {
        //compute the uint16_t decay parameter from the desired time constant
        //do this by first computing $e^-1$ --> corresponds to decay after a single time constant
        //from here, figure out the amount of incremental decay for this level of decay to happen after the specified time constant
        //then convert that number into a Q0.32 fixed-point format
        
        //compute `tau` of the lowpass filter in units of samples
        //inverse of the radian frequency gives us seconds; multiplying by sampling frequency gives us Hz
        float filter_time_constant = ((float)App_Constants::AUDIO_SAMPLE_RATE_HZ)/(f_cutoff.get() * RADSEC_PER_HZ);

        //compute the n-th root of the time constant to figure out how much decay per sample
        //essentially after `filter_time_constant` multiplies, we need to have a signal level corresponding to exp(-1)
        float decay_per_sample = pow(EXP_m1, 1.0/filter_time_constant); 
        
        //conversion to Q1.31 fixed point --> lets us use some DSP instructions when leveraging this effect
        //the way numerical constants are computed means gain of the system should never exceed 1
        feedback_factor = (int32_t)(std::numeric_limits<int32_t>::max() + 1.0) * decay_per_sample;
        feedforward_factor = (int32_t)((uint32_t)(1<<31) - feedback_factor);

        //save our new cutoff frequency
        sync_cutoff_freq = f_cutoff.get();
    }

    //actually run our effect, having computed our constants
    for(size_t i = 0; i < block_in.size(); i++) {
        //create references to our memory elements for the particular sample
        const auto& sample_in = block_in[i];
        auto& sample_out = block_out[i];

        //run the IIR filter
        //multiply the input sample by the feed-forward term
        //multiply the previous output by the feed-back term
        //sum these two together and save the new output 
        //use DSP instructions to make this process slightly faster
        //need additional left shift for Q1.31 format for the IIR coeffficients
        int32_t lp_feed_forward = signed_multiply_32x16b(feedforward_factor, (uint32_t)(sample_in));
        int32_t lp_new_output = multiply_accumulate_32x32_rshift32_rounded(lp_feed_forward, feedback_factor, lp_last_output) << 1;

        //assign last sample with the full resolution, and the output with truncated resolution
        lp_last_output = lp_new_output;
        sample_out = sample_in - (int16_t)(lp_new_output >> 16);
    }
}

//################# end CORE OF THE EFFECT ###################

//function we call to actually instantiate a new effect on the heap
//return a unique pointer to automatically manage this heap memory
std::unique_ptr<Effect_Interface> Effect_IIR_HP::clone() {
    return std::make_unique<Effect_IIR_HP>(*new Effect_IIR_HP(*this));
}

std::string Effect_IIR_HP::get_name() { return name; }
Effect_Icon_t Effect_IIR_HP::get_icon() { return icon; }
RGB_LED::COLOR Effect_IIR_HP::get_theme_color() { return theme_color; }
Effect_Parameter* Effect_IIR_HP::get_quick_edit_param() { return effect_edit.get_quick_edit_param(); }

//=========================== OVERRIDDEN PRIVATE FUNCTIONS =========================

//override our entry function --> call our default implementation
//configuration of render resources
void Effect_IIR_HP::impl_on_entry() {
    //run the entry function in our edit menu implementation
    effect_edit.configure_render_resources();
}

//override our exit function --> call our default implementation
//release all the render resources
void Effect_IIR_HP::impl_on_exit() {
    //run the exit function in our edit menu implementation 
    effect_edit.release_render_resources();
}


void Effect_IIR_HP::draw() {
    //call the render function of our edit menu implemenation
    //pass it the global graphics handle
    effect_edit.render(graphics_handle);
}

