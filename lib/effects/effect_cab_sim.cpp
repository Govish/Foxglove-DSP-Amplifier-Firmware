#include <effect_cab_sim.h>

//=========================== STATIC MEMBER VARIABLES - CAB IMPULSE RESPONSES =======================

const Effect_Cab_Sim::Impulse_Response_t Effect_Cab_Sim::FENDER_TWIN_REVERB = {
	118861,		248308,		225188,		125849,		72302,		42370,		-5074,		
	-73272,		-149370,	-169454,	-102290,		-26979,		4499,		3465,		
	-8571,		7160,		36711,		22835,		-4578,		-4697,		-1566,		
	18870,		69174,		77943,		22802,		-16384,		-16041,		-15392,		
	-19066,		-29075,		-44713,		-35480,		-6875,		13997,		24312,		
	11459,		-12448,		3793,		43082,		37671,		4642,		-19235,		
	-46221,		-56845,		-39556,		-27918,		-28971,		-17894,		11187,		
	24830,		5098,		-24844,		-39781,		-40704,		-30985,		-4458,		
	19647,		24478,		29068,		35993,		19252,		-21256,		-47171,		
	-39538,		-16213,		499,		5206,		3560,		-2645,		-14832,		
	-25507,		-28773,		-32762,		-37555,		-32288,		-20198,		-12748,		
	-5885,		3336,		9466,		11629,		6676,		-3193,		-9767,		
	-16519,		-23699,		-23721,		-23301,		-29561,		-32605,		-30916,		
	-30993,		-26833,		-15817,		-5344,		3527,		12114,		16690,		
	16388,		12366,		4270,		-2959,		-5026,		-9358,		-20197,		
	-29531,		-30691,		-23191,		-11277,		-368,		8940,		14868,		
	10671,		-2459,		-14010,		-21076,		-26166,		-24031,		-13730,		
	-3830,		1900,		4242,		4424,		3213,		404,		-2569,		
	-1646,		1954,		936,		-5364,		-11573,		-15769,		-17708,		
	-16030,		-10272,		-2648,		4446,		9490,		10038,		4758,		
	-2023,		-4314,		-1994,		1893,		4286,		1754,		-3537,		
	-5683,		-4859,		-1900,		4693,		11897,		16290,		18705,		
	18699,		14877,		9499,		4473,		-307,		-3713,		-5702,		
	-7118,		-7501,		-6948,		-6710,		-6782,		-6666,		-7324,		
	-7223,		-3145,		3266,		9025,		14197,		18280,		20342,		
	20409,		17302,		10241,		1906,		-4019,		-6414,		-6463,		
	-5959,		-5475,		-4212,		-1746,		1452,		4658,		7612,		
	10670,		14057,		16799,		16943,		13735,		9037,		6019,		
	5438,		5086,		3300,		-18,		-3749,		-5775,		-5241,		
	-2815,		1135,		5640,		8522,		8734,		6922,		4746,		
	5061,		8368,		11366,		11973,		10719,		8570,		6468,		
	4352,		1295,		-2045,		-3688,		-3321,		-1823,		38,		
	1161,		1430,		1673,		2002,		2719,		4639,		7692,		
	11087,		13823,		14414,		12947,		11420,		10328,		8879,		
	7027,		4706,		2248,		751,		413,		884,		2111,		
	3595,		5209,		7228,		8710,		9008,		8708,		7581,		
	5375,		3103,		1354,		105,		
};


//=========================== STATIC MEMBER VARIABLES - ICON =======================

const Effect_Icon_t Effect_Cab_Sim::icon = {
    0xFC, 0xFF, 0xFF, 0x01, 0x06, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x06, 
    0x01, 0x00, 0x00, 0x04, 0xF9, 0xFF, 0xFF, 0x04, 0x09, 0x00, 0x80, 0x04, 
    0xE9, 0xEE, 0xB6, 0x04, 0xA9, 0xAA, 0xB6, 0x04, 0xE9, 0xEE, 0x80, 0x04, 
    0x09, 0x40, 0x80, 0x04, 0x09, 0x88, 0x80, 0x04, 0x09, 0x04, 0x81, 0x04, 
    0x09, 0x72, 0x82, 0x04, 0x09, 0x88, 0x80, 0x04, 0x09, 0x88, 0x80, 0x04, 
    0x09, 0x88, 0x80, 0x04, 0x09, 0x72, 0x82, 0x04, 0x09, 0x04, 0x81, 0x04, 
    0x09, 0x88, 0x80, 0x04, 0x09, 0x00, 0x80, 0x04, 0xF9, 0xFF, 0xFF, 0x04, 
    0xE1, 0x00, 0x38, 0x04, 0xF9, 0xFF, 0xFF, 0x04, 0x09, 0x00, 0x80, 0x04, 
    0x09, 0x00, 0x80, 0x04, 0x09, 0x88, 0x80, 0x04, 0x09, 0x04, 0x81, 0x04, 
    0x09, 0x72, 0x82, 0x04, 0x09, 0x88, 0x80, 0x04, 0x09, 0x88, 0x80, 0x04, 
    0x09, 0x88, 0x80, 0x04, 0x09, 0x72, 0x82, 0x04, 0x09, 0x04, 0x81, 0x04, 
    0x09, 0x88, 0x80, 0x04, 0x09, 0x00, 0x80, 0x04, 0x09, 0x00, 0x80, 0x04, 
    0xF9, 0xFF, 0xFF, 0x04, 0x01, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x02, 
    0x06, 0x00, 0x00, 0x03, 0xFC, 0xFF, 0xFF, 0x00
};

//=========================== OVERRIDDEN PUBLIC FUNCTIONS =========================

//save the name, effect theme color, and impulse kernel
Effect_Cab_Sim::Effect_Cab_Sim(RGB_LED::COLOR _theme_color, std::string _name, const Impulse_Response_t& _impulse_kernel):
    name(_name),
    theme_color(_theme_color),
    impulse_kernel(_impulse_kernel)
{}

//copy constructor just invokes the default constructor with the same parameters as the original
Effect_Cab_Sim::Effect_Cab_Sim(const Effect_Cab_Sim& other):
    name(other.name),
    theme_color(other.theme_color),
    impulse_kernel(other.impulse_kernel)
{}

//function we call to actually instantiate a new effect on the heap
//return a unique pointer 
std::unique_ptr<Effect_Interface> Effect_Cab_Sim::clone() {
    return std::make_unique<Effect_Cab_Sim>(*new Effect_Cab_Sim(*this));
}

std::string Effect_Cab_Sim::get_name() { return name; }
Effect_Icon_t Effect_Cab_Sim::get_icon() { return icon; }
RGB_LED::COLOR Effect_Cab_Sim::get_theme_color() { return theme_color; }

//======================================= CORE OF THE EFFECT --> CONVOLUTIONAL REVERB ==============================

/**
 * TODO: this
*/
void Effect_Cab_Sim::audio_update(const Audio_Block_t& block_in, Audio_Block_t& block_out) {
    //go through all of the samples in the block 
    for(size_t block_sample_index = 0; block_sample_index < block_in.size(); block_sample_index++) {
        //reference the samples at the particular index
        const auto& sample_in = block_in[block_sample_index];
        auto& sample_out = block_out[block_sample_index];

        //drop the particular input sample into our circular sample buffer
        sample_memory[sample_memory_head] = sample_in;

        //actually run the convolution
        //use 32x16 multiply-accumulate (MAC) DSP instructions to make this happen
        int32_t sum = 0;
        size_t sample_buffer_ptr = sample_memory_head; //most recent sample
        for(const auto& tap : impulse_kernel) {
            const auto& sample = sample_memory[sample_buffer_ptr]; //grab the FIR tap and the corresponding sample
            sum = signed_multiply_accumulate_32x16b(sum, tap, (uint32_t)sample); //run the MAC using DSP instructions

            //tap will move "forward in time"
            //sample index will move "backward in time"
            //roll-over the sample buffer pointer as necessary 
            if(sample_buffer_ptr == 0) sample_buffer_ptr = sample_memory.size() - 1;
            else sample_buffer_ptr--;
        }
        
        //since FIR taps are Q1.31, we need to left shift our sum by 1
        //and additionaly compensate for any sorta coefficient scaling done
        //  \--> the latter is done to ensure that at no point our FIR sum exceeds the 32-bit accumulator
        sum = sum << 1;
        sum = sum * impulse_kernel.size();

        //we'll do some additional processing here to ensure that the output sample safely clips to min/max limits
	//instead of doing some funky rollover
	if(sum > ((int32_t)std::numeric_limits<int16_t>::max()) << SUM_SHIFT_AMT) //upward going clip
		sample_out = std::numeric_limits<int16_t>::max();
	else if (sum < ((int32_t)std::numeric_limits<int16_t>::min()) << SUM_SHIFT_AMT) //upward going clip
		sample_out = std::numeric_limits<int16_t>::min();
        else 
		sample_out = (int16_t)(sum >> SUM_SHIFT_AMT);

        //not forgetting to increment the circular buffer for the sample memory; roll over to zero as necessary
        sample_memory_head++;
        if(sample_memory_head >= sample_memory.size()) sample_memory_head = 0;
    }
}
//=========================== OVERRIDDEN PRIVATE FUNCTIONS =========================

//override the entry function, schedule a transition after one second
void Effect_Cab_Sim::impl_on_entry() {
    //schedule a transition out of the current page
    //since we don't have any parameters to attach
    done_editing_sched.schedule_oneshot_ms(to_return_page, 2000);
}

void Effect_Cab_Sim::draw() {
    //display a message on the screen
    static const std::array<std::string, 4> no_param_msg = {
        name,
        "======",
        "This Effect Has No",
        "Editable Parameters"
    };

    //compute the coordinates of the text such that it's center aligned
    static std::array<u8g2_uint_t, no_param_msg.size()> x_coords;
    static std::array<u8g2_uint_t, no_param_msg.size()> y_coords;
    for(size_t i = 0; i < no_param_msg.size(); i++) 
        //center the text
        x_coords[i] = ( graphics_handle.getWidth() - 
                        graphics_handle.getStrWidth(no_param_msg[i].c_str())) >> 1;
    
    //compute the y coordinates of each line of text too
    static const auto msg_height = (graphics_handle.getMaxCharHeight() + 2) * no_param_msg.size() - 2;
    y_coords[0] = (graphics_handle.getDisplayHeight() - msg_height)/2;
    for(size_t i = 1; i < y_coords.size(); i++)
        y_coords[i] = y_coords[i-1] + graphics_handle.getMaxCharHeight() + 2;

    //render the text on the screen
    graphics_handle.clearBuffer();
    graphics_handle.setFontPosTop(); //using top left of text as reference
    for(size_t i = 0; i < no_param_msg.size(); i++) 
        graphics_handle.drawStr(x_coords[i], y_coords[i], no_param_msg[i].c_str());
    graphics_handle.setFontPosBaseline(); //restore font reference to default
    graphics_handle.sendBuffer();
}