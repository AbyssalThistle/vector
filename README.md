# vector

Vector implementation based on
[Sean Barrett's implementation](http://nothings.org/stb/stretchy_buffer.txt)
allocates two `vecsize_t` before the user pointer to track `size` and `capacity`.
typedef `vecsize_t` to suit your project.

## usage
Null pointers to a type are initilisation.

push elements with `vec_push(T, v, d)` where:
* `T` is the type
* `v` is the pointer to a variable of that type
* `d` is the data

single elements can be removed with `vec_pop(v)`.

access/change elements with `[]`, as you would an array.
