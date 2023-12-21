#ifndef OSC_H_
#define OSC_H_

#include <portaudio.h>
#include <stdlib.h>

typedef struct osc_data {
  float left_phase;
  float right_phase;
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
