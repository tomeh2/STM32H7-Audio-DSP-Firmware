/*
 * linked_list.c
 *
 *  Created on: Sep 16, 2024
 *      Author: PC
 */

#include "linked_list.h"
#include "audio_defs.h"

#include <stddef.h>
#include <stdlib.h>

int8_t linkedlist_init(struct LinkedList* ll)
{
	ll->head = NULL;
}

int8_t linkedlist_insert(struct LinkedList* ll, void* element, uint32_t index)
{
	if (!ll)
		return -EINVAL;

	struct LinkedListElement* new_element = malloc(sizeof(struct LinkedListElement));
	if (!new_element)
		return -ENOMEM;
	new_element->element = element;
	new_element->next = NULL;

	if (!ll->head)
	{
		ll->head = new_element;
		return EOK;
	}

	if (!index)
	{
		ll->head = new_element;
		new_element->next = ll->head;
		return EOK;
	}

	struct LinkedListElement* curr = ll->head;
	for (uint32_t i = 0; i < (index - 1) && curr->next != NULL; i++)
		curr = curr->next;

	if (!curr->next)
	{
		curr->next = new_element;
		return EOK;
	}

	struct LinkedListElement* old_curr_next = curr->next;
	curr->next = new_element;
	new_element->next = old_curr_next;
	return EOK;
}

int8_t linkedlist_remove(struct LinkedList* ll, uint32_t index)
{
	if (!ll)
		return -EINVAL;

	if (!ll->head)
		return EOK;

	struct LinkedListElement* prev = NULL;
	struct LinkedListElement* curr = ll->head;

	for (uint32_t i = 0; i < index && curr->next != NULL; i++)
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr == ll->head)
	{
		ll->head = curr->next;
		free(curr);
	}
	else
	{
		prev->next = curr->next;
		free(curr);
	}
	return EOK;
}






