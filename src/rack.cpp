#include <iostream>
#include <string>
#include <memory>

#include "audio.hpp"
#include "osc.hpp"

using namespace std;
using namespace modules;

int loop() {
    return 0;
}

int main(int argc, char** argv) {
    auto data = std::make_unique<data_t>(10);
    start_audio(data);
    loop();
    stop_audio();
    return 0;
}
