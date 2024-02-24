#ifdef OSC_H
#define OSC_H

#include "modules.h"

namespace modules {
    struct osc_data {
        float left_phase
        float right_phase
    };
    struct osc_parameters {
        float freq
        char wave
    }

    class osc : module {
        osc_data data;
        osc_parameters parameters;

    public:
        osc(types type){
            super(type);
        }

        int edit_parameter(int option, float value) {
            paramters[option] = value;
            return 0;
        }
        int processFrame(float* frame, unsigned int frameCount) {

            for(i = 0; i < frameCount; i++){
                *frame++ = data.left_phase;  /* left */
                *frame++ = data.right_phase;  /* right */
                /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
                data.left_phase += 0.01f;
                /* When signal reaches top, drop back down. */
                if( data.left_phase >= 1.0f ) data.left_phase -= 2.0f;
                //data.left_phase *= 0.5;
                /* higher pitch so we can distinguish left and right. */
                data.right_phase += 0.01f;
                if( data.right_phase >= 1.0f ) data.right_phase -= 2.0f;
                //data.right_phase *= 0.5;
            }
            return 0;
        }
    }
}

#endif //OSC_H
