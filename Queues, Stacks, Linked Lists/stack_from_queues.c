/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Braeden Kuether
 * Email: kuetherb@oregonstate.edu 
 */

#include <stdio.h>

#include "queue.h"
#include <assert.h>
#include "stack_from_queues.h"

/*
 * This function should allocate and initialize all of the memory needed for
 * your stack and return a pointer to the stack structure.
 */
struct stack_from_queues* stack_from_queues_create() {

	//Allocating new memory for the stack struct 
	struct stack_from_queues* new = malloc(sizeof(struct stack_from_queues));
	
	//Using the queue_create functions to create both the queues in the stack struct
	new->q1 = queue_create();
	new->q2 = queue_create();

	//Return the struct
	return new;
}

/*
 * This function should free all of the memory allocated to a stack, including
 * the memory associated with each queue.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if stack is NULL.
 */
void stack_from_queues_free(struct stack_from_queues* stack) {

	//Assert function checks if the struct is NULL
	assert(stack);

	//Use queue_free function from the provided queue.c to free both the queues in the stack struct
	queue_free(stack->q1);
	queue_free(stack->q2);

	//Free the stack struct
	free(stack);
}

/*
 * This function should return 1 if a stack is completely empty or 0 if there
 * is at least one element stored in the stack.
 *
 * Params:
 *   stack - the stack whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *
 * Return:
 *   Should return 1 if the stack is empty or 0 otherwise.
 */
int stack_from_queues_isempty(struct stack_from_queues* stack) {

	//Using the queue_isempty function from the stack.c
	if (queue_isempty(stack->q1)) {
		if (queue_isempty(stack->q1)) {

			//Returns 1 if both queues are empty
			return 1;
		}
	}

	//Return 0 if the conditions are not met. 
 	return 0;
}

/*
 * Should push a new value onto a stack.
 *
 * Params:
 *   stack - the stack onto which to push a value.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *   value - the new value to be pushed onto the stack
 */
void stack_from_queues_push(struct stack_from_queues* stack, int value) {

	//Checks to see if the stack struct is NULL
	assert(stack);

	//Counter for the for loop
	int counter = 0;

	//Do this while the first queue is not empty
	while (!queue_isempty(stack->q1)) {

		//Push all of the elements in the first queue to the second queue
		queue_enqueue(stack->q2,queue_dequeue(stack->q1));
	

		//Counter for number of elements
		counter++;
	}
	
	//Enqueue the input value onto the first queue
	queue_enqueue(stack->q1,value);

	//Push all the elements back to the first queue using a for loop
	for (int i = 0; i < counter; i++){

		//Use enqueue function to move elements back to the first queue and dequeue to delete elements in the second. 
		queue_enqueue(stack->q1,queue_dequeue(stack->q2));
	}
}

/*
 * Should return a stack's top value without removing that value from the
 * stack.
 *
 * Params:
 *   stack - the stack from which to read the top value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack.
 */
int stack_from_queues_top(struct stack_from_queues* stack) {

	//Assert function checks if queue is NULL
 	assert(stack);

 	//Using the queue_front function from queue.c which returns the value of the head.
 	return (queue_front(stack->q1));
}

/*
 * Should remove the top element from a stack and return its value.
 *
 * Params:
 *   stack - the stack from which to pop a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack before that value
 *   is popped.
 */
int stack_from_queues_pop(struct stack_from_queues* stack) {

	//Assert function checks if queue is NULL
	assert(stack);

	//Using the queue_dequeue function from queue.c which returns the value of the head and removes the element. 
	return (queue_dequeue(stack->q1));
}
