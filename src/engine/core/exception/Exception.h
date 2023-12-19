#pragma once

#include <string>

class Exception {
public:
    Exception(const std::string& message) : message(message) {}

    std::string getMessage() {
        return message;
    }

private:
    std::string message;
};

