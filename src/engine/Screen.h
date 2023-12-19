#pragma once

#include "Global.h"

namespace Screen {
    extern float width;
    extern float height;

    void SetResolution(float width, float height);

    const Vector2 GetResolution();
};

