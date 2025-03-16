#pragma once
#include "VertexLayout.h"
#include "math/vec3.h"
#include "math/vec2.h"

struct Vertex
{
    vec3 position;
    vec2 uv;
    vec3 normal;
};

struct Face
{
    Vertex v[3];
};

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void upload_data(const std::vector<float>& vertices);
    void upload_data(const std::vector<Face>& faces);
    void bind() const;
    void unbind();


    inline uint32_t get_id() const
    {
        return m_id;
    }

private:
    uint32_t m_id = 0;
};

