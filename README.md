# Modular Synth
Since I didn't like existing software modular synthesizers, and I wanted to learn more about audio programming, I decided to make my own.
Only required library is Portaudio, since I want to do all the audio processing myself to learn.

## Build
`cmake -S . -B build` to configure

`cmake --build build` to build

## Usage
- `l`
  - List existing modules
- `q`
  - Quit program
- `c <module type>`
  - Create a module of given type
- `e <module index> <parameter number> <value>`
  - Edit given parameter on given module to value
