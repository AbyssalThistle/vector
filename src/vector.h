#include <stdio.h>
#include <malloc.h>
#define VEC_DEFAULT_CAPACITY 4
#define VEC_REALLOC reallocarray
#define VEC_GENERATE_TYPE(TYPE) VEC_GENERATE_NAME(TYPE, TYPE) 
#define VEC_GENERATE_NAME(TYPE, NAME) \
typedef struct { \
	int size; \
	int capacity; \
	size_t data_size; \
	TYPE *data; \
} Vec##NAME; \
Vec##NAME * \
vecInitWCap##NAME(unsigned int capacity) \
{ \
	Vec##NAME *v = malloc(sizeof(Vec##NAME)); \
	if ( v == NULL ){ \
		fprintf(stderr, "%s malloc of vec failed\n", __FUNCTION__); \
		return NULL; \
	} \
	v->data = malloc(sizeof(TYPE) * capacity); \
	if ( v->data == NULL ){ \
		fprintf(stderr, "%s malloc of vec data failed\n", __FUNCTION__); \
		return NULL; \
	} \
	v->size = 0; \
	v->capacity = capacity; \
	v->data_size = sizeof(TYPE); \
	return v; \
} \
Vec##NAME* \
vecInit##NAME() \
{ \
	return vecInitWCap##NAME(VEC_DEFAULT_CAPACITY); \
} \
TYPE \
vecAt##NAME(Vec##NAME *v, unsigned int pos) \
{ \
	if(pos >= v->size) { \
		fprintf(stderr, "%s can't hit pos %d, size is %d\n", \
				__FUNCTION__, pos, v->size); \
		return v->data[0]; \
	} \
	return v->data[pos]; \
} \
TYPE * \
vecPtr##NAME(Vec##NAME *v, unsigned int pos) \
{ \
	if(pos >= v->size) { \
		fprintf(stderr, "%s can't hit pos %d, size is %d\n", \
				__FUNCTION__, pos, v->size); \
		return NULL; \
	} \
	return v->data + pos; \
} \
void \
vecPush##NAME(Vec##NAME *v, TYPE value) \
{ \
	if(v->size == v->capacity) { \
		void* tmp = VEC_REALLOC(v->data, v->capacity * 2, sizeof(TYPE)); \
		if(!tmp) { fprintf(stderr, "%s realloc failed!", __FUNCTION__); } \
		v->data = tmp; \
		v->capacity *= 2; \
	} \
	v->data[v->size] = value; \
	v->size += 1; \
} \
void \
vecSet##NAME(Vec##NAME *v, unsigned int pos, TYPE value) \
{ \
	if(pos >= v->size) { \
		fprintf(stderr, "%s can't hit %d, size is %d", \
			__FUNCTION__, pos, v->size); \
	} \
	v->data[pos] = value; \
} \
TYPE \
vecPop##NAME(Vec##NAME *v) \
{ \
	if(v->size == 0) { \
		fprintf(stderr, "%s underflow\n", __FUNCTION__); \
		return v->data[0]; \
	} \
	v->size--; \
	return v->data[v->size]; \
} \
void \
vecFree##NAME(Vec##NAME *v)  \
{ \
	free(v->data); \
	v->data = NULL; \
	free(v); \
	v = NULL; \
}
