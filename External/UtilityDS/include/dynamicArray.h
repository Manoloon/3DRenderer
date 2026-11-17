#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef enum dynArr_code_e
{
    SUCCESS,
    INVALID_ARGUMENT,
    ALREADY_INIT,
    MEM_OVERFLOW,
    OUT_OF_MEMORY
}dynArr_code_e;

typedef struct dynarray_s dynarray_t;

dynarray_t* dynArray_create(size_t itemSize);
size_t dynArray_get_length(dynarray_t* array);
// copia superficial : offset = size * item_size -> destino = items + offset : 

// casos de borde : 
/*
    1 - el vector esta lleno : duplicar capacidad y luego insertar
    2 - falla realloc : el vector debe conservar su estado anterior
    3 - elemento de origen pertenece al propio vector : por el momento no permitir esto .
    4 - 
*/
uint8_t dynArray_push_back(dynarray_t* array,const void* item);
size_t dynArray_get_capacity(dynarray_t* array);

void* dynArray_get_items(dynarray_t* array);
// devuelve puntero del item en indice index;
// solo valido si no se realizo ninguna operacion que modifica el conjunto.

void* dynArray_get_item(dynarray_t* array,size_t index);
//void set_item(dynarray_t* array,int index,void* newData);
//void* pop_back(dynarray_t* array);
//void remove(dynarray_t* array,int index);
//void resize(dynarray_t* array,size_t new_size);
//void reserve(dynarray_t* array, size_t size);
// Clear the array should left the array with 0 items , items as NULL 
// but the capacity and the item_size untouch , because we need it to
// reused.
uint8_t dynArray_clear(dynarray_t* array);

uint8_t dynArray_free(dynarray_t** array);

#endif