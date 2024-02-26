#include <iostream>

#include "audio.hpp"

#define SAMPLE_RATE 48000

static PaError err;
static PaStream* stream;

static int mainCallback( const void *input,
                         void *output,
                         unsigned long frameCount,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData ){
    data_t* data = (data_t*) userData;
    float* out = (float*) output;
    for(int i = data->length; i >= 0; i--) {

    }
    return 0;
}

static int processModules(modules::module* m){
    if(m == nullptr){
        return 0;
    }
    return processModules(m->input);
}

int start_stream(modules::module* data){
    err = Pa_Initialize();
    if( err != paNoError ) goto start_error;

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
    if( err != paNoError ) goto start_error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto start_error;

    return 0;

start_error:
    err = Pa_Terminate();
    if( err != paNoError ) {
        std::cout << "PortAudio error: " << Pa_GetErrorText( err );
    }
    return 1;
}

int stop_stream() {
    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

error:
    err = Pa_Terminate();
    if( err != paNoError ) {
        printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
    }

    return 0;
}