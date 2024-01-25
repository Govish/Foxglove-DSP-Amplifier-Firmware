#pragma once

/**
 * Effect that implements convolutional reverb to simulate an amplifier cabinet
 * No adjustable parameters; basically only matters whether effect is present in the audio path or not
 * 
 * By Ishaan Gov Jan 2024
*/

#include <array> //for impulse response
#include <effect_interface.h> //implements interface specified here
#include <scheduler.h> //to stage a transition
#include <dspinst.h> //for DSP instructions for convolution

class Effect_Cab_Sim : public Effect_Interface {
public:
    //###################################################################################
    
    //typedef'ing the particular size of the impulse respones (read: number of samples)
    typedef std::array<int32_t, 256> Impulse_Response_t;

    //###################################################################################

    //default constructor -- just call the base class constructor
    Effect_Cab_Sim(RGB_LED::COLOR _theme_color, std::string _name, const Impulse_Response_t& _impulse_kernel);

    //copy constructor--invokes the default constructor with the same parameters as the template
    Effect_Cab_Sim(const Effect_Cab_Sim& other);
    
    //implement the clone function to produce instances of this effect that are copies of the original
    //need to override base class so we produce copies of the derived class instead
    std::unique_ptr<Effect_Interface> clone() override;

    //provide implementations for the following functions:
    void audio_update(const Audio_Block_t& block_in, Audio_Block_t& block_out) override;
    std::string get_name() override;
    Effect_Icon_t get_icon() override;
    RGB_LED::COLOR get_theme_color() override;

    //################################################################################
    //Add different impulse response kernels here--gives us some options for different cabinets 

    static const Impulse_Response_t FENDER_TWIN_REVERB;

    //################################################################################

private:
    //define implementation for `draw()` in the effect edit context
    //will just print "no params to adjust" centered on display
    void draw() override;

    //override the entry function, schedule a transition after one second
    void impl_on_entry() override;
    
    //have an icon for the effect, will be constant for all instances
    static const Effect_Icon_t icon;

    //have a particular name for our instance
    const std::string name; 

    //also have a theme color that can be configured instance-by-instance
    const RGB_LED::COLOR theme_color;    

    //reference to the impulse reponse kernel for the convolutional reverb
    const Impulse_Response_t& impulse_kernel;
    
    //additionally have some sample memory for the convolution to happen
    //will use the 32x16 MAC dsp instruction to do the convolution
    //will use a circular buffer, so we need to remember where the buffer `head` is
    static constexpr Impulse_Response_t dummy_imp = {0}; //need this just to get the size of the impulse response
    std::array<Audio_Sample_t, dummy_imp.size()> sample_memory = {0}; //zero initialize
    size_t sample_memory_head = 0; //point to the beginning of the sample memory

    //use this to schedule a transition back to the previous page
    Scheduler done_editing_sched;
};