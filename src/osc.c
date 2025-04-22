#include "osc.h"

int oscProcess(osc_data_t data,
               unsigned int frameCount,
               float *out)
{
    unsigned int i;
    for(i = 0; i < frameCount; i++) {
        *out++ = data.table[data.left_phase];
        *out++ = data.table[data.right_phase];
        data.left_phase += 1;
        if( data.left_phase >= TABLE_SIZE ) data.left_phase -= TABLE_SIZE;
        data.right_phase += 1; /* higher pitch so we can distinguish left and right. */
        if( data.right_phase >= TABLE_SIZE ) data.right_phase -= TABLE_SIZE;
    }
    return 0;
}

osc_t* createOsc(){
    osc_t* osc = (osc_t*)malloc(sizeof(osc_t));
    if(osc == NULL){
        return NULL;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        osc->data.table[i] = (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
    }
    osc->data.wave = 0;
    osc->oscCallback = &oscProcess;
    return osc;
}

void deleteOsc(osc_t* osc) {
    free(osc);
}
