/*
 * linked_list.h
 *
 *  Created on: Sep 16, 2024
 *      Author: PC
 */

#ifndef INC_LINKED_LIST_H_
#define INC_LINKED_LIST_H_

#include <stdint.h>

struct LinkedListElement;

struct LinkedListElement
{
	void* element;
	struct LinkedListElement* next;
};

struct LinkedList
{
	struct LinkedListElement* head;
};

int8_t linkedlist_init(struct LinkedList* ll);
int8_t linkedlist_insert(struct LinkedList* ll, void* element, uint32_t index);
int8_t linkedlist_remove(struct LinkedList* ll, uint32_t index);

#endif /* INC_LINKED_LIST_H_ */
