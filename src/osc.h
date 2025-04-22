#ifndef OSC_H_
#define OSC_H_

#include <portaudio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define TABLE_SIZE (200)
#ifndef M_PI
#define M_PI  (3.14159265)
#endif

enum WAVE_TYPE {
    SIN,
    TRI,
    SAW,
    SQR
};

typedef struct osc_data {
    float table[TABLE_SIZE];
    float freq;
    int left_phase;
    int right_phase;
    enum WAVE_TYPE wave;
}osc_data_t;

typedef struct osc {
    osc_data_t data;
    int (*oscCallback)(osc_data_t,
                       unsigned int,
                       float*);
}osc_t;

osc_t* createOsc();
void deleteOsc(osc_t* osc);

#endif // OSC_H_
