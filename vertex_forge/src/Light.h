#pragma once
#include "math/vec3.h"

struct Light
{
    float ambient = 0.2f;
    float diffuse = 0.5f;
    float specular = 1.0f;
    vec4 color = { 1.0f, 1.0, 1.0f, 1.0f };
};

