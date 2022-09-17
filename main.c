#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 6

int nums[SIZE] = {1, 2, 3, 4, 5, 6};

int check_sum(int *tri)
{
	assert(tri);

	int sum     = -1;
	int cur_sum = 0;

	for (int i = 0; i <= 4; i += 2)
	{
		cur_sum = tri[i] + tri[i + 1] + tri[(i + 1 + 4) % 6];
		if (sum == -1)
		{
			sum = cur_sum;
		}
		if (sum != cur_sum)
			return 0;
	}
	return 1;
}

void rand_solve(int *tri)
{
	assert(tri);

	srand(time(NULL));

	int r = 0;
	int used[SIZE] = {0};

	do {
		for (int i = 0; i < SIZE; i++)
		{
			used[i] = 0;
		}
		for (int i = 0; i < SIZE; i++)
		{
			do
			{
				r = rand() % 6;
			} while (used[r] != 0);

			tri[i] = nums[r];
			used[r] = 1;
		}
	} while (check_sum(tri) != 1);
}

void swap(int *a, int *b)
{
	assert(a);
	assert(b);
	assert(a != b);

	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void reverse(int *arr, int begin, int end)
{
	assert(arr);

	while (begin < end)
	{
		swap(&arr[begin++], &arr[end--]);
	}
}

int next_permutation(int *tri)
{
	assert(tri);

	int min = -1;

	for (int i = SIZE - 2; i >= 0; --i)
	{
		if (tri[i] < tri[i + 1])
		{
			min = i + 1;
			
			for (int j = i + 1; j <= SIZE - 1; j++)
			{
				if ((tri[j] < tri[min]) && tri[j] > tri[i])
				{
					min = j;
				}
			}
			swap(&tri[i], &tri[min]);
			reverse(tri, i + 1, SIZE - 1);
			return 1;
		}
	}
	return 0;
}

void print_array(int *tri)
{
	assert(tri);

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", tri[i]);
	}
	printf("\n");
}

void perm_solve(int *tri)
{
	assert(tri);

	while (!check_sum(tri) && next_permutation(tri))
		;
}

void solve(int *tri, void (*tactic)(int *tri))
{
	assert(tri);
	assert(tactic);

	tactic(tri);
}

int main()
{
	int tri[SIZE] = {1, 2, 3, 4, 5, 6};
	
	solve(tri, perm_solve);
	
	print_array(tri);

	return 0;
}