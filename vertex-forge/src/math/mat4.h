#pragma once

#include "vec3.h"

struct mat4
{
    float m[16] = { 0 };

    static mat4 translate(vec3 pos);
	static mat4 rotate_y(float amount, bool to_rad = true);
	static mat4 rotate_x(float amount, bool to_rad = true);

    static void mult_vec_by_mat(const mat4& mat, vec3& vec);
    static mat4 mult_mat_by_mat(const mat4& other_mat, const mat4& mat);

    float& operator()(int row, int column);
    const float& operator()(int row, int column) const;
    mat4 operator *(const mat4& other);

    void print_matrix();

    void load_identity();

    static mat4 calculate_projection(float aspect_ration, float fov, float near, float far);

    static mat4 calculate_view_matrix(vec3 eye, vec3 to, vec3 up);

};

