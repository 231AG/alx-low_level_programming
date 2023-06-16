#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * sum_dlistint - function to sum all nodes
 * @head: the head of linked list
 *
 * Return: the sum of nodes
 */

int sum_dlistint(dlistint_t *head)
{
	int count = 0;
	dlistint_t *curr = head;

	if (head)
	{
		while (curr != NULL)
		{
			count += curr->n;
			curr = curr->next;
		}
	}
	return (count);
}
