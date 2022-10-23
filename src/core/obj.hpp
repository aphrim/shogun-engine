#pragma once
#include "include.hpp"

namespace SHOGUN {

class OBJParser {
public:
    std::vector<float> parseObj(const char* objPath);
};

}
