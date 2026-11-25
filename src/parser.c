#include "parser.h"
#include "triangle.h"
#include <string.h>
#include <stdlib.h>
void parse_face(const char *input,mesh_t* in_mesh)
{
    face_t face;
    // const int type = 10;
    //char *endptr = NULL;
    int vertex_index[3];
    int texture_index[3];
    int normal_index[3];
    // face
    sscanf(input,"f  %d/%d/%d %d/%d/%d %d/%d/%d",
        &vertex_index[0],&texture_index[0],&normal_index[0],
        &vertex_index[1],&texture_index[1],&normal_index[1],
        &vertex_index[2],&texture_index[2],&normal_index[2]);
    dynArray_push_back(in_mesh->faces, &face);
}

void parse_vertex(const char *input,mesh_t* in_mesh)
{
    vec3_t vector;
    char *endptr = NULL;
    vector.x = strtof(input + 2, &endptr);
    vector.y = strtof(endptr, &endptr);
    vector.z = strtof(endptr, &endptr);
    //vector.w = strtof(endptr,&endptr);
    //printf("x:%.2f, y=%.2f, z:%.2f, w:%.2f\n", vector.x, vector.y, vector.z,vector.w);
    dynArray_push_back(in_mesh->vertices, &vector);
}

void parse_line(dynarray_t *input,mesh_t* in_mesh)
{
    if (input == NULL)
    {
        fprintf(stderr, "input is NULL\n");
        return;
    }
    //size_t size = dynArray_get_length(input);
    const char *items = dynArray_get_items(input);
    // vertex
    if(strncmp(items,"v ",2))
    {
        parse_vertex(items,in_mesh);
    }
    else if (strncmp(items,"f ",2))
    {
        parse_face(items,in_mesh);
    }
    /*
    if (size > 2)
    {
        // vertex
        switch (items[0])
        {
        case 'v':
            if (items[1] == ' ')
            {
                parse_vertex(items,in_mesh);
            }
            break;
        case 'f':
            if (items[1] == ' ')
            {
                parse_face(items,in_mesh);
            }
            break;
        default:
            break;
        }
    }*/
    dynArray_clear(input);
}

bool start_parsing(FILE *file, mesh_t* in_mesh)
{
    if(in_mesh == NULL)
    {
        fprintf(stderr,"Start_parcing: mesh is NULL\n");
        return false;
    }
    in_mesh->vertices = dynArray_create(sizeof(vec3_t));
    in_mesh->faces = dynArray_create(sizeof(face_t));

    int ch = 0;
    int parsing = 1;
    dynarray_t *line_buffer = dynArray_create(sizeof(char));
    if (line_buffer == NULL)
    {
        fprintf(stderr, "line_buffer push_back failed\n");
        return false;
    }
    // lectura char por char
    while (parsing == 1)
    {
        // avanza automaticamente character por character
        ch = fgetc(file);
        if (ch == EOF)
        {
            parsing = 0;
            continue;
        }
        if (ch != '\n')
        {
            if (dynArray_push_back(line_buffer, &ch) != SUCCESS)
            {
                fprintf(stderr, "line_buffer push_back failed\n");
                return false;
            }
        }
        else
        {
            char end = '\0';
            dynArray_push_back(line_buffer, &end);
            parse_line(line_buffer,in_mesh);
        }
    }
    dynArray_free(&line_buffer);
    return true;
}
