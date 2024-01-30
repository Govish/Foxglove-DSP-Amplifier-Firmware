#pragma once

/**
 * Effect that implements a basic overdrive effect
 * 
 * A core part of this effect is the CIC filter needed for multi-rate processing and anti-aliasing
 * This is heavily advised by this fantastic article by Rick Lyons found here:
 * https://www.dsprelated.com/showarticle/1337.php
 * 
 * By Ishaan Gov Jan 2024
*/

#include <array>
#include <string>

#include <effect_interface.h> //implements interface specified here
#include <effect_edit/default_effect_edit_impl.h> //effect menu implementation
#include <effect_param_num_lin.h>   //linear control of distortion stage gain
#include <dspinst.h> //for DSP and SIMD instruction for speed and such

class Effect_Overdrive : public Effect_Interface {
public:
    //default constructor -- just call the base class constructor
    Effect_Overdrive();

    //need to have a non-default copy constructor--> need to freshly instantiate the `effect_edit` param
    //we'll invoke the default constructor using the theme color and name from the `other`
    Effect_Overdrive(const Effect_Overdrive& other);
    
    //implement the clone function to produce instances of this effect that are copies of the original
    //need to override base class so we produce copies of the derived class instead
    std::unique_ptr<Effect_Interface> clone() override;

    //provide implementations for the following functions:
    void audio_update(const Audio_Block_t& block_in, Audio_Block_t& block_out) override;
    std::string get_name() override;
    Effect_Icon_t get_icon() override;
    RGB_LED::COLOR get_theme_color() override;
    Effect_Parameter* get_quick_edit_param() override; 

private:
    //define the implementations for the effect edit menu
    //will use the `default_effect_edit_implementation` to handle editing and rendering our parameter menu
    void draw() override;
    void impl_on_entry() override;
    void impl_on_exit() override;

    //funciton we'll be using to actually do the non-linear overdrive effect
    int32_t diode_clip_od(int32_t sample, int32_t gain_q131);
    
    //have an icon for the effect, will be constant for all instances
    static const Effect_Icon_t icon;

    //have a particular name and theme for our instance
    const std::string name; 
    const RGB_LED::COLOR theme_color;    

    //have a parameter that sets the desired volume
    Effect_Parameter_Num_Lin gain;
    float prev_gain = 0;
    int32_t gain_fp = 0; //Q1.31 representation of our gain value

    //stuff relevant to the CIC filter
    static constexpr size_t RATE_INCREASE_LOG2 = 3; //increase sample rate by 8x if this number is 3
    static constexpr size_t RATE_INCREASE_MULT = 1 << RATE_INCREASE_LOG2;
    static constexpr size_t CIC_FILTER_ORDER = 3; //this many CIC filter stages
    //memory elements for the integrator and comb filtering stages
    //hard-coding the CIC filter to use a 2-sample comb stage --> equates to a single memory element
    std::array<int32_t, CIC_FILTER_ORDER> interp_integrator_values = {0};
    std::array<int32_t, CIC_FILTER_ORDER> inter_comb_memories = {0};
    std::array<int32_t, CIC_FILTER_ORDER> decim_integrator_values = {0};
    std::array<int32_t, CIC_FILTER_ORDER> decim_comb_memories = {0};

    //place to hold some interpolated samples for each low-rate sample input
    std::array<int32_t, RATE_INCREASE_MULT> interp_samples = {0};

    //have an instance of our `default_effect_edit_impl`
    //to actually handle our edit menu 
    Default_Effect_Edit_Impl effect_edit;
};  