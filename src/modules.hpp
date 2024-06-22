#ifndef MODULE_H
#define MODULE_H

#include <iostream>

namespace modules{
    enum Type {
        NA,
        AUDIO,
        OSC,
        VCA,
        LPF
    };

    class module {
    public:
        module();
        module(modules::Type type);

        virtual int processFrame(float* frame, unsigned int frameCount) = 0;

        modules::Type type;

        module* input = nullptr;
        module* output = nullptr;


        friend std::ostream& operator << (std::ostream &os, const module &m);
    };

}
#endif //MODULE_H
