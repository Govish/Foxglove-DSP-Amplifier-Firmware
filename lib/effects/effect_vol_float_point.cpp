
#include <effect_vol_float_point.h>

#include <limits> //for int32_t limits

//=========================== STATIC MEMBER VARIABLES =======================

const Effect_Icon_t Effect_Vol_Float_Point::icon = {
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
    0xE1, 0x01, 0x00, 0x04, 0x21, 0x00, 0x00, 0x04, 0x21, 0x72, 0x73, 0x04, 
    0xE1, 0x52, 0x25, 0x04, 0x21, 0x52, 0x27, 0x04, 0x21, 0x52, 0x25, 0x04, 
    0x21, 0x76, 0x25, 0x04, 0x01, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x02, 
    0x06, 0x00, 0x00, 0x03, 0xFC, 0xFF, 0xFF, 0x00
};

//=========================== OVERRIDDEN PUBLIC FUNCTIONS =========================

//save the name and effect theme color during initialization
Effect_Vol_Float_Point::Effect_Vol_Float_Point():
    name("Float Pt. Vol"),
    theme_color(RGB_LED::CYAN),
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
Effect_Vol_Float_Point::Effect_Vol_Float_Point(const Effect_Vol_Float_Point& other):
    Effect_Vol_Float_Point()
{}

//################# CORE OF THE EFFECT ###################

void Effect_Vol_Float_Point::audio_update(const Audio_Block_t& block_in, Audio_Block_t& block_out) {
    //synchronize our parameter for reading/rendering
    volume.synchronize();

    //actually run our effect, having computed our constants
    for(size_t i = 0; i < block_in.size(); i++) {
        //create references to our memory elements for the particular sample
        const auto& sample_in = block_in[i];
        auto& sample_out = block_out[i];

        /**
         * Actually do the volume adjustment here
         * some notes to help you:
         *  - you should (for clarity) explicitly cast `sample_in` to a `float` when doing these operations
         *      --> search on the internet to see how to cast to a float in C++; if you're having trouble, find me
         *  - get the value of the parameter by using the `get()` function
         */
        float vol_adjust_sample = /*TODO: your code here*/ (float)sample_in * volume.get();
        
        /**
         * Output our volume adjusted sample here
         * Need to convert back into an `int16_t`
         *      \--> should be able to do this just by re-casting
        */
        sample_out = /*TODO your code here*/ (int16_t)vol_adjust_sample;
    }
}

//################# end CORE OF THE EFFECT ###################

//function we call to actually instantiate a new effect on the heap
//return a unique pointer to automatically manage this heap memory
std::unique_ptr<Effect_Interface> Effect_Vol_Float_Point::clone() {
    return std::make_unique<Effect_Vol_Float_Point>(*new Effect_Vol_Float_Point(*this));
}

std::string Effect_Vol_Float_Point::get_name() { return name; }
Effect_Icon_t Effect_Vol_Float_Point::get_icon() { return icon; }
RGB_LED::COLOR Effect_Vol_Float_Point::get_theme_color() { return theme_color; }
Effect_Parameter* Effect_Vol_Float_Point::get_quick_edit_param() { return effect_edit.get_quick_edit_param(); }

//=========================== OVERRIDDEN PRIVATE FUNCTIONS =========================

//override our entry function --> call our default implementation
//configuration of render resources
void Effect_Vol_Float_Point::impl_on_entry() {
    //run the entry function in our edit menu implementation
    effect_edit.configure_render_resources();
}

//override our exit function --> call our default implementation
//release all the render resources
void Effect_Vol_Float_Point::impl_on_exit() {
    //run the exit function in our edit menu implementation 
    effect_edit.release_render_resources();
}


void Effect_Vol_Float_Point::draw() {
    //call the render function of our edit menu implemenation
    //pass it the global graphics handle
    effect_edit.render(graphics_handle);
}

