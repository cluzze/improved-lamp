#include "solution.h"

#include "myassert.h"
#include "vector.h"
#include "permutation.h"

void get_triplets(Vector *vec, Vector *triplets)
{
	MYASSERT(vec)
	MYASSERT(triplets)

	int i = 0, j = 0;

	for (i = 0; i < 3; ++i)
	{
		set_el_vector(triplets, i, vec->data[i]);
	}

	set_el_vector(triplets, triplets->size - 3, vec->data[vec->size - 1]);
	set_el_vector(triplets, triplets->size - 2, vec->data[vec->size - 2]);
	set_el_vector(triplets, triplets->size - 1, vec->data[1]);

	for (i = 3, j = 3; i < (int)vec->size - 1; i += 2)
	{
		set_el_vector(triplets, j++, vec->data[i]);
		set_el_vector(triplets, j++, vec->data[i - 1]);
		set_el_vector(triplets, j++, vec->data[i + 1]);
	}

}

int check_sum(Vector *triplets)
{
	MYASSERT(triplets)

	size_t i = 0;
	int sum = -1, cur_sum = 0;

	for (i = 0; i < triplets->size; i += 3)
	{
		cur_sum = triplets->data[i] +
				  triplets->data[i + 1] +
				  triplets->data[i + 2];
		if (sum == -1) sum = cur_sum;
		else if (sum != cur_sum) return 0; 
	}

	return 1;
}

int get_hash(int a, int b, int c, int n)
{
	return a * (n + 1) * (n + 1) +
		   b * (n + 1) +
		   c;
}

int check_used(Vector *triplets, Vector *used)
{
	MYASSERT(triplets)
	MYASSERT(used)

	size_t i = 0;
	Vector hash;

	init_vector(&hash, triplets->size / 3);

	for (i = 0; i < triplets->size; i += 3)
	{
		hash.data[i / 3] = get_hash(triplets->data[i],
							   		triplets->data[i + 1],
							   		triplets->data[i + 2],
							   		2 * triplets->size / 3);

		if (used->data[hash.data[i / 3]] == 1)
		{
			destroy_vector(&hash);
			return 0;
		}
	}

	for (i = 0; i < hash.size; ++i)
	{
		used->data[hash.data[i]] = 1;
	}

	destroy_vector(&hash);

	return 1;
}

void perm_solve(Vector *vec, Vector *triplets, Vector *used, Vector2d *solutions)
{
	do
	{
		get_triplets(vec, triplets);
		if (check_sum(triplets) && check_used(triplets, used))
		{
			push_back_vector2d(solutions, triplets);
		}
	} while (next_permutation(vec));
}