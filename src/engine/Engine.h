#pragma once

#include "Global.h"

struct Engine {
    GameObject* gameObject;
    bool enable;

    void load(GameObject* gameObject, bool enable = true);

};












