#ifndef MODULE_H
#define MODULE_H

#include <iostream>

namespace modules{
    enum types {
        OSC,
        VCA,
        LPF
    };

    class module {
        types type;
    public:
        module(types type){
            this->type = type;
        }
        virtual int edit_parameter(int option, float value);
        virtual int processFrame(float* frame, unsigned int frameCount);

        friend std::ostream& operator << (std::ostream &os, const module &m) {
            return (os << "Message: " << m.type << std::endl);
        }
    };
}

#endif //MODULE_H
