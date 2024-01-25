#include <effect_cab_sim.h>

//=========================== STATIC MEMBER VARIABLES - CAB IMPULSE RESPONSES =======================

const Effect_Cab_Sim::Impulse_Response_t Effect_Cab_Sim::FENDER_TWIN_REVERB = {
    340064945,		710418961,		644275502,		360066408,		206871111,		121235001,		-14504678,		
    -209619092,		-427339282,		-484803051,		-292646584,		-77183305,		12878266,		9919142,		
    -24518246,		20491304,		105036492,		65336680,		-13091268,		-13433538,		-4473695,		
    53993722,		197914446,		223005181,		65245669,		-46864842,		-45884998,		-44029517,		
    -54541530,		-83177701,		-127918363,		-101501910,		-19662100,		40052340,		69565085,		
    32792100,		-35607161,		10858867,		123265912,		107784221,		13288773,		-55023345,		
    -132232056,		-162628187,		-113165749,		-79868399,		-82880644,		-51191217,		32010961,		
    71044867,		14590072,		-71074407,		-113811192,		-116450406,		-88646191,		-12751540,		
    56212926,		70036423,		83166947,		102982277,		55085594,		-60809177,		-134952100,		
    -113116889,		-46383808,		1429080,		14896431,		10188190,		-7564417,		-42431327,		
    -72974913,		-82317102,		-93731037,		-107443560,		-92376176,		-57785846,		-36474147,		
    -16837117,		9543220,		27083165,		33269922,		19100770,		-9136117,		-27943786,		
    -47262620,		-67803930,		-67866827,		-66667035,		-84578113,		-93285134,		-88455160,		
    -88675033,		-76772433,		-45256224,		-15293759,		10086477,		34653770,		47747428,		
    46881697,		35376460,		12212285,		-8469713,		-14383581,		-26776055,		-57789139,		
    -84492608,		-87811614,		-66354725,		-32269489,		-1057199,		25572833,		42533318,		
    30525274,		-7041423,		-40089595,		-60303198,		-74866583,		-68759905,		-39288336,		
    -10965011,		5428966,		12129557,		12651882,		9186279,		1148758,		-7357019,		
    -4716190,		5582651,		2670642,		-15352603,		-33117677,		-45122161,		-50669987,		
    -45870579,		-29395864,		-7584464,		12711679,		27143909,		28711671,		13604689,		
    -5794059,		-12351201,		-5713677,		5408828,		12255746,		5010626,		-10126529,		
    -16266022,		-13907968,		-5444482,		13419983,		34028919,		46599806,		53509375,		
    53491783,		42555920,		27169488,		12789805,		-885867,		-10630262,		-16319925,		
    -20372424,		-21466274,		-19884269,		-19204664,		-19409029,		-19078901,		-20960656,		
    -20671486,		-9004617,		9335963,		25814146,		40612477,		52293666,		58192068,		
    58383411,		49495722,		29294244,		5446999,		-11503961,		-18355319,		-18496956,		
    -17055620,		-15670928,		-12056189,		-5001206,		4147333,		13321315,		21772975,		
    30521354,		40212462,		48056256,		48469990,		39292127,		25851641,		17215612,		
    15553945,		14547070,		9437663,		-54420,		    -10729592,		-16527361,		-14998370,		
    -8056709,		3243588,		16131861,		24378596,		24982928,		19800450,		13573901,		
    14477314,		23936532,		32515913,		34252115,		30664570,		24514633,		18503071,		
    12447951,		3701251,		-5852603,		-10553043,		-9505640,		-5217162,		104826,		
    3318857,		4089078,		4783649,		5725864,		7775101,		13270951,		22005664,		
    31717619,		39544450,		41236931,		37040390,		32670545,		29548559,		25402176,		
    20103065,		13462534,		6432003,		2147572,		1181318,		2528744,		6039504,		
    10285974,		14902919,		20679473,		24917914,		25771231,		24913991,		21690054,		
    15379192,		8878210,		3873389,		300410,		
};

//=========================== STATIC MEMBER VARIABLES - ICON =======================

const Effect_Icon_t Effect_Cab_Sim::icon = {
    0xF8, 0xFF, 0xFF, 0x01, 0x06, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x06, 
    0x01, 0x00, 0x00, 0x04, 0xF9, 0xFF, 0xFF, 0x04, 0x09, 0x00, 0x80, 0x04, 
    0xE9, 0xEE, 0xB6, 0x04, 0xA9, 0xAA, 0xB6, 0x04, 0xE9, 0xEE, 0x80, 0x04, 
    0x09, 0x40, 0x80, 0x04, 0x09, 0xE8, 0x80, 0x04, 0x09, 0x04, 0x83, 0x04, 
    0x09, 0x72, 0x82, 0x04, 0x09, 0x8A, 0x80, 0x04, 0x09, 0x8A, 0x84, 0x04, 
    0x09, 0x99, 0x82, 0x04, 0x09, 0x72, 0x82, 0x04, 0x09, 0x04, 0x81, 0x04, 
    0x09, 0xCC, 0x80, 0x04, 0x09, 0x20, 0x80, 0x04, 0xF9, 0xFF, 0x7F, 0x04, 
    0xE1, 0x00, 0x38, 0x04, 0xF1, 0xFF, 0xFF, 0x04, 0x09, 0x00, 0x80, 0x04, 
    0x09, 0x10, 0x80, 0x04, 0x09, 0x98, 0x80, 0x04, 0x09, 0x04, 0x81, 0x04, 
    0x09, 0x72, 0x82, 0x04, 0x09, 0x49, 0x82, 0x04, 0x09, 0x88, 0x84, 0x04, 
    0x09, 0xDA, 0x80, 0x04, 0x09, 0x72, 0x82, 0x04, 0x09, 0x04, 0x81, 0x04, 
    0x09, 0xA8, 0x80, 0x04, 0x09, 0x20, 0x80, 0x04, 0x09, 0x00, 0x80, 0x04, 
    0xF1, 0xFF, 0xFF, 0x04, 0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x04, 
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
        sum = sum << 1;

        //and our sample output would be the upper 16 bits of the sum
        //the previous left shift and this right shift should be consolidated into a single shift
        //writing it this way for clarity
        sample_out = (int16_t)(sum >> 16);

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