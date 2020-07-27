#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define VEC_INITIAL_CAP 4
#define VEC_SCALE_FAC 2

typedef uint16_t vecsize_t;

#define _vec_head(v) ((vecsize_t *)(v)-2)
#define vec_size(v) ((v == NULL) ? 0 : _vec_head(v)[0])
#define vec_cap(v) ((v == NULL) ? 0 : _vec_head(v)[1])
#define vec_null_check(v) assert(v)

#define vec_push(T, v, d) \
do { \
	if (!v) { \
		v = malloc((sizeof(T) * VEC_INITIAL_CAP) + (2 * sizeof(vecsize_t))); \
		vec_null_check(v); \
		((vecsize_t *)(v))[0] = 1; \
		((vecsize_t *)(v))[1] = VEC_INITIAL_CAP; \
		v = (vecsize_t *)v + 2; \
		v[0] = d; \
		break; \
	} \
	if(vec_size(v) == vec_cap(v)) { \
		v = _vec_head(v); \
		v = realloc(v, (sizeof(T) *((vecsize_t *)(v))[1] * VEC_SCALE_FAC) + (2 * sizeof(vecsize_t))); \
		vec_null_check(v); \
		((vecsize_t *)(v))[1] *= VEC_SCALE_FAC; \
		v = (vecsize_t *)v + 2; \
	} \
	v[vec_size(v)] = d; \
	_vec_head(v)[0] += 1; \
} while(0);

#define vec_free(v) \
do { \
	free(_vec_head(v)); \
	v = NULL; \
} while(0);

#define vec_pop(v) \
do { \
	_vec_head(v)[0] -= 1; \
} while(0);
