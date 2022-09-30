#ifndef _VECTOR_
#define _VECTOR_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myassert.h"

typedef struct
{
	size_t size;
	size_t capacity;
	int *data;
} Vector;

typedef struct
{
	size_t size;
	size_t capacity;
	Vector *data;
} Vector2d;

void init_vector(Vector *vec, size_t size);

void fill_vector(Vector *vec);

void set_el_vector(Vector *vec, size_t id, int el);

void push_back_vector(Vector *vec, int el);

void pop_back_vector(Vector *vec);

void destroy_vector(Vector *vec);

void print_vector(FILE *fd, Vector *vec);

void init_vector2d(Vector2d *vec, size_t nvecs, size_t size);

void set_el_vector2d(Vector2d *vec, size_t id1, size_t id2, int el);

void push_back_vector2d(Vector2d *vec, Vector *el);

void print_vector2d(FILE *fd, Vector2d *vec);

void destroy_vector2d(Vector2d *vec);

#endif