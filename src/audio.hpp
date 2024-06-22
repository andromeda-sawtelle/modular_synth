#ifndef AUDIO_H
#define AUDIO_H

#include <portaudio.h>

#include "modules.hpp"

namespace modules{
    class audio_out : virtual public module {
        int num;
    public:
        audio_out();

        int edit_parameters(int option, float value){
            return 0;
        }
        int processFrame(float* frame, uint frameCount){
            return 0;
        }
    };
}

using namespace modules;

class data_t {
public:
    modules::module** modules;
    int length;
    int capacity;

    data_t(int cap){
        modules = new modules::module*[cap];
        modules[0] = new modules::audio_out();
        length = 1;
        capacity = cap;
    }
    ~data_t(){
        for(int i = 0; i < length; i++){
            delete modules[i];
        }
        delete[] modules;
    }
};

int start_audio(modules::module* data);

int stop_audio();

#endif //AUDIO_H
