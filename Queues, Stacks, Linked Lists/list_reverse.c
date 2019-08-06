/*
 * This is the file in which you'll write a function to reverse a linked list.
 * Make sure to add your name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>

#include "list_reverse.h"

/*
 * In this function, you will be passed the head of a singly-linked list, and
 * you should reverse the linked list and return the new head.  The reversal
 * must be done in place, and you may not allocate any new memory in this
 * function.
 *
 * Params:
 *   head - the head of a singly-linked list to be reversed
 *
 * Return:
 *   Should return the new head of the reversed list.  If head is NULL, this
 *   function should return NULL.
 */
struct link* list_reverse(struct link* head) {

	//Create three pointer variables. 
	struct link* spot = head;
	struct link* prev = NULL;
	struct link* next;

	//While loop until end of linked list
	while (spot != NULL) { 

		//Setting value of next pointer
		next = spot->next;

		//Reversing order of link
		spot->next = prev;
		prev = spot;
		spot = next;
	}

	//Head is equal to the last element of the linked list that isn't NULL
	head = prev;

	//Returning head value
	return head;
}
