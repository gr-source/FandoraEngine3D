#pragma once

#include "Global.h"

namespace Resources {
    
    template<typename T>
    T& Load(const std::string& path);

    template<typename T>
    std::vector<std::unique_ptr<T>> LoadAll(const std::string& path);
};

