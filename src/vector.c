#include "vector.h"
#include <math.h>

float vec2_length(vec2_t v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

float vec2_length_squared(vec2_t v)
{
    return v.x * v.x + v.y * v.y;
}

vec2_t vec2_add(vec2_t a, vec2_t b)
{
    vec2_t new_vec = 
    {
        a.x + b.x, a.y + b.y
    };

    return new_vec;
}

float vec3_length(vec3_t v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec3_length_squared(vec3_t v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

vec3_t vec3_add(vec3_t a, vec3_t b)
{ 
    vec3_t new_vec = 
        {
            a.x + b.x,
            a.y + b.y,
            a.z + b.z
        };
    return new_vec; 
}

vec3_t vec3_rotate_z(vec3_t vec, float angle)
{
    vec3_t rotated =
    {
        vec.x * cos(angle) - vec.y * sin(angle),
        vec.y * cos(angle) + vec.x * sin(angle),
        vec.z
    };
return rotated;
}

vec3_t vec3_rotate_x(vec3_t vec, float angle) {
  vec3_t rotated = {.x = vec.x,
                    .y = vec.y * cos(angle) - vec.z * sin(angle),
                    .z = vec.z * cos(angle) + vec.y * sin(angle)};
  return rotated;
}

vec3_t vec3_rotate_y(vec3_t vec, float angle) 
{ 
    vec3_t rotated = 
    {
        .x = vec.x * cos(angle) - vec.z * sin(angle),
        .y = vec.y,
        .z = vec.z * cos(angle) + vec.x * sin(angle)
    };
    return rotated; 
}
