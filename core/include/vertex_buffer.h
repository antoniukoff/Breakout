#pragma once
#include "vertex_layout.h"
#include "math/vec3.h"
#include "math/vec2.h"

struct vertex
{
    vec3 position;
    vec2 uv;
    vec3 normal;
};

struct face
{
    vertex v[3];
};

class vertex_buffer
{
public:
    vertex_buffer();
    ~vertex_buffer();

    void upload_data(const std::vector<float>& vertices);
    void upload_data(const std::vector<face>& faces);
    void bind() const;
    void unbind();


    inline uint32_t get_id() const
    {
        return m_id;
    }

private:
    uint32_t m_id = 0;
};

