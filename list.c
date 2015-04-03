#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct list
{
	list_node_ptr_t head;
	void (*element_copy)(element_ptr_t *dest_element, element_ptr_t src_element);
	void (*element_free)(element_ptr_t *element);
	int (*element_compare)(element_ptr_t x, element_ptr_t y);
	void (*element_print)(element_ptr_t element);
};

struct list_node
{
	list_node_ptr_t prev;
	element_ptr_t element;
	list_node_ptr_t next;
};

list_ptr_t list_create 	( // callback functions
				void (*element_copy)(element_ptr_t *dest_element, element_ptr_t src_element),
				void (*element_free)(element_ptr_t *element),
				int (*element_compare)(element_ptr_t x, element_ptr_t y),
				void (*element_print)(element_ptr_t element)
			)
{
	list_ptr_t list = (list_ptr_t)malloc(sizeof(list_t));

	if(list == NULL) {
		list_errno = LIST_MEMORY_ERROR;
		return NULL;
	}

	list->head = NULL;
	list->element_copy = element_copy;
	list->element_free = element_free;
	list->element_compare = element_compare;
	list->element_print = element_print;

	return list;
}

void list_free( list_ptr_t* list )
{
	list_errno = LIST_NO_ERROR;
	while(list_size(*list) != 0) {
		list_free_at_index(*list, 0);
	}
	free(*list);
	*list = NULL;
}

int list_size( list_ptr_t list )
{
	if(list == NULL) {
		list_errno = LIST_INVALID_ERROR;
		return 0;
	}

	int size = 0;
	list_node_ptr_t node = list->head;
	while(node != NULL) {
		size++;
		node = node->next;
	}
	return size;
}

list_ptr_t list_insert_at_index( list_ptr_t list, element_ptr_t element, int index)
{
	list_errno = LIST_NO_ERROR;		// Reset errno
	if(list == NULL) {
		list_errno = LIST_INVALID_ERROR;
		return NULL;
	}

	list_node_ptr_t new_node = (list_node_ptr_t)malloc(sizeof(list_node_t));

	if(new_node == NULL) {	
		list_errno = LIST_MEMORY_ERROR;
		return NULL;
	}

	list->element_copy(&(new_node->element), element);
	list->element_free(&element);
	
	if(list_size(list) == 0) {		// Empty list
		list->head = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	} else {						// Non-empty list
		list_node_ptr_t node = list_get_reference_at_index(list, index);
		if(index <= 0) {						// Prepend the new node to the beginning
			list->head = new_node;
			new_node->prev = NULL;
			new_node->next = node;
			node->prev = new_node;
		} else if(index >= list_size(list)) {	// Append the new node to the end
			node->next = new_node;
			new_node->prev = node;
			new_node->next = NULL;
		} else {								// Insert the new node at 'index'
			list_node_ptr_t previous_node = node->prev;
			previous_node->next = new_node;
			new_node->prev = previous_node;
			node->prev = new_node;
			new_node->next = node;
		}
	}

	return list;
}

list_ptr_t list_remove_at_index( list_ptr_t list, int index)
{
	list_node_ptr_t node = list_get_reference_at_index(list, index);
	
	if(node == NULL) {	// Empty list
		list_errno = LIST_EMPTY_ERROR;
		return list;
	} else {			// Non-empty list
		if(node->prev == NULL && node->next == NULL) {	// Only node
			list->head = NULL;
		} else if(node->prev == NULL) { // First node of many
			list->head = node->next;
			node->next->prev = NULL;
			node->next = NULL;
		} else if(node->next == NULL) { // Last node of many
			node->prev->next = NULL;
			node->prev = NULL;
		} else {						// Not first or last node
			list_node_ptr_t previous_node = node->prev;
			list_node_ptr_t next_node = node->next;

			previous_node->next = next_node;
			next_node->prev = previous_node;

			node->prev = NULL;
			node->next = NULL;
		}
	}
	return list;
}

list_ptr_t list_free_at_index( list_ptr_t list, int index)
{
	if(list_size(list) == 0) {	// Empty list
		list_errno = LIST_EMPTY_ERROR;
		return list;
	}
	list_node_ptr_t node = list_get_reference_at_index(list, index);
	list->element_free(&(node->element));
	list_remove_at_index(list, index);
	free(node);
	return list;
}

list_node_ptr_t list_get_reference_at_index( list_ptr_t list, int index )
{
	if(list == NULL) {
		list_errno = LIST_INVALID_ERROR;
		return NULL;
	}
	if(list_size(list) == 0) {	// Empty list
		return NULL;
	}
								// Non-empty list
	list_node_ptr_t node = list->head;
	int current_idx = 0;

	while(current_idx < index && current_idx < list_size(list)-1) {
		node = node->next;
		current_idx++;
	}

	return node;
}

element_ptr_t list_get_element_at_index( list_ptr_t list, int index )
{
	list_node_ptr_t node = list_get_reference_at_index(list, index);
	if(node == NULL) {	// Empty list
		return NULL;
	} else {
		return node->element;
	}
}

int list_get_index_of_element( list_ptr_t list, element_ptr_t element )
{
	int i;
	for(i = 0; i < list_size(list); i++) {
          if(list->element_compare(list_get_element_at_index(list,i),element) == 0){
			return i;
		}
	}
	return -1;
}

void list_print( list_ptr_t list )
{
	
	int size = list_size(list);
	printf("List size: %d\n", size);
	int i;
	for(i=0; i<size; i++)
	{
		list->element_print(list_get_element_at_index(list, i));
	}
}