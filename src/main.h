#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <portaudio.h>
#include <stdbool.h>
#include <string.h>

#include "osc.h"
#include "vca.h"

#define SAMPLE_RATE (44100)
#define NUM_SECONDS 2

enum modType {
    OSC,
    VCA
};

typedef struct module {
    enum modType type;
    void *module;
}module_t;

#endif // MAIN_H_
