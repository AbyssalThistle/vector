# vector

Vector implementation based on
[Sean Barrett's implementation](http://nothings.org/stb/stretchy_buffer.txt)
allocates two `vecsize_t` before the user pointer to track `size` and `capacity`.
typedef `vecsize_t` to suit your project.

## usage
Null pointers to a type are initilisation.

push elements with `VEC_PUSH(T, v, d)` where:
* `T` is the type
* `v` is the pointer to a variable of that type
* `d` is the data

single elements can be removed with `VEC_POP(v)` or `VEC_POP_AT(v, n)`
size and capacity macros are available with `VEC_SIZE(v)` and `VEC_CAP(v)`

access/change elements with `[]`, as you would an array.
