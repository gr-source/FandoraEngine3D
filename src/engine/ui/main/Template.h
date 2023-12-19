#pragma once

enum AlertType {
    ERROR,
    SUCCESS,
    NONE
};

namespace Template {

    void AlertWindow(const char* title, const char* message, const AlertType& type);
}
