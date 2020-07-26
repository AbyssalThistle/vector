#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#define VEC_INITIAL_CAP 4
#define VEC_SCALE_FAC 2

typedef uint16_t vecsize_t;

#define _vec_head(v) ((vecsize_t *)(v)-2)
#define vec_size(v) _vec_head(v)[0]
#define vec_cap(v) _vec_head(v)[1]
#define vec_null_check(v) assert(v)

#define vec_push(T, v, d) \
do { \
	if (!v) { \
		v = malloc((sizeof(T) * VEC_INITIAL_CAP) + (2 * sizeof(vecsize_t))); \
		vec_null_check(v); \
		((vecsize_t *)(v))[0] = 1; \
		((vecsize_t *)(v))[1] = VEC_INITIAL_CAP; \
		printf("%s vec is at %p\n", #T, v); \
		v = (vecsize_t *)v + 2; \
		printf("head is at %p, ", ((vecsize_t *)(v)-2) ); \
		printf("content is at %p, ", v); \
		printf("size is %u and cap is %u\n", vec_size(v), vec_cap(v)); \
		v[0] = d; \
		break; \
	} \
	if(vec_size(v) == vec_cap(v)) { \
		printf("%s vec is %p - ", #T, v); \
		v = _vec_head(v); \
		printf("head is %p\n", v); \
		v = realloc(v,(sizeof(T) * vec_cap(v) * VEC_SCALE_FAC) + (2 * sizeof(vecsize_t))); \
		vec_null_check(v); \
		v = (vecsize_t *)v + 2; \
	} \
	printf("biz "); \
	v[vec_size(v)] = d; \
	vec_size(v) += 1; \
} while(0);

#define vec_free(v) \
do { \
	free(_vec_head(v)); \
	_vec_head(v) = NULL; \
	v = NULL; \
} while(0);

#define vec_pop(v) \
do { \
	vec_size(v) -= 1; \
} while(0);
