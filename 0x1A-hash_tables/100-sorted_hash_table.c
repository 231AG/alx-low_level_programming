#include "hash_tables.h"

/**
 * sorted_insert - insert node in sorted order
 * @ht: table
 * @node: node to insert
 */
void sorted_insert(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *shead, *stail;

	shead = ht->shead;
	stail = ht->stail;

	if (shead == NULL)
	{
		ht->shead = node;
		ht->stail = node;
		node->sprev = NULL;
		node->snext = NULL;
		return;
	}

	while (shead)
	{
		if (strcmp(shead->key, node->key) > 0)
		{
			node->snext = shead;
			node->sprev = shead->sprev;
			shead->sprev = node;
			if (node->sprev == NULL)
				ht->shead = node;
			else
				node->sprev->snext = node;
			return;
		}
		shead = shead->snext;
	}
	node->sprev = stail;
	node->snext = NULL;
	stail->snext = node;
	ht->stail = node;
}

/**
 * find_and_update - updates if key is found
 * @head: list head
 * @key: key to search
 * @value: vaue to set
 * Return: int
 */
int find_and_update(shash_node_t *head, const char *key, const char *value)
{
	/* return 0 if not found */
	while (head)
	{
		if (strcmp(head->key, key) == 0)
		{
			head->value = strdup(value);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

/**
 * shash_table_create - creates and initializes a sorted hash table
 * @size: size of the table
 * Return: shash_table_t*
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	shash_node_t **array;
	unsigned long int index;

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	array = malloc(sizeof(shash_node_t) * size);
	if (array == NULL)
		return (NULL);

	index = 0;
	while (index < size)
	{
		array[index] = NULL;
		index++;
	}

	ht->size = size;
	ht->array = array;
	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - set key and value in sorted hash table
 * @ht: sorted hash table
 * @key: key
 * @value: value to add or update
 * Return: int
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t **array, *head, *node;

	index = key_index((const unsigned char *)key, ht->size);
	array = ht->array;
	head = array[index];

	if (head)
	{
		if (find_and_update(head, key, value))
			return (1);
	}

	node = malloc(sizeof(shash_node_t));
	if (!node)
		return (0);

	node->key = strdup(key);
	node->value = strdup(value);
	node->next = head;

	sorted_insert(ht, node);
	return (1);
}

/**
 * shash_table_get - gets value associated with key
 * @ht: table
 * @key: key
 * Return: char*
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *node;
	char *k = strdup(key);

	index = hash_djb2((const unsigned char *)k) % ht->size;
	node = ht->array[index];

	if (node == NULL)
		return (NULL);

	while (node && strcmp(node->key, k) != 0)
	{
		node = node->next;
	}
	if (node)
	{
		return (node->value);
	}
	else
		return (NULL);
}

/**
 * sprint_node - prints node
 * @node: node
 */
void sprint_node(shash_node_t *node)
{
	while (node)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->next;
	}
}

/**
 * shash_table_print - print key/values of hash table in order
 * @ht: hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;

	node = ht->shead;

	putchar('{');
	while (node)
	{
		sprint_node(node);
		if (node->snext != NULL)
			printf(", ");
		node = node->snext;
	}
	puts("}");
}

/**
 * shash_table_print_rev - print key/values of hash table in reversed order
 * @ht: hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;

	node = ht->stail;

	putchar('{');
	while (node)
	{
		sprint_node(node);
		if (node->sprev != NULL)
			printf(", ");
		node = node->sprev;
	}
	puts("}");
}

/**
 * free_node - helper to free node
 * @node: to free
 */
void free_node(shash_node_t *node)
{
	if (node == NULL)
		return;

	free_node(node->next);
	free(node->key);
	free(node->value);
	free(node->snext);
	free(node->sprev);
	free(node);
}

/**
 * free_array - a helper too free array buckets
 * @array: array
 * @size: size
 */
void free_array(shash_node_t **array, unsigned long int size)
{
	if (array == NULL)
		return;

	if (size == 1)
	{
		if (array[size - 1])
			free_node(array[size - 1]);
		return;
	}
	free_array(array, size - 1);
	if (array[size - 1])
	{
		free_node(array[size - 1]);
	}
}

/**
 * shash_table_delete - free and delete hash table
 * @ht: hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	free_array(ht->array, ht->size);
	free(ht->array);
	ht->array = NULL;
	ht->shead = NULL;
	ht->stail = NULL;
	free(ht);
}
