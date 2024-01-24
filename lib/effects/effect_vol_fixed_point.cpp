
#include <effect_vol_fixed_point.h>

#include <limits> //for int32_t limits

//=========================== STATIC MEMBER VARIABLES =======================

const Effect_Icon_t Effect_Vol_Fixed_Point::icon = {
    0xF8, 0xFF, 0xFF, 0x01, 0x06, 0x00, 0x00, 0x03, 0x02, 0x00, 0x00, 0x02, 
    0x01, 0x00, 0x00, 0x04, 0x01, 0x60, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 
    0x01, 0x70, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 0x01, 0xFC, 0x00, 0x04, 
    0x01, 0xEC, 0x03, 0x04, 0x01, 0x86, 0x03, 0x04, 0x01, 0x06, 0x03, 0x04, 
    0x01, 0x07, 0x06, 0x04, 0x01, 0x06, 0x03, 0x04, 0x01, 0x06, 0x03, 0x04, 
    0x01, 0xDE, 0x03, 0x04, 0x01, 0xF8, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 
    0x01, 0x70, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 
    0x01, 0x70, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 
    0x01, 0x70, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 
    0x01, 0x70, 0x00, 0x04, 0x01, 0x70, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 
    0xE1, 0x01, 0x00, 0x04, 0x21, 0x00, 0x00, 0x04, 0x21, 0xAA, 0x1B, 0x04, 
    0xE1, 0xAA, 0x28, 0x04, 0x21, 0x92, 0x29, 0x04, 0x21, 0xAA, 0x28, 0x04, 
    0x21, 0xAA, 0x1B, 0x04, 0x01, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x02, 
    0x06, 0x00, 0x00, 0x03, 0xFC, 0xFF, 0xFF, 0x00
};

//=========================== OVERRIDDEN PUBLIC FUNCTIONS =========================

//save the name and effect theme color during initialization
Effect_Vol_Fixed_Point::Effect_Vol_Fixed_Point():
    name("Fixed Pt. Vol"),
    theme_color(RGB_LED::GREEN),
    volume("Volume", 0.01, 1, 100, 1),
    effect_edit(to_return_page, leds, encs) //initialize our edit page implementation
{
    //set the header text and theme color for the effects edit menu
    effect_edit.set_display_text("Edit Volume");
    effect_edit.set_LED_color(theme_color);

    //set the parameters to edit/render in the edit menu
    effect_edit.set_render_parmeter(&volume, 2);
}

//copy constructor that invokes the default constructor above
Effect_Vol_Fixed_Point::Effect_Vol_Fixed_Point(const Effect_Vol_Fixed_Point& other):
    Effect_Vol_Fixed_Point()
{}

//################# CORE OF THE EFFECT ###################

void Effect_Vol_Fixed_Point::audio_update(const Audio_Block_t& block_in, Audio_Block_t& block_out) {
    //synchronize our parameter for reading/rendering
    volume.synchronize();

    //if volume frequency has been adjusted --> recompute the fixed-point value
    if(volume.get() != prev_volume) {
        /**
         * Aonvert the floating point volume to a Q1.31 fixed point representation
         * A volume of `1` should correspond to the maximum value of an int32_t
         *      \--> can use std::numeric_limits<int32_t>::max()
         * A volume of `0` should correspond to 0
         * Should be a relatively simple one-line conversion
         */        
        vol_fp = /* TODO your code*/ 0;
        
        //update the previous volume value such that we only run this `if` statement
        //if the volume knob was adjusted
        prev_volume = /* TODO your code */ 0;
    }

    //actually run our effect, having computed our constants
    for(size_t i = 0; i < block_in.size(); i++) {
        //create references to our memory elements for the particular sample
        const auto& sample_in = block_in[i];
        auto& sample_out = block_out[i];

        /**
         * Actually do the volume adjustment now
         * We need to multiply our input sample by our Q1.31 fixed point representation of our volume
         * To do this, we'll leverage a special DSP instruction `signed_multiply_32x16b()`
         *      \--> look at the function declaration and definition to see the actual math it does
         * 
         * NOTE: does this function do everything we need? Or do we have to apply another shift to our data?   
        */
        int32_t vol_adj_sample = /*TODO: your code*/ 0;
        /* TODO any other relevant code for `vol_adj_sample` */

        /**
         * our sample is currently a 32-bit value
         * as such, we need to get rid of some bits, such that the sample fits in 16 bits
         * Do we take the upper 16 bits or the lower 16 bits? Something in-between?
         * You'll potentially have to use bitwise operations
         *      \--> bitwise left shift: `>>`
         *      \--> bitwise and: `&`
         * Try searching for what these mean on the internet, then ask for help if they aren't making sense
        */
        
        //output our volume-adjusted sample
        sample_out = /*TODO: your code*/ sample_in;
    }
}

//################# end CORE OF THE EFFECT ###################

//function we call to actually instantiate a new effect on the heap
//return a unique pointer to automatically manage this heap memory
std::unique_ptr<Effect_Interface> Effect_Vol_Fixed_Point::clone() {
    return std::make_unique<Effect_Vol_Fixed_Point>(*new Effect_Vol_Fixed_Point(*this));
}

std::string Effect_Vol_Fixed_Point::get_name() { return name; }
Effect_Icon_t Effect_Vol_Fixed_Point::get_icon() { return icon; }
RGB_LED::COLOR Effect_Vol_Fixed_Point::get_theme_color() { return theme_color; }
Effect_Parameter* Effect_Vol_Fixed_Point::get_quick_edit_param() { return effect_edit.get_quick_edit_param(); }

//=========================== OVERRIDDEN PRIVATE FUNCTIONS =========================

//override our entry function --> call our default implementation
//configuration of render resources
void Effect_Vol_Fixed_Point::impl_on_entry() {
    //run the entry function in our edit menu implementation
    effect_edit.configure_render_resources();
}

//override our exit function --> call our default implementation
//release all the render resources
void Effect_Vol_Fixed_Point::impl_on_exit() {
    //run the exit function in our edit menu implementation 
    effect_edit.release_render_resources();
}


void Effect_Vol_Fixed_Point::draw() {
    //call the render function of our edit menu implemenation
    //pass it the global graphics handle
    effect_edit.render(graphics_handle);
}

