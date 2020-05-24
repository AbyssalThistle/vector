#pragma once
#include <stdlib.h>

typedef struct {
	size_t count;
	size_t capacity;
	void** data;
} Vector;

void vector_init(Vector* v);
int vector_count(Vector* v);
void *vector_get(Vector *v, int index);
void vector_set(Vector* v, int index, void* data);
void vector_push(Vector* v, void* data);
void vector_pop(Vector* v);
void vector_pop_at(Vector *v, int index);
void vector_free(Vector *v);
