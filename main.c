#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"
#include "permutation.h"
#include "solution.h"

int main()
{
	Vector vec;
	Vector triplets;
	Vector used;
	Vector2d solutions;
	
	int n = 0;
	scanf("%d", &n);

	init_vector(&vec, 2 * n);
	init_vector(&triplets, 3 * n);
	init_vector(&used, get_hash(2 * n, 2 * n - 1, 2 * n - 2, 2 * n));
	init_vector2d(&solutions, 0, 2 * n);

	fill_vector(&vec);

	/*print_vector(stdout,   &vec);
	print_vector(stdout,   &triplets);
	print_vector(stdout,   &used);
	print_vector2d(stdout, &solutions);
*/
	perm_solve(&vec, &triplets, &used, &solutions);

	//print_vector2d(stdout, &solutions);

	printf("%ld\n", solutions.size);

	destroy_vector(&vec);
	destroy_vector(&triplets);
	destroy_vector(&used);
	destroy_vector2d(&solutions);
}