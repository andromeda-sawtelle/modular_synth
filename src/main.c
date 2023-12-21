#include "main.h"

static module_t data[2];
static size_t data_len = 1;

static int mainCallback( const void *input,
                         void *output,
                         unsigned long frameCount,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData ){
    module_t *data = (module_t *)userData;
    (void *)input;

    for(int i = data_len-1; i >= 0; i--) {
        switch(data->type){
            case OSC:
                data->module.osc->oscCallback(data->module.osc->data,
                                             frameCount,
                                             timeInfo,
                                             statusFlags,
                                             output);
                break;
            case TEST:
                printf("test");
        }
    }

    return 0;
}

static int init_data(){
    int res = 0;
    data[0].type = OSC;
    data[0].module.osc = createOsc();
    if(data[0].module.osc == NULL){
        res = 1;
    }
    return res;
}

static int delete_data(){
    int res = 0;
    deleteOsc(data[0].module.osc);
    return res;
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
                                256,        /* frames per buffer, i.e. the number
                                                   of sample frames that PortAudio will
                                                   request from the callback. Many apps
                                                   may want to use
                                                   paFramesPerBufferUnspecified, which
                                                   tells PortAudio to pick the best,
                                                   possibly changing, buffer size.*/
                                mainCallback, /* this is your callback */
                                &data ); /*This is a pointer that will be passed to
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
