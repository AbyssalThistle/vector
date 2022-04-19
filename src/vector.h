#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
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

#define VEC_PUSH_STR(v, d) \
do { \
	if (!v) { \
		v = malloc((sizeof(char *) * VEC_INITIAL_CAP) + (2 * sizeof(vecsize_t))); \
		VEC_NULL_CHECK(v); \
		((vecsize_t *)(v))[0] = 1; \
		((vecsize_t *)(v))[1] = VEC_INITIAL_CAP; \
		v = (vecsize_t *)v + 2; \
		v[0] = malloc(strlen(d) + 1); \
		strncpy(v[0], d, strlen(d) + 1); \
		break; \
	} \
	if(VEC_SIZE(v) == VEC_CAP(v)) { \
		v = _VEC_HEAD(v); \
		v = realloc(v, (sizeof(char *) *((vecsize_t *)(v))[1] * VEC_SCALE_FAC) + (2 * sizeof(vecsize_t))); \
		VEC_NULL_CHECK(v); \
		((vecsize_t *)(v))[1] *= VEC_SCALE_FAC; \
		v = (vecsize_t *)v + 2; \
	} \
	v[VEC_SIZE(v)] = malloc(strlen(d) + 1); \
	strncpy(v[VEC_SIZE(v)], d, strlen(d) + 1); \
	_VEC_HEAD(v)[0] += 1; \
} while(0);

#define VEC_PUSH_NSTR(v, d, n) \
do { \
	unsigned int len = n; \
	if (d[n] != '\0') { len += 1; } \
	if (!v) { \
		v = malloc((sizeof(char *) * VEC_INITIAL_CAP) + (2 * sizeof(vecsize_t))); \
		VEC_NULL_CHECK(v); \
		((vecsize_t *)(v))[0] = 1; \
		((vecsize_t *)(v))[1] = VEC_INITIAL_CAP; \
		v = (vecsize_t *)v + 2; \
		v[0] = malloc(len); \
		strncpy(v[0], d, n); \
		v[len] = '\0'; \
		break; \
	} \
	if(VEC_SIZE(v) == VEC_CAP(v)) { \
		v = _VEC_HEAD(v); \
		v = realloc(v, (sizeof(char *) *((vecsize_t *)(v))[1] * VEC_SCALE_FAC) + (2 * sizeof(vecsize_t))); \
		VEC_NULL_CHECK(v); \
		((vecsize_t *)(v))[1] *= VEC_SCALE_FAC; \
		v = (vecsize_t *)v + 2; \
	} \
	v[VEC_SIZE(v)] = malloc(len); \
	strncpy(v[VEC_SIZE(v)], d, n); \
	v[len] = '\0'; \
	_VEC_HEAD(v)[0] += 1; \
} while(0);

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
	v[_VEC_HEAD(v)[0]] = d; \
	_VEC_HEAD(v)[0] += 1; \
} while(0);

#define VEC_FREE_STR(v) \
do { \
	for(int _i = 0; _i < _VEC_HEAD(v)[0]; ++_i) { \
		free(v[_i]); \
		v[_i] = NULL; \
	} \
	free(_VEC_HEAD(v)); \
	v = NULL; \
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
	for(int _i = at; _i < _VEC_HEAD(v)[0] - 1; ++_i) { \
		v[_i] = v[_i+1]; \
	} \
	_VEC_HEAD(v)[0] -= 1; \
	if(_VEC_HEAD(v)[0] == 0) { VEC_FREE(v) } \
} while(0);

#define VEC_POP_STR(v) \
do { \
	free(v[_VEC_HEAD(v)[0] - 1]); \
	_VEC_HEAD(v)[0] -= 1; \
	if(_VEC_HEAD(v)[0] == 0) { VEC_FREE(v) } \
} while(0);

#define VEC_SET_STR(v, at) \
do { \
	free(v[at]); \
	v[at] = malloc(strlen(v)); \
	strcpy(v[at], v); \
} while(0);

#define VEC_POP_STR_AT(v, at) \
do { \
	free(v[at]); \
	for(int _i = at; _i < _VEC_HEAD(v)[0] - 1; ++_i) { \
		v[_i] = v[_i+1]; \
	} \
	_VEC_HEAD(v)[0] -= 1; \
	if(_VEC_HEAD(v)[0] == 0) { VEC_FREE(v) } \
} while(0);

#pragma GCC diagnostic pop
