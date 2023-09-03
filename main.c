#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

void
exit_with_error (const char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

char
*get_primes (int n)
{
	char *prime_table = calloc(n+1, 1);
	if (!prime_table) exit_with_error("Failed to allocate prime table.");

	int i, j;
	for (i = 2; i*i <= n; i++)
		if (!prime_table[i])
			for (j = i*i; j <= n; j += i) prime_table[j] = 1;

	return prime_table;
}

int
main (int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage %s <N>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *end;
	int n;
	errno = 0;
	n = strtol(argv[1], &end, 10);
	if (errno != 0) exit_with_error("Error parsing input.");

	clock_t start_time = clock();

	char *prime_table = get_primes(n);
	if (!prime_table) exit_with_error("Failed to generate primes.");
	
	clock_t end_time = clock();
	double seconds_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	FILE *output_file = fopen("output.txt", "w");
	int i;
	for (i = 2; i <= n; i++)
		if (!prime_table[i]) fprintf(output_file, "%d\n", i);

	free(prime_table);
	fclose(output_file);

	printf("\nTime taken: %f seconds (%lu cycles)\n", seconds_spent, (end_time - start_time));

	return 0;
}
