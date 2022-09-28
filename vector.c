#include "vector.h"

void init_vector(Vector *vec, size_t size)
{
	MYASSERT(vec)

	vec->size = size;
	vec->capacity = vec->size * 2;

	if (vec->capacity == 0) vec->capacity += 2;

	vec->data = (int*)calloc(vec->capacity, sizeof(int));
}

void fill_vector(Vector *vec)
{
	MYASSERT(vec)

	size_t i = 0;

	for (i = 0; i < vec->size; ++i)
	{
		vec->data[i] = (int)i + 1;
	}
}

void set_el_vector(Vector *vec, size_t id, int el)
{
	MYASSERT(vec)
	MYASSERT(id < vec->size)

	vec->data[id] = el;
}

void push_back_vector(Vector *vec, int el)
{
	MYASSERT(vec)

	if (vec->size == vec->capacity)
	{
		vec->capacity *= 2;
		vec->data = (int*)realloc(vec->data, vec->capacity * sizeof(int));
		memset(vec->data + vec->size, 0, vec->size * sizeof(int));
	}

	vec->data[vec->size++] = el;
}

void destroy_vector(Vector *vec)
{
	MYASSERT(vec)

	free(vec->data);
}

void print_vector(FILE *fd, Vector *vec)
{
	MYASSERT(fd)
	MYASSERT(vec)

	size_t i = 0;

	for (i = 0; i < vec->size - 1; ++i)
	{
		fprintf(fd, "%d, ", vec->data[i]);
	}
	fprintf(fd, "%d\n", vec->data[i]);
}

void init_vector2d(Vector2d *vec, size_t nvecs, size_t size)
{
	MYASSERT(vec)

	size_t i = 0;

	vec->size = nvecs;
	vec->capacity = vec->size * 2;

	if (vec->capacity == 0) vec->capacity += 2;

	vec->data = (Vector*)calloc(vec->capacity, sizeof(Vector));

	for (i = 0; i < vec->capacity; ++i)
		init_vector(&vec->data[i], size);

}

void set_el_vector2d(Vector2d *vec, size_t id1, size_t id2, int el)
{
	MYASSERT(vec)
	MYASSERT(id1 < vec->size)
	MYASSERT(id2 < vec->data[id1].size)

	vec->data[id1].data[id2] = el;
}

void push_back_vector2d(Vector2d *vec, Vector *el)
{
	MYASSERT(vec)
	MYASSERT(el)

	size_t i = 0;

	if (vec->size == vec->capacity)
	{
		vec->capacity *= 2;
		vec->data = (Vector*)realloc(vec->data, vec->capacity * sizeof(Vector));

		for (i = vec->size; i < vec->capacity; ++i)
			init_vector(&vec->data[i], el->size);
	}

	vec->data[vec->size].size = el->size;
	for (i = 0; i < el->size; ++i)
	{
		vec->data[vec->size].data[i] = el->data[i];
	}
	vec->size++;
}

void print_vector2d(FILE *fd, Vector2d *vec)
{
	MYASSERT(fd)
	MYASSERT(vec)

	size_t i = 0;

	for (i = 0; i < vec->size; ++i)
	{
		print_vector(fd, &vec->data[i]);
	}
}

void destroy_vector2d(Vector2d *vec)
{
	MYASSERT(vec)

	size_t i = 0;

	for (i = 0; i < vec->capacity; ++i)
	{
		destroy_vector(&vec->data[i]);
	}

	free(vec->data);
}