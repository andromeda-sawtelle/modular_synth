#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <portaudio.h>
#include "osc.h"

#define SAMPLE_RATE (44100)
#define NUM_SECONDS 2

enum modType {
    OSC,
    TEST
};

typedef struct testMod {
    int x;
    float y;
}testMod_t;

typedef struct module {
    enum modType type;
    union {
        osc_t *osc;
        testMod_t *test;
    }module;
}module_t;

#endif // MAIN_H_
