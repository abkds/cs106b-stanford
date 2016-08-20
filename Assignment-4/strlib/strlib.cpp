//
// Created by Abhishek K Das on 20/08/16.
//

#include "strlib.h"
#include <algorithm>
#include <string>

std::string toLowerCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


std::string toUpperCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
