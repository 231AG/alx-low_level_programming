#include "hash_tables.h"

/**
 * hash_table_create - function to create a hash table
 * @size: the size of array
 *
 * Return: the result.
 */

hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *hash = NULL;
	hash_node_t **ar = NULL;
	unsigned long int x = 0;

	hash = malloc(sizeof(hash_table_t));

	if (hash == NULL)
	{
		return (NULL);
	}

	ar = malloc(sizeof(hash_node_t *) * size);

	if (ar == NULL)
	{
		return (NULL);
	}

	for (; x < size; ++x)
	{
		ar[x] = NULL;
	}

	hash->size = size;
	hash->array = ar;

	return (hash);
}
