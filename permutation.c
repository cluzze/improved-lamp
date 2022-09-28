#include "permutation.h"
#include "myassert.h"

void swap(int *a, int *b)
{
	MYASSERT(a)
	MYASSERT(b)
	MYASSERT(a != b)

	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void reverse(int *arr, int begin, int end)
{
	MYASSERT(arr)

	while (begin < end)
	{
		swap(&arr[begin++], &arr[end--]);
	}
}

int next_permutation(Vector *vec)
{
	MYASSERT(vec)

	int min = -1;
	int i = 0, j = 0;

	for (i = vec->size - 2; i >= 0; --i)
	{
		if (vec->data[i] < vec->data[i + 1])
		{
			min = i + 1;
			
			for (j = i + 1; j <= (int)vec->size - 1; ++j)
			{
				if ((vec->data[j] < vec->data[min]) 
					&& vec->data[j] > vec->data[i])
				{
					min = j;
				}
			}

			swap(&vec->data[i], &vec->data[min]);
			reverse(vec->data, i + 1, vec->size - 1);
			
			return 1;
		}
	}

	return 0;
}