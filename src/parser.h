#ifndef PARSER_H
#define PARSER_H
#include "mesh.h"
#include <stdbool.h>

void parse_face(const char *input,mesh_t* in_mesh);

void parse_vertex(const char *input,mesh_t* in_mesh);

bool start_parsing(const char* filename,mesh_t* in_mesh);
#endif