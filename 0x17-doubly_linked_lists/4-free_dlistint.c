#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * free_dlistint - function to free the linked list
 * @head: the head of linked list
 *
 * Return: nothing.
 */

void free_dlistint(dlistint_t *head)
{
	dlistint_t *curr = head;
	dlistint_t *forword = NULL;

	while (curr != NULL)
	{
		forword = curr->next;
		free(curr);

		curr = forword;
	}
}
