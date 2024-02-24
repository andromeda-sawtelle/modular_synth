#include "osc.h"

int oscProcess(osc_data_t data,
               unsigned int frameCount,
               float *out)
{
  unsigned int i;
    for(i = 0; i < frameCount; i++){
        *out++ = data.left_phase;  /* left */
        *out++ = data.right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        data.left_phase += 0.01f;
 /* When signal reaches top, drop back down. */
        if( data.left_phase >= 1.0f ) data.left_phase -= 2.0f;
        //data.left_phase *= 0.5;
        /* higher pitch so we can distinguish left and right. */
        data.right_phase += 0.01f;
        if( data.right_phase >= 1.0f ) data.right_phase -= 2.0f;
        //data.right_phase *= 0.5;
    }
    return 0;
}

osc_t* createOsc(){
  osc_t* osc = (osc_t*)malloc(sizeof(osc_t));
  if(osc == NULL){
    return NULL;
  }
  osc->oscCallback = &oscProcess;
  return osc;
}

void deleteOsc(osc_t* osc) {
  free(osc);
}
