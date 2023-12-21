#include "vca.h"


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
