#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    float x;
    float y;
}vec2_t;

typedef struct
{
    float x;
    float y;
    float z;
}vec3_t;

/// Vector2D
float vec2_length(vec2_t v);
float vec2_length_squared(vec2_t v);
vec2_t vec2_add(vec2_t a,vec2_t b);
vec2_t vec2_sub(vec2_t a,vec2_t b);
vec2_t vec2_mult(vec2_t a,vec2_t b);

/// Vector3D 
float vec3_length(vec3_t v);
float vec3_length_squared(vec3_t v);

vec3_t vec3_add(vec3_t a , vec3_t b);
vec3_t vec3_sub(vec3_t a , vec3_t b);
vec3_t vec3_mult(vec3_t a , vec3_t b);
vec3_t vec3_projection(vec3_t v);
vec3_t vec3_rotate_x(vec3_t vec,float angle);
vec3_t vec3_rotate_y(vec3_t vec,float angle);
vec3_t vec3_rotate_z(vec3_t vec,float angle);

#endif
