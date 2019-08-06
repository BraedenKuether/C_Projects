/*
 * This is the file in which you'll write the functions required to implement
 * a queue using two stacks.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Braeden Kuether
 * Email: kuetherb@oregonstate.edu
 */

#include <stdio.h>

#include "stack.h"
#include <assert.h>
#include "queue_from_stacks.h"

/*
 * This function should allocate and initialize all of the memory needed for
 * your queue and return a pointer to the queue structure.
 */
struct queue_from_stacks* queue_from_stacks_create() {

	//Malloc to allocate memory
	struct queue_from_stacks* new = malloc(sizeof(struct queue_from_stacks));
	
	//Using the stack_create function from the provided stack.c 
	new->s1 = stack_create();
	new->s2 = stack_create();

	//Returning struct 
	return new;
}

/*
 * This function should free all of the memory allocated to a queue, including
 * the memory associated with each stack.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if queue is NULL.
 */
void queue_from_stacks_free(struct queue_from_stacks* queue) {

	//Assert function checks if queue struct is NULL
	assert(queue);

	//Using the stack_free function from the provided stack.c
	stack_free(queue->s1);
	stack_free(queue->s2);

	//Freeing the queue
	free(queue);
}

/*
 * This function should return 1 if a queue is completely empty or 0 if there
 * is at least one element stored in the queue.
 *
 * Params:
 *   queue - the queue whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *
 * Return:
 *   Should return 1 if the queue is empty or 0 otherwise.
 */
int queue_from_stacks_isempty(struct queue_from_stacks* queue) {
	
	//Using stack_isempty function from the provided stack.c
	if (stack_isempty(queue->s1)) {
		if (stack_isempty(queue->s2)) {

			//Return 1 if both stacks are empty
			return 1;
		}
	}

	//Return 0 if tghe conditions are not met
	return 0;
}

/*
 * Should enqueue a new value onto the end of a queue.
 *
 * Params:
 *   queue - the queue onto which to enqueue a value.  May not be NULL.
 *     The function should exit the program with an error if queue is NULL.
 *   value - the new value to be enqueueed onto the queue
 */
void queue_from_stacks_enqueue(struct queue_from_stacks* queue, int value) {
	
	//Checks to see if the queue struct is NULL
	assert(queue);

	//Counter for the for loop
	int counter = 0;

	//Do this while the first stack is not empty
	while (!stack_isempty(queue->s1)) {

		//Push all of the elements in the first stack to the second stack
		stack_push(queue->s2,stack_pop(queue->s1));

		//Counter for number of elements
		counter++;
	} 
	
	//Pushing the input value onto the second stack
	stack_push(queue->s2,value);
	
	//Push all the elements back to the first stack using a for loop
	for (int i = 0; i < counter + 1; i++){

		//Use stack push function to move elements back to the first stack and pop to delete elements in the second. 
		stack_push(queue->s1,stack_pop(queue->s2));
	}
}

/*
 * Should return a queue's front value without removing that value from the
 * queue.
 *
 * Params:
 *   queue - the queue from which to read the front value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue.
 */
int queue_from_stacks_front(struct queue_from_stacks* queue) {

	//Assert function used to check if the queue struct is NULL
	assert(queue);

	//Returns the value at the top element with the top function from stack.c
 	return(stack_top(queue->s1));
}

/*
 * Should remove the front element from a queue and return its value.
 *
 * Params:
 *   queue - the queue from which to dequeue a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if queue is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the front of the queue before that value
 *   is dequeued.
 */
int queue_from_stacks_dequeue(struct queue_from_stacks* queue) { 

	//Assert statement used to check if queue stack is NULL
	assert(queue);

	//Return the value of the front element and removes the toop element with the pop function from stack.c
	return(stack_pop(queue->s1));
}
