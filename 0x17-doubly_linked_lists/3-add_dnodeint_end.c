#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * add_dnodeint_end - func to adds new node at the end
 * @head: the head of the list
 * @n: the number to place the value in it
 *
 * Return: the new head of linked list
 */

dlistint_t *add_dnodeint_end(dlistint_t **head, const int n)
{
	dlistint_t *curr = NULL;
	dlistint_t *n_node = NULL;

	n_node = malloc(sizeof(dlistint_t));

	if (n_node == NULL)
	{
		return (NULL);
	}
	n_node->n = n;

	if (*head)
	{
		curr = *head;

		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		n_node->next = NULL;
		n_node->prev = curr;
		curr->next = n_node;

		return (n_node);
	}
	n_node->next = *head;
	n_node->prev = NULL;

	*head = n_node;
	return (*head);
}
