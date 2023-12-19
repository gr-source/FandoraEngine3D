#pragma once

#include "Global.h"

struct {
    std::string exec(const char* cmd) {
        std::string str;

        FILE* pipe = popen(cmd, "r");
        if (pipe != nullptr) {
            std::string line(0, 1024);
            while (fgets(line.data(), line.size(), pipe) != nullptr) {
                std::cout << line << std::endl;
            }
            pclose(pipe);
        }
        return str;
    }
} Command;

