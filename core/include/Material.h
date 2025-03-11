#pragma once
#include "math/vec3.h"

struct Material
{
    vec4 ambient = { 0.5f, 0.73f, 0.4f, 1.0f };
    vec4 diffuse = { 0.5f, 0.73f, 0.4f, 1.0f };
    vec4 specular = { 0.5f, 0.73f, 0.4f, 1.0f };
    float shininess = 96;
};

