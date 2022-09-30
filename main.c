#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"
#include "permutation.h"
#include "solution.h"

void despair(Vector *krug, Vector *vec, int sum, int n, Vector *used, Vector2d *solutions)
{
	int i = 0;
	int cur_el = 0;

	if ((int)krug->size == n)
	{
		cur_el = sum - (krug->data[krug->size - 1] + krug->data[0]);

		if (cur_el < 1 || cur_el > 2 * n) return;

		if (used->data[cur_el] == 0)
		{
			Vector sol;
			init_vector(&sol, 0);
			for (i = 0; i < (int)krug->size - 1; ++i)
			{
				push_back_vector(&sol, vec->data[i]);
				push_back_vector(&sol, krug->data[i]);
				push_back_vector(&sol, krug->data[i + 1]);
			}
			push_back_vector(&sol, cur_el);
			push_back_vector(&sol, krug->data[i]);
			push_back_vector(&sol, krug->data[0]);

			push_back_vector2d(solutions, &sol);
			destroy_vector(&sol);
		}
		return;
	}
	for (i = 1; i <= 2 * n; ++i)
	{
		cur_el = sum - (i + krug->data[krug->size - 1]);

		if (cur_el < 1 || cur_el > 2 * n) continue;

		if (cur_el != i && used->data[i] == 0 && used->data[cur_el] == 0)
		{
			push_back_vector(krug, i);
			push_back_vector(vec, cur_el);
			used->data[i] = used->data[cur_el] = 1;

			despair(krug, vec, sum, n, used, solutions);
			
			pop_back_vector(krug);
			pop_back_vector(vec);
			used->data[i] = used->data[cur_el] = 0;
		}
	}
}

void fun(Vector *krug, Vector *vec, int n, Vector *used, Vector2d *solutions)
{
	int i = 0, j = 0, k = 0;

	for (i = 1; i <= 2 * n; ++i)
	{
		for (j = 1; j <= 2 * n; ++j)
		{
			if (i != j)
			{
				used->data[i] = used->data[j] = 1;
				push_back_vector(krug, i);
				push_back_vector(krug, j);

				for (k = 1; k <= 2 * n; ++k)
				{
					if (k != i && k != j)
					{
						used->data[k] = 1;
						push_back_vector(vec, k);
						despair(krug, vec, i + j + k, n, used, solutions);
						pop_back_vector(vec);
						used->data[k] = 0;
					}
				}
				pop_back_vector(krug);
				pop_back_vector(krug);
				used->data[i] = used->data[j] = 0;
			}
		}
	}
}

int perm_cmp(const void *a, const void *b)
{
	Vector *v1 = (Vector*)a;
	Vector *v2 = (Vector*)b;

	int i = 0;
	for (i = 0; i < (int)v1->size; ++i)
		if (v1->data[i] != v2->data[i])
			return v1->data[i] - v2->data[i];

	return 0;
}

void get_unique_solutions(Vector2d *solutions, Vector2d *unique_solutions)
{
	int i = 0, j = 0, k = 0;
	int id1 = 0, id2 = 0;
	int size = 0;
	int unique = 0;

	for (i = (int)solutions->size - 1; i >= 1; --i)
	{
		size = solutions->data[i].size;
		unique = 1;

		for (j = i - 1; j >= 0; --j)
		{
			k = -1;

			for (k = 0; k < size && 
					solutions->data[i].data[0] != solutions->data[j].data[k]; ++k)
				;

			id1 = 1;
			id2 = (k + 1) % size;
			while (id1 != 0 && solutions->data[i].data[id1] ==
							   solutions->data[j].data[id2])
			{
				id1 = (id1 + 1) % size;
				id2 = (id2 + 1) % size;
			}

			if (id1 == 0)
			{
				unique = 0;
			}
		}
		if (unique)
		{
			push_back_vector2d(unique_solutions, &solutions->data[i]);
		}
	}
}

int main()
{
	Vector krug;
	Vector vec;
	Vector used;
	Vector2d solutions;
	Vector2d unique_solutions;

	int n = 0;
	scanf("%d", &n);

	init_vector(&krug, 0);
	init_vector(&vec, 0);
	init_vector(&used, 2 * n + 1);
	init_vector2d(&solutions, 0, 2 * n);
	init_vector2d(&unique_solutions, 0, 2 * n);

	fun(&krug, &vec, n, &used, &solutions);

	qsort(solutions.data, solutions.size, sizeof(Vector), perm_cmp);

	get_unique_solutions(&solutions, &unique_solutions);

	print_vector2d(stdout, &unique_solutions);

	destroy_vector(&krug);
	destroy_vector(&vec);
	destroy_vector(&used);
	destroy_vector2d(&solutions);
	destroy_vector2d(&unique_solutions);
}