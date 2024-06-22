#ifndef OSC_H
#define OSC_H

#include "modules.hpp"

namespace modules {
    enum wave_t {
        SIN,
        TRI,
        SAW,
        SQR
    };

    enum osc_param {
        WAVE,
        FREQ
    };

    struct osc_data {
        float left_phase;
        float right_phase;
    };
    struct osc_parameters {
        float freq;
        wave_t wave;
    };

    class osc : virtual public module {
        osc_data data;
        osc_parameters parameters;
    public:
        osc();
        int edit_parameter(int option, float value);
        int processFrame(float* frame, unsigned int frameCount) override;
    };
}

#endif //OSC_H
