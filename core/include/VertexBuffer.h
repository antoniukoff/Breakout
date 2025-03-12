#pragma once
#include "VertexLayout.h"

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void upload_data(const std::vector<float>& vertices);
    void bind() const;
    void unbind();

    inline uint32_t get_attribute_count() const
    {
        return m_total_count;
    }

    inline uint32_t get_id() const
    {
        return m_id;
    }

private:
    uint32_t m_id = 0;
    uint32_t m_total_count = 0;
};

