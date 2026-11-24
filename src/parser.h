#ifndef PARSER_H
#define PARSER_H
#include "dynamicArray.h"
#include "mesh.h"
#include <stdbool.h>
#include <stdio.h>

void parse_face(const char *input,mesh_t* in_mesh);

void parse_vertex(const char *input,mesh_t* in_mesh);

void parse_line(dynarray_t *input,mesh_t* in_mesh);

bool start_parsing(FILE *file,mesh_t* in_mesh);
#endif