#include "osc.hpp"

using namespace modules;

osc::osc() : module(OSC){
    parameters.freq = 440;
    parameters.wave = SIN;
}

int osc::edit_parameter(int option, float value) {
    switch(option){
        case WAVE:
            parameters.wave = static_cast<wave_t>(int(value));
            break;
        case FREQ:
            parameters.freq = value;
    };
    return 0;
}

int osc::processFrame(float* frame, unsigned int frameCount) {
    for(uint i = 0; i < frameCount; i++){
        *frame++ = data.left_phase;  /* left */
        *frame++ = data.right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        data.left_phase += 0.01f;
        /* When signal reaches top, drop back down. */
        if( data.left_phase >= 0.5f ) data.left_phase -= 1.0f;
        //data.left_phase *= 0.5;
        /* higher pitch so we can distinguish left and right. */
        data.right_phase += 0.01f;
        if( data.right_phase >= 0.5f ) data.right_phase -= 1.0f;
        //data.right_phase *= 0.5;
    }
    return 0;
}
