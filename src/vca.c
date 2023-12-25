#include "vca.h"

#include <stdio.h>

int vcaProcess(vca_data_t data,
               unsigned int frameCount,
               float *out)
{
  unsigned int i;
  for(i = 0; i < frameCount; i++){
    *out++ *= data.gain;
    *out++ *= data.gain;
  }
  return 0;
}

vca_t* createVca(float gain){
  vca_t* vca = (vca_t*)malloc(sizeof(vca_t));
  if(vca == NULL){
    return NULL;
  }
  vca->vcaCallback = &vcaProcess;
  vca->data.gain = gain;
  return vca;
}

void deleteVca(vca_t* vca) {
  free(vca);
}

int edit_gain(vca_t *vca, float value){
  vca->data.gain = value;
  return 0;
}

int edit_vca_params(vca_t *vca, int param, float value){
  switch (param) {
  case GAIN:
    edit_gain(vca, value);
    break;
  default:
    fprintf(stderr, "%d is not a valid parameter for a VCA\n", param);
    return 1;
  }

  return 0;
}
