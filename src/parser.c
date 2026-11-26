#include "parser.h"
#include "triangle.h"
#include <string.h>
#include <stdlib.h>
void parse_face(const char *input,mesh_t* in_mesh)
{
    face_t face;
    // const int type = 10;
    //char *endptr = NULL;
    //int vertex_index[3];
    int texture_index[3];
    int normal_index[3];
    // face
    sscanf(input,"f  %d/%d/%d %d/%d/%d %d/%d/%d",
        &face.a,&texture_index[0],&normal_index[0],
        &face.b,&texture_index[1],&normal_index[1],
        &face.c,&texture_index[2],&normal_index[2]);
    dynArray_push_back(in_mesh->faces, &face);
}

void parse_vertex(const char *input,mesh_t* in_mesh)
{
    vec3_t vertex;
    sscanf(input,"v %f %f %f",&vertex.x,&vertex.y,&vertex.z);
    // char *endptr = NULL;
    // vertex.x = strtof(input + 2, &endptr);
    // vertex.y = strtof(endptr, &endptr);
    // vertex.z = strtof(endptr, &endptr);
    //vector.w = strtof(endptr,&endptr);
    
    dynArray_push_back(in_mesh->vertices, &vertex);
}

bool start_parsing(const char* filename, mesh_t* in_mesh)
{
    FILE* file = fopen(filename,"r");
    if(in_mesh == NULL)
    {
        fprintf(stderr,"Start_parcing: mesh is NULL\n");
        return false;
    }
    in_mesh->vertices = dynArray_create(sizeof(vec3_t));
    in_mesh->faces = dynArray_create(sizeof(face_t));

    char buffer[1024];

    while (fgets(buffer,sizeof(buffer),file))
    {
            // vertex
        if(strncmp(buffer,"v ",2) == 0)
        {
            parse_vertex(buffer,in_mesh);
        }
        if(strncmp(buffer,"f ",2) == 0)
        {
            parse_face(buffer,in_mesh);
        }
    }
    return true;
}
