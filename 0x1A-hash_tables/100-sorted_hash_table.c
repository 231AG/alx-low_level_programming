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

	if (node->key < shead->key)
	{
		node->snext = shead;
		node->sprev = NULL;
		shead->sprev = node;
		ht->shead = node;
		return;
	}

	while (shead->snext && node->key >= shead->snext->key)
	{
		shead = shead->snext;
	}

	node->sprev = shead;
	node->snext = shead->snext;
	if (shead->snext)
	{
		shead->snext->sprev = node;
	}
	shead->snext = node;
	if (node->snext == NULL)
	{
		ht->stail = node;
	}
}

int find_and_update(shash_node_t *head, const char *key, const char *value)
{
	/* return 0 if not found */
	while (head)
	{
		if (strcmp(head->key, key) == 0)
		{
			free(head->value);
			head->value = strdup(value);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

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
