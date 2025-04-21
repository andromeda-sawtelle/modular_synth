#include "main.h"

// Need to change to easily remove modules
// When deleteing, replace module at index with the module at the
// end of the array, then decrement n_data
static module_t data[50];
static int n_data = 1;

static int mainCallback( const void *input,
                         void *output,
                         unsigned long frameCount,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData ){
    module_t *data = (module_t *)userData;
    float *out = (float*) output;
    (void *)input;
    for(int i = n_data-1; i >= 0; i--) {
        module_t curr_module = data[i];
        switch(curr_module.type){
            case AUDIO_OUT:
                break;
            case OSC:{
                osc_t* osc = (curr_module.module);
                osc->oscCallback(osc->data,
                                frameCount,
                                out);
                break;
            }
            case VCA:{
                vca_t *vca = (curr_module.module);
                vca->vcaCallback(vca->data,
                                frameCount,
                                out);
            }
        }

    }
    return 0;
}

static void delete_data(){
    for(int i = 0; i < n_data; i++){
        module_t module = data[i];
        switch (module.type) {
            case AUDIO_OUT:
                break;
            case OSC:{
                osc_t *osc = (osc_t*)(module.module);
                deleteOsc(osc);
                break;
            }
            case VCA:{
                vca_t *vca = (vca_t*)(module.module);
                deleteVca(vca);
                break;
            }
        }

    }
}

void create_module(enum modType type){
    switch(type){
    case AUDIO_OUT:
        printf("Cannot create a new Audio Out\n");
        break;
    case OSC:
        break;
    case VCA:
        break;
    }
}

void delete_module(int index){
    printf("Delete module at %d\n", index);
}

char* get_device_name(module_t *module){
    switch (module->type) {
    case AUDIO_OUT:
        return "Audio Out";
    case OSC:
        return "Oscillator";
    case VCA:
        return "VCA";
    default:
        return NULL;
    }
}

int print_devices(){
    for(int i = 0; i < n_data; i++){
        printf("%d: %s\n", i, get_device_name(&data[i]));
    }
    return 0;
}

int edit_device(module_t *module, const int param, const float value){
    switch (module->type) {
    case VCA:
        return edit_vca_params((vca_t*)module->module, param, value);
        break;
    case OSC:
        break;
    default:
        printf("Unknown device\n");
    }

    return 1;
}

int loop(){
    bool running = true;
    while(running){
        char line[256];
        if (fgets(line, sizeof(line), stdin)) {
            switch (line[0]) {
                int i;
                char *p;
            case 'q':
                running = false;
                break;
            case 'l':
                print_devices();
                break;
            case 'e':
                i = 1;
                module_t *module;
                int param;
                float value;
                p = strtok(line, " ");
                for (p = strtok(NULL, " "); p != NULL; p = strtok(NULL, " ")){
                    char *end;
                    switch (i) {
                    case 1:{
                        //determine module
                        int index = strtol(p, &end, 10);
                        if((index < 0) && (index >= n_data)){
                            fprintf(stderr, "%d is out of range for existing modules\n", index);
                            return 1;
                        }
                        module = &data[index];
                        break;
                    }
                    case 2:
                        //get the param num
                        param = strtol(p, &end, 10);
                        break;
                    case 3:
                        //get the value
                        value = strtof(p, &end);
                        break;
                    }
                    i++;

                }
                edit_device(module, param, value);
                break;
            case 'c':
                switch(line[1]){
                case 'r':
                    p = strtok(line, " ");
                    p = strtok(NULL, " \n");

                    printf("%s\n", p);

                    if(strcmp(p, "osc") == 0){
                        printf("WTF\n");
                        data[n_data].type = OSC;
                        data[n_data].module = createOsc();
                        n_data++;
                    }
                    else if(strcmp(p, "vca") == 0){
                        data[n_data].type = VCA;
                        data[n_data].module = createVca(1);
                        n_data++;
                    }
                    else{
                        printf("%s -> unrecognized module\n", p);
                    }

                    break;
                case 'n': 
                    i = 1;
                    module_t *module1;
                    module_t *module2;
                    p = strtok(line, " ");
                    for (p = strtok(NULL, " "); p != NULL; p = strtok(NULL, " ")){
                        char *end;
                        switch (i) {
                        case 1:{
                            //determine module
                            int index = strtol(p, &end, 10);
                            if((index < 0) && (index >= n_data)){
                                fprintf(stderr, "%d is out of range for existing modules\n", index);
                                return 1;
                            }
                            module1 = &data[index];
                            break;
                        }
                        case 2:
                            //determine module 2
                            int index = strtol(p, &end, 10);
                            if((index < 0) && (index >= n_data)){
                                fprintf(stderr, "%d is out of range for existing modules\n", index);
                                return 1;
                            }
                            module2 = &data[index];
                            break;
                        i++;
                        }
                    }
                default:
                    printf("command %s is not available\n", line);
                }
                break;
            default:
                printf("command %c is not valid\n", line[0]);
            }
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    PaStreamParameters outputParameters;
    PaError err;
    PaStream *stream;

    data[0].type = AUDIO_OUT;
    data[n_data].type = OSC;
    data[n_data].module = createOsc();
    n_data++;

    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        goto error;
    }
    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    /* Open an audio I/O stream. */
    err = Pa_OpenStream( &stream,
                                NULL,
                                &outputParameters,
                                SAMPLE_RATE,
                                FRAMES_PER_BUFFER,
                                paClipOff,
                                mainCallback, /* this is your callback */
                                data); /*This is a pointer that will be passed to
                                                   your callback*/
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    //loop();
    Pa_Sleep(NUM_SECONDS);

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
