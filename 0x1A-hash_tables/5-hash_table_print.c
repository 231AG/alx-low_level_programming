#include "hash_tables.h"

/**
 * hash_table_print -print a hash table
 * @ht: pointer to checked
 *
 * Return: nothing
 */

void hash_table_print(const hash_table_t *ht)
{
	hash_node_t *index = NULL;
	unsigned long int x;
	short name = 0;

	if (ht == NULL)
	{
		return;
	}

	printf("{");

	for (x = 0; x < ht->size; ++x)
	{
		index = ht->array[x];

		while (index)
		{
			if (name == 1)
			{
				printf(", ");
			}
			name = 1;
			printf("'%s': '%s'", (char *) index->key, (char *) index->value);
			index = index->next;

		}
	}
	printf("}\n");
}
