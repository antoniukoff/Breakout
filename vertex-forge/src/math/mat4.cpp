#include "mat4.h"
#include <iostream> 

mat4 mat4::translate(vec3 pos)
{
    mat4 t_matrix;
    t_matrix.load_identity();
    t_matrix(0, 3) = pos.x;
    t_matrix(1, 3) = pos.y;
    t_matrix(2, 3) = pos.z;

    return t_matrix;
}

mat4 mat4::rotate_y(float amount, bool to_rad)
{
    mat4 rotation;
    float rad_amount = (to_rad) ? TO_RAD(amount) : amount;
    float cos_theta = cosf(rad_amount);
    float sin_theta = sinf(rad_amount);

    rotation(0, 0) = cos_theta;
    rotation(0, 2) = sin_theta;
    rotation(1, 1) = 1.0f;
    rotation(2, 0) = -sin_theta;
    rotation(2, 2) = cos_theta;
    rotation(3, 3) = 1.0f;

    return rotation;
}

mat4 mat4::rotate_x(float amount, bool to_rad)
{
    mat4 rotation;
    float rad_amount = (to_rad) ? TO_RAD(amount) : amount;
    float cos_theta = cosf(rad_amount);
    float sin_theta = sinf(rad_amount);

    rotation(0, 0) = 1.0f;
    rotation(1, 1) = cos_theta;
    rotation(1, 2) = -sin_theta;
    rotation(2, 1) = sin_theta;
    rotation(2, 2) = cos_theta;
    rotation(3, 3) = 1.0f;

    return rotation;
}

void mat4::mult_vec_by_mat(const mat4& mat, vec3& vec)
{
    vec3 new_vec;

    new_vec.x = mat(0, 0) * vec.x + mat(0, 1) * vec.y + mat(0, 2) * vec.z + mat(0, 3) * 1.0f;
    new_vec.y = mat(1, 0) * vec.x + mat(1, 1) * vec.y + mat(1, 2) * vec.z + mat(1, 3) * 1.0f;
    new_vec.z = mat(2, 0) * vec.x + mat(2, 1) * vec.y + mat(2, 2) * vec.z + mat(2, 3) * 1.0f;
    float w   = mat(3, 0) * vec.x + mat(3, 1) * vec.y + mat(3, 2) * vec.z + mat(3, 3) * 1.0f;

    if (w != 0)
    {
        new_vec.x /= w;
        new_vec.y /= w;
        new_vec.z /= w;
    }

    vec = new_vec;
}

mat4 mat4::mult_mat_by_mat(const mat4& other_mat, const mat4& mat)
{
    mat4 new_mat = {}; // Initialize to 0

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            new_mat(j, i) = other_mat(j, 0) * mat(0, i) +
                            other_mat(j, 1) * mat(1, i) +
                            other_mat(j, 2) * mat(2, i) +
                            other_mat(j, 3) * mat(3, i);
        }
    }

    return new_mat;
}

float& mat4::operator()(int row, int column) 
{
	return m[column * 4 + row];
}

const float& mat4::operator()(int row, int column) const
{
	return m[column * 4 + row];
}

mat4 mat4::operator*(const mat4& other)
{
    return mat4::mult_mat_by_mat(*this, other);
}

void mat4::print_matrix()
{
    for (int i = 0; i < 4; ++i)
    {
        std::cout << "[ ";
        for (int j = 0; j < 4; j++)
        {
            std::cout << (*this)(i, j) << ", ";
        }
        std::cout << "] " << std::endl;

    }
    std::cout << std::endl;
}

void mat4::load_identity()
{
    (*this)(0, 0) = 1.0f;
    (*this)(1, 1) = 1.0f;
    (*this)(2, 2) = 1.0f;
    (*this)(3, 3) = 1.0f;
}

mat4 mat4::calculate_projection(float aspect_ration, float fov, float near, float far)
{
    mat4 projection;
    float fov_rad = TO_RAD(fov);
    float half_tan_fov = tanf(fov_rad / 2.0f);

    projection(0, 0) = 1.0f / (half_tan_fov * aspect_ration);
    projection(1, 1) = 1.0f / half_tan_fov;
    projection(2, 2) = -((far + near) / (far - near));
    projection(2, 3) = -((2 * far * near) / (far - near));
    projection(3, 2) = -1;
    projection(3, 3) = 0.0f;

    return projection;
}

mat4 mat4::calculate_view_matrix(vec3 eye, vec3 to, vec3 up)
{
    vec3 forward = vec3::normalize(eye - to);
    vec3 right = vec3::normalize(vec3::cross(up, forward));
    vec3 local_up = vec3::cross(forward, right);

    mat4 view_matrix;

    view_matrix(0, 0) = right.x;
    view_matrix(0, 1) = right.y;
    view_matrix(0, 2) = right.z;

    view_matrix(1, 0) = local_up.x;
    view_matrix(1, 1) = local_up.y;
    view_matrix(1, 2) = local_up.z;

    view_matrix(2, 0) = forward.x;
    view_matrix(2, 1) = forward.y;
    view_matrix(2, 2) = forward.z;

    view_matrix(0, 3) = -vec3::dot(right, eye);
    view_matrix(1, 3) = -vec3::dot(local_up, eye);
    view_matrix(2, 3) = -vec3::dot(forward, eye);

    view_matrix(3, 3) = 1.0f;

    return view_matrix;
}

