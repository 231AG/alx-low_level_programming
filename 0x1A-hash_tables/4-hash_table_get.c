#include "hash_tables.h"

/**
 * hash_table_get - to retrive the value
 * @ht: pointer to table
 * @key: char to get the value
 *
 * Return: the result.
 */

char *hash_table_get(const hash_table_t *ht, const char *key)
{
	hash_node_t *ind;
	unsigned long int x;

	if (ht == NULL || key == NULL || *key == '\0')
	{
		return (NULL);
	}

	x = key_index((const unsigned char *)key, ht->size);

	if (x >= ht->size)
	{
		return (NULL);
	}

	ind = ht->array[x];

	while (ind != NULL)
	{
		if (strcmp(ind->key, key) == 0)
		{
			return (ind->value);
		}

		ind = ind->next;
	}

	return (NULL);
}
