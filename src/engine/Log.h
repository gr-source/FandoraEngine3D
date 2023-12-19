#pragma once

#include <iostream>
#include <string>

struct {

    void Write(const std::string& msg) {
        std::cout << msg << std::endl;
    }
} Log;

