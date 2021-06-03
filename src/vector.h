#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#ifndef VEC_INITIAL_CAP
	#define VEC_INITIAL_CAP 4
#endif

#ifndef VEC_SCALE_FAC
	#define VEC_SCALE_FAC 2
#endif

#ifndef VEC_SIZE_TYPE
	#define VEC_SIZE_TYPE uint16_t
#endif

typedef VEC_SIZE_TYPE vecsize_t;

#define _VEC_HEAD(v) ((vecsize_t *)(v)-2)
#define VEC_SIZE(v) ((v == NULL) ? 0 : _VEC_HEAD(v)[0])
#define VEC_CAP(v) ((v == NULL) ? 0 : _VEC_HEAD(v)[1])
#define VEC_NULL_CHECK(v) assert(v)

#define VEC_PUSH(T, v, d) \
do { \
	if (!v) { \
		v = malloc((sizeof(T) * VEC_INITIAL_CAP) + (2 * sizeof(vecsize_t))); \
		VEC_NULL_CHECK(v); \
		((vecsize_t *)(v))[0] = 1; \
		((vecsize_t *)(v))[1] = VEC_INITIAL_CAP; \
		v = (vecsize_t *)v + 2; \
		v[0] = d; \
		break; \
	} \
	if(VEC_SIZE(v) == VEC_CAP(v)) { \
		v = _VEC_HEAD(v); \
		v = realloc(v, (sizeof(T) *((vecsize_t *)(v))[1] * VEC_SCALE_FAC) + (2 * sizeof(vecsize_t))); \
		VEC_NULL_CHECK(v); \
		((vecsize_t *)(v))[1] *= VEC_SCALE_FAC; \
		v = (vecsize_t *)v + 2; \
	} \
	v[VEC_SIZE(v)] = d; \
	_VEC_HEAD(v)[0] += 1; \
} while(0);

#define VEC_FREE(v) \
do { \
	free(_VEC_HEAD(v)); \
	v = NULL; \
} while(0);

#define VEC_POP(v) \
do { \
	_VEC_HEAD(v)[0] -= 1; \
	if(_VEC_HEAD(v)[0] == 0) { VEC_FREE(v) } \
} while(0);

#define VEC_POP_AT(v, at) \
do { \
	for(int i = at; i < _VEC_HEAD(v)[0] - 1; ++i) { \
		v[i] = v[i+1]; \
	} \
	_VEC_HEAD(v)[0] -= 1; \
	if(_VEC_HEAD(v)[0] == 0) { VEC_FREE(v) } \
} while(0);
