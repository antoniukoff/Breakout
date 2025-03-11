#pragma once
#include "VertexLayout.h"

class VertexBuffer
{
public:
    VertexBuffer();

    void upload_data(const std::vector<float>& vertices);

    void set_layout(const VertexLayout& layout);

    void enable_layout() const;

    void bind() const;

    void unbind();

private:
    VertexLayout m_layout;
    unsigned int m_id = 0;
};

