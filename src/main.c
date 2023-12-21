#include "main.h"

static module_t *data;
static int data_len = 2;

static int mainCallback( const void *input,
                         void *output,
                         unsigned long frameCount,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData ){
    module_t *data = (module_t *)userData;
    float *out = (float*) output;
    (void *)input;
    for(int i = data_len-1; i >= 0; i--) {
        module_t curr_module = data[i];
        switch(curr_module.type){
            case OSC:
                osc_t* osc = (osc_t*)(curr_module.module);
                osc->oscCallback(osc->data,
                                frameCount,
                                out);
                break;
            case VCA:
                vca_t* vca = (vca_t*)(curr_module.module);
                vca->vcaCallback(vca->data,
                                frameCount,
                                out);
        }

    }
    return 0;
}

static int init_data(){
    data = malloc(sizeof(module_t) * data_len);
    if(data == NULL){
        return 1;
    }

    data[1].type = OSC;
    data[1].module = createOsc();
    if(data[1].module == NULL){
        return 1;
    }

    data[0].type = VCA;
    data[0].module = createVca(0.01);
    if(data[0].module == NULL){
        return 1;
    }

    return 0;
}

static void delete_data(){
    for(int i = 0; i < data_len; i++){
        module_t module = data[i];
        switch (module.type) {
        case OSC:
            osc_t *osc = (osc_t*)(module.module);
            deleteOsc(osc);
            break;
        case VCA:
            vca_t *vca = (vca_t*)(module.module);
            deleteVca(vca);
            break;
        }

    }
    free(data);
}

int main(int argc, char const *argv[])
{
	PaError err;
    PaStream *stream;

    if(init_data()){
        return 1;
    }

	err = Pa_Initialize();
    if( err != paNoError ) goto error;

    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paFloat32,  /* 32 bit floating point output */
                                SAMPLE_RATE,
                                paFramesPerBufferUnspecified,        /* frames per buffer, i.e. the number
                                                   of sample frames that PortAudio will
                                                   request from the callback. Many apps
                                                   may want to use
                                                   paFramesPerBufferUnspecified, which
                                                   tells PortAudio to pick the best,
                                                   possibly changing, buffer size.*/
                                mainCallback, /* this is your callback */
                                data); /*This is a pointer that will be passed to
                                                   your callback*/
    if( err != paNoError ) goto error;

	err = Pa_StartStream( stream );
	if( err != paNoError ) goto error;

	Pa_Sleep(NUM_SECONDS*1000);

	err = Pa_StopStream( stream );
	if( err != paNoError ) goto error;

	err = Pa_CloseStream( stream );
	if( err != paNoError ) goto error;

error:
	err = Pa_Terminate();
	if( err != paNoError ) {
		printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
	}

    delete_data();

	return 0;
}
