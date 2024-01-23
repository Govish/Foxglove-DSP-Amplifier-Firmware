#pragma once

/* 
 * Effect parameter with numerical floating point value
 * Linear spacing in between each of the values
 * Adjusted by the encoder
 * Effectively emulates a linear-taper potentiometer
 * 
 * By Ishaan Gov December 2023 
 */

#include <string>

#include <effect_param.h>
#include <encoder.h>

class Effect_Parameter_Num_Lin : public Effect_Parameter {
public:
    //constructor, takes in min, max, and step values of the parameter (step --> how much a single encoder tick should change the value)
    //TODO: sanity check inputs maybe, not sure if `static_assert` could catch some of these?
    Effect_Parameter_Num_Lin(const std::string _label, const float _param_min, const float _param_max, const float _param_step, const float param_default);

    //should basically configure the max value of the encoder and its steps position
    //shouldn't attach any callbacks --> that's what the owner program should do
    //also save this encoder for when we compute our parameter
    void attach_configure_enc(Rotary_Encoder& enc) override;

    //render the parameter
    //will show up as a label of the parameter at the bottom
    //a bar chart roughly visualizing the value w.r.t. the entire range
    //and the actual numerical value above it
    void draw(uint32_t x_offset, uint32_t y_offset, U8G2& graphics_handle) override;

    //synchronize will compute the actual effect value from the encoder position
    //and save it to a member variable; parameter value can be retrieved with `get`
    void synchronize() override;
    
    //actually get the parameter value
    //make sure to call `synchronize()` before reading this
    float get();

private:
    //store the min, max and encoder max counts
    //don't really need to save `step` as that's effectively encoded into `encoder_max_count`
    const float param_min;
    const float param_max;
    const uint32_t encoder_max_count;

    //actual parameter value computed from the encoder value
    uint32_t last_encoder_count = 0;    //don't recalculate if encoder value didn't change
                                        //also useful to initialize encoder value 
    float param_value;
};