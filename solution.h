#ifndef _SOLUTION_
#define _SOLUTION_

#include "vector.h"

void get_triplets(Vector *vec, Vector *triplets);

int check_sum(Vector *triplets);

int get_hash(int a, int b, int c, int n);

int check_used(Vector *triplets, Vector *used);

void perm_solve(Vector *vec, Vector *triplets, Vector *used, Vector2d *solutions);

#endif