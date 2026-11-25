#include "parser.h"
#include "triangle.h"
#include <stdlib.h>
void parse_face(const char *input,mesh_t* in_mesh)
{
    face_t face;
    const int type = 10;
    char *endptr = NULL;
    // face
    face.a = strtol(input + 2, &endptr, type);
    face.b = strtol(endptr + 1, &endptr, type);
    face.c = strtol(endptr + 1, &endptr, type);

    // face.v2.a = strtol(endptr + 1, &endptr, type);
    // face.v2.b = strtol(endptr + 1, &endptr, type);
    // face.v2.c = strtol(endptr + 1, &endptr, type);

    // face.v3.a = strtol(endptr + 1, &endptr, type);
    // face.v3.b = strtol(endptr + 1, &endptr, type);
    // face.v3.c = strtol(endptr + 1, &endptr, type);

    //printf("face v1 a:%d, b=%d, c:%d\n", face.v1.a, face.v1.b, face.v1.c);
    //printf("face v2 a:%d, b=%d, c:%d\n", face.v2.a, face.v2.b, face.v2.c);
    //printf("face v3 a:%d, b=%d, c:%d\n", face.v3.a, face.v3.b, face.v3.c);
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
    size_t size = dynArray_get_length(input);
    const char *items = dynArray_get_items(input);
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
    }
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
