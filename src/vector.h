#include <stdio.h>
#define VEC_DEFAULT_CAPACITY 4
#define VEC_REALLOC reallocarray
#define VEC_GENERATE_TYPE(TYPE) VEC_GENERATE_NAME(TYPE, TYPE) 
#define VEC_GENERATE_NAME(TYPE, NAME) \
typedef struct { \
	int size; \
	int capacity; \
	size_t data_size; \
	TYPE *data; \
} vec_##NAME; \
vec_##NAME * \
vec_init_w_cap_##NAME(unsigned int capacity) \
{ \
	vec_##NAME *v = malloc(sizeof(vec_##NAME)); \
	if ( v == NULL ){ \
		fprintf(stderr, "%s malloc of vec failed\n", __FUNCTION__); \
		return NULL; \
	} \
	v->data = malloc(sizeof(TYPE)); \
	if ( v->data == NULL ){ \
		fprintf(stderr, "%s malloc of vec data failed\n", __FUNCTION__); \
		return NULL; \
	} \
	v->size = 0; \
	v->capacity = capacity; \
	v->data_size = sizeof(TYPE); \
	return v; \
} \
vec_##NAME* \
vec_init_##NAME() \
{ \
	return vec_init_w_cap_##NAME(VEC_DEFAULT_CAPACITY); \
} \
TYPE \
vec_at_##NAME(vec_##NAME *v, unsigned int pos) \
{ \
	if(pos >= v->size) { \
		fprintf(stderr, "%s can't hit pos %d, size is %d\n", \
				__FUNCTION__, pos, v->size); \
		return 0; \
	} \
	return v->data[pos]; \
} \
TYPE * \
vec_ptr_##NAME(vec_##NAME *v, unsigned int pos) \
{ \
	if(pos >= v->size) { \
		fprintf(stderr, "%s can't hit pos %d, size is %d\n", \
				__FUNCTION__, pos, v->size); \
		return NULL; \
	} \
	return v->data + pos; \
} \
void \
vec_push_##NAME(vec_##NAME *v, TYPE value) \
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
vec_set_##NAME(vec_##NAME *v, unsigned int pos, TYPE value) \
{ \
	if(pos >= v->size) { \
		fprintf(stderr, "%s can't hit %d, size is %d", \
			__FUNCTION__, pos, v->size); \
	} \
	v->data[pos] = value; \
} \
TYPE \
vec_pop_##NAME(vec_##NAME *v) \
{ \
	if(v->size == 0) { \
		fprintf(stderr, "%s underflow\n", __FUNCTION__); \
		return 0; \
	} \
	v->size--; \
	return v->data[v->size]; \
} \
void \
vec_free_##NAME(vec_##NAME *v)  \
{ \
	free(v->data); \
	v->data = NULL; \
	free(v); \
	v = NULL; \
}
