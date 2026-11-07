#include "vector.h"
#include <math.h>

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
