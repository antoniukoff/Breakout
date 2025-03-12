#pragma once
#include "VertexLayout.h"

class VertexBuffer
{
public:
    VertexBuffer();

    void upload_data(const std::vector<float>& vertices);
    void bind() const;
    void unbind();

private:
    unsigned int m_id = 0;
};

