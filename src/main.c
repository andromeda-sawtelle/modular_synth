#include <stdio.h>
#include <portaudio.h>

int main(int argc, char const *argv[])
{
	PaError err;

	err = Pa_Initialize();
	if (err != paNoError){
		printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
	}

	err = Pa_Terminate();
	if( err != paNoError ) {
		printf(  "PortAudio error: %s\n", Pa_GetErrorText( err ) );
	}

	return 0;
}
