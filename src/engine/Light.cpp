#include "Light.h"

Light::Light(const Vector3& position, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular) : position(position), ambient(ambient), diffuse(diffuse), specular(specular) {}

Light& Light::GetSun() {
    static Light light(Vector3(0, 0, 0), Vector3(0.3, 0.3, 0.3), Vector3(1.0, 1.0, 0.9), Vector3(1.0, 1.0, 1.0));
    return light;
}
