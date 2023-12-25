#ifndef VCA_H_
#define VCA_H_

#include <portaudio.h>
#include <stdlib.h>

enum params {
  GAIN
};

typedef struct vca_data {
  float gain;
}vca_data_t;

typedef struct vca {
  vca_data_t data;
  int (*vcaCallback)(vca_data_t,
                    unsigned int,
                    float*);
}vca_t;

vca_t* createVca(float gain);
void deleteVca(vca_t* vca);
int edit_vca_params(vca_t *vca, int param, float value);
int edit_gain(vca_t *vca, float value);

#endif // VCA_H_
