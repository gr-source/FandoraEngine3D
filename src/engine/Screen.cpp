#include "Screen.h"

float Screen::width = 0;
float Screen::height = 0;

void Screen::SetResolution(float w, float h) {
    width = w;
    height = h;
}

const Vector2 Screen::GetResolution() {
    return {Screen::width, Screen::height};
}
