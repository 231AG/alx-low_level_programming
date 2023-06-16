#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * get_dnodeint_at_index -  function to get the node
 * @head: the head of the list
 * @index: to find in lists
 *
 * Return: to target the specific node
 */

dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
	unsigned int count = 0;
	dlistint_t *curr = head;

	if (head)
	{
		while (curr != NULL)
		{
			if (count == index)
			{
				return (curr);
			}
			curr = curr->next;

			++count;
		}
	}
	return (NULL);
}
