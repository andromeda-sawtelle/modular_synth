#include "modules.hpp"

using namespace modules;

module::module() {
    this->type = NA;
}
module::module(Type type) {
    this->type = type;
}

std::ostream& operator << (std::ostream &os, const module &m) {
    return (os << "Message: " << std::endl);
}

