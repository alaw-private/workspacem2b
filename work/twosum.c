#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *two_sum(int *nums, size_t numsize, int target, int *return_size)
{
	int valid_num_indices[numsize];
	memset(&valid_num_indices, -1, numsize);
	int tmpcnt = 0;
	for (int i = 0; i < numsize; i++) {
		if (*(nums + i) <= target)
			valid_num_indices[tmpcnt++] = i;
	}
	int i, j;
	for (i = 0; i < tmpcnt - 1; i++) {
		for (j = i + 1; j < tmpcnt; j++) {
			if (*(nums + i) + *(nums + j) == target)
				goto found_pair;
		}
	}
	return NULL;
found_pair:
	int *returnarr = malloc(sizeof(int) * 2);
	*returnarr = i;
	*(returnarr + 1) = j;
	return_size = returnarr;
	return returnarr;
}

int test(int tests, int **testnums, int *testsizes, int *testtargets, int **returns)
{
	for (int i = 0; i < tests; i++) {
		two_sum(*(testnums + i), *(testsizes + i), *(testtargets + i), *(returns + i));
	}
	for (int i = 0; i < tests; i++) {
		printf("nums: ");
		for (int j = 0; j < *(testsizes + i); j++) {
			printf("%d ", *(*(testnums + i) + j));
		}
		printf("| target: %d ", *(testtargets + i));
		if (*(returns + i) == NULL)
			printf("| result: NULL\n");
		else
			printf("| result: %d %d\n", **(returns + i), *(*(returns + i) + 1));
	}
	for (int i = 0; i < tests; i++) {
		if (*(returns + i) != NULL)
			free(*(returns + i));
	}
}

int main()
{
	int tcount = 10;
	int **tnumarrays = malloc(sizeof(int *) * tcount);
	int *tsizes = malloc(sizeof(int) * tcount);
	int *ttargets = malloc(sizeof(int) * tcount);
	int **tresults = malloc(sizeof(int *) * tcount);
}