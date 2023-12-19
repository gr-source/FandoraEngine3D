#pragma once

#include "Global.h"

class Mesh {
private:
public:
    std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector2> uv;
    
    Mesh() = default;

};



