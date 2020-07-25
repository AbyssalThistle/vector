#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define VEC_INITIAL_CAP 4
#define VEC_SCALE_FAC 2

typedef uint16_t vecsize_t;

//vecsize_t vec_count(void* v);
//void vec_push(void* v, void* data);
//void vec_free(void *v);

#define vec_cap(v) *((vecsize_t *)(v-1))
#define vec_size(v) *((vecsize_t *)(v-2))
#define vec_null_check(v) assert(v)

#define vec_push(T, v, d) \
do { \
	if (!v) { \
		v = malloc((sizeof(T) * VEC_INITIAL_CAP) + (2 * sizeof(vecsize_t))); \
		vec_null_check(v); \
		*((vecsize_t *)v) = 1; \
		*((vecsize_t *)(v + 1)) = VEC_INITIAL_CAP; \
		*((vecsize_t *)v) += 2; \
		v[0] = d; \
		break; \
	} \
	if(vec_size(v) == vec_cap(v)) { \
		v = realloc(v,(sizeof(T) * vec_cap(v) * VEC_SCALE_FAC) + \
				2 * sizeof(vecsize_t)); \
		vec_null_check(v); \
	} \
	v[vec_size(v)] = d; \
	vec_size(v) += 1; \
} while(0);

#define vec_free(v) \
do { \
	(vecsize_t) *header = &v[-2]; \
	free(header); \
	v = NULL; \
} while(0);

#define vec_pop(v) \
do { \
	vec_size(v) -= 1; \
} while(0);
