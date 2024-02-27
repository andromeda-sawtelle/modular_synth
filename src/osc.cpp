#include "osc.hpp"

osc::osc() : module(OSC){
    parameters.freq = 440;
    parameter.wave = SIN;
}

osc_parameters get


int edit_parameter(int option, float value) {
    switch(option){
        case WAVE:
            break;
        case FREQ:
            parameters.freq = value;
    };
    return 0;
}

int processFrame(float* frame, unsigned int frameCount) {
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
