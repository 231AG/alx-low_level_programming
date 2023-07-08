#include "hash_tables.h"

/**
 * hash_table_set - func to add elem in the table
 * @ht: a pointer to be checked
 * @key: the value to add to index
 * @value: the value connected to key
 *
 * Return: the result.
 */

int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *fresh;
	char *new_copy;
	unsigned long int x, ind;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
	{
		return (0);
	}
	new_copy = strdup(value);
	if (new_copy == NULL)
	{
		return (0);
	}
	ind = key_index((const unsigned char *)key, ht->size);

	for (x = ind; ht->array[x]; x++)
	{
		if (strcmp(ht->array[x]->key, key) == 0)
		{
			free(ht->array[x]->value);
			ht->array[x]->value = new_copy;
			return (1);
		}
	}
	fresh = malloc(sizeof(hash_node_t));
	if (fresh == NULL)
	{
		free(new_copy);
		return (0);
	}
	fresh->key = strdup(key);
	if (fresh->key == NULL)
	{
		free(fresh);
		return (0);
	}
	fresh->value = new_copy;
	fresh->next = ht->array[ind];
	ht->array[ind] = fresh;
	return (1);
}
