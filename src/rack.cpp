#include <iostream>
#include <string>

#include "modules.hpp"

using namespace std;
using namespace modules;

class rack {
    module* modules;
    char length = 0;

public:
    rack() {
    }
    ~rack(){
    }
};

int main(int argc, char** argv) {
    rack rack;
}
