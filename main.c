#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 6

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

	for (int i = 0; i <= 4; i += 2)
	{
		printf("(%d,%d,%d)", tri[i], tri[i + 1], tri[(i + 1 + 4) % 6]);

	}
	printf("\n");
}

int check_used(int *tri, int *used)
{
	int hash[3] = {0};
	for (int i = 0; i <= 4; i += 2)
	{
		hash[i/2] = tri[i] * 49 + tri[i + 1] * 7 + tri[(i + 1 + 4) % 6];
		if (used[hash[i/2]] == 1)
			return 1;
	}
	for (int i = 0; i < 3; i++)
	{
		used[hash[i]] = 1;
	}
	return 0;
}

int perm_solve(int *tri, int solutions[][SIZE], int *used)
{
	assert(tri);

	int size = 0;

	while (next_permutation(tri))
	{
		if (check_sum(tri) && !check_used(tri, used))
		{
			for (int i = 0; i < SIZE; ++i)
			{
				solutions[size][i] = tri[i];
			}
			size++;
		}		
	}
	return size;
}

int main()
{
	int tri[SIZE] = {1, 2, 3, 4, 5, 6};
	int solutions[24][SIZE];
	int used[6 * 49 + 5 * 7 + 4];
	int size = perm_solve(tri, solutions, used);
	
	for (int i = 0; i < size; i++)
	{
		print_array(solutions[i]);
	}

	return 0;
}