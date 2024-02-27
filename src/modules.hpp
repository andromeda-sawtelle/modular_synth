#ifndef MODULE_H
#define MODULE_H

#include <iostream>

enum types {
    NA,
    AUDIO,
    OSC,
    VCA,
    LPF
};

class module {
    types type;
public:
    module* input = nullptr;
    module* output = nullptr;

    module() {
        type = NA;
    }
    module(types mod_type){
        type = mod_type;
    }

    virtual int processFrame(float* frame, unsigned int frameCount);

    friend std::ostream& operator << (std::ostream &os, const module &m) {
        return (os << "Message: " << std::endl);
    }
};

template <typename E>
constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}


#endif //MODULE_H
