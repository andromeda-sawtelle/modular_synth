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
        virtual module* create_module(int type);
        virtual int edit_parameter(int option, float value);
        virtual int delete_module(module* module);
        virtual int processFrame(float* frame, unsigned int frameCount);

        friend std::ostream& operator << (std::ostream &os, const module &m) {
            return (os << "Message: " << m.type << std::endl);
        }
    };
}
