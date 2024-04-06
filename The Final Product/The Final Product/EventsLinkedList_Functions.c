#include "Emulation.h"



void initialize_list(List** list) {
	/* This function initializes(makes it empty) a linked list
	- It takes the start and gives it NULL
	*/

	*list = NULL;
	/*Making the list empty using NULL*/

}

void add_to_list(List** list, Event* new_event) {

	List* newnode; 
	newnode = malloc(sizeof(List));
	
	if (newnode == NULL)
		/* No heap space */
		printf("unable to allocate memory");

	/*
	-The strcpy function only works for strings, our struct contains integars
	-A manual copy had to be done.
	*/
	newnode->event.time = new_event->time;
	newnode->event.event = new_event->event;
	newnode->event.orig_cust = new_event->orig_cust;
	newnode->event.dest_cust = new_event->dest_cust;
	newnode->event.weight = new_event->weight;

	newnode->next = *list; 
	/*giving the newnode->next the address of the start of the list. 
	-incase the list already existed, new node gets added to the start of the list
	*/

	*list = newnode;
	/*
	-now giving start the address of the new node
	-indicating that newnode is currently the start of the list
	*/


	list_count++;
}

void display_list(List* list) {
	List* current;

	current = list;
	/*giving current the start of the list*/
	if (list == NULL) {
		printf("List is currently empty");
	}

	else{
	fprintf(EF, "Time	Event	Origin	Destination	Weight");
	while (current != NULL) {

		fprintf(EF, "%d	%c	%d	%d	%d\n",
			current->event.time, current->event.event, current->event.orig_cust, current->event.dest_cust, current->event.weight);
		/*printing the elements of each node in the linked list while we traverse the list*/
		current = current->next;
	}
	}

	//printf("You have %d nodes in the list", list_count);
}

void free_mem(List** ptr)
{
	/*
	 - Free memory
	 - Since the freed node might be zeroed, it is necessary to remember
	   the next address before the freeing takes place
	*/
	List* current;
	List* next;

	/* Current gets the value of ptr */
	current = *ptr;

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	/* Clear original pointer */
	*ptr = NULL;
}


/*Function to swap the nodes */
List* swap(List* ptr1, List* ptr2)
{
	List* tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return ptr2;
}


///Function to sort the list
int bubbleSort(List** head, int count)
{
	List** h;
	int i, j, swapped;

	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i - 1; j++) {

			List* p1 = *h;
			List* p2 = p1->next;

			if (p1->event.time > p2->event.time) {

				/* update the link after swapping */
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}
}

