/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include "dynarray.h"
#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
	struct dynarray* value;
	struct dynarray* priority;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* new = malloc(sizeof(struct pq));
	new->value = dynarray_create();
	new->priority = dynarray_create();
	return new;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->value);
	dynarray_free(pq->priority);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise..
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	int size = dynarray_size(pq->value);
	if (size == 0) {
		return 1;
	} else {
		return 0;
	}
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {

	int size = dynarray_size(pq->value);

	//Insert value at the bottom of the PQ
	dynarray_insert(pq->value, -1, value);
	dynarray_insert(pq->priority, -1, priority);

	restructure_up(pq,size);
}

void restructure_up(struct pq* pq, int index) {
	
	if (index == 0) {
		return;
	}

	int parent = (index - 1) / 2;
	int parent_priority = dynarray_get(pq->priority,parent);

	int index_priority = dynarray_get(pq->priority,index);

	if (index_priority < parent_priority) {
		swap_elements(pq,index,parent);
		restructure_up(pq,parent);
	}
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {

  	void* low_priority_value = dynarray_get(pq->value,0);
 	return low_priority_value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {

	int low_priority = dynarray_get(pq->priority,0);
	return low_priority;
}




/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {

	if (dynarray_size(pq->value) == 0) {
		return;
	} 

	int size = dynarray_size(pq->value) - 1;

	//Start by creating a variables for root
	void* root_value = dynarray_get(pq->value,0);

	//Create variables for last element 
	int last_value = dynarray_get(pq->value,size);
	int last_priority = dynarray_get(pq->priority,size);

	//Then we swap the first and last elements to be able to remove the root element
 	swap_elements(pq,0,size);

 	//Then we remove the root element after swaping
 	dynarray_remove(pq->value,-1);
 	dynarray_remove(pq->priority,-1);

 	//Restructure the pq
 	restructure(pq,0);

 	return root_value;
}

void swap_elements(struct pq* pq, int index_1, int index_2) {
	//Create struct for first index swapped.
	void* one_value = dynarray_get(pq->value,index_1);
	int one_priority = dynarray_get(pq->priority,index_1);

	//Create strcut for second index swapped
	void* two_value = dynarray_get(pq->value,index_2);
	int two_priority = dynarray_get(pq->priority,index_2);

	//Set elements at index 1 equal to element at index 2
	dynarray_set(pq->value,index_1,two_value);
	dynarray_set(pq->priority,index_1,two_priority);

	//Set elements at index 1 equal to element at index 2./
	dynarray_set(pq->value,index_2,one_value);
	dynarray_set(pq->priority,index_2,one_priority);
}

void restructure(struct pq* pq, int index) {

	int left_child = (index * 2) + 1;
	int right_child = (index * 2) + 2;

	if ((left_child < dynarray_size(pq->value)) && (right_child < dynarray_size(pq->value))) {

		if (dynarray_get(pq->priority,left_child) < dynarray_get(pq->priority,right_child) || dynarray_get(pq->priority,left_child) == dynarray_get(pq->priority,right_child)){
			swap_elements(pq,index,left_child);
			restructure(pq,left_child);
		} 

		else {
			swap_elements(pq,index,right_child);
			restructure(pq, right_child);
		}
	} 

	else if (left_child < dynarray_size(pq->value) && dynarray_get(pq->priority,index) >= dynarray_get(pq->priority,left_child)) {
		swap_elements(pq,index,left_child);
		restructure(pq,left_child);

	}

	else {
		return;
	}

}