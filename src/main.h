#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <portaudio.h>
#include <stdbool.h>
#include <string.h>

#include "osc.h"
#include "vca.h"

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER  (64)
#define NUM_SECONDS 2

enum modType {
    AUDIO_OUT,
    OSC,
    VCA
};

typedef struct module module_t;

struct module {
    enum modType type;
    void *module;
    module_t *input;
    module_t *output;
};

#endif // MAIN_H_
