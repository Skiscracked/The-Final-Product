#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include <io.h>

#define NAMELEN 33
#define BINDEX 3
#define EINDEX 1
#define LENGTH 256
#define TRUE 1
#define FALSE 0
#define ELENGTH 2
#define START 1000

#define TRUNCATE(name)		name[strlen(name)-1] = '\0'


/*1. Set up the structures for the various records*/
struct Customer_record {
	int Customer_ID;
	char fname[NAMELEN];
	char lname[NAMELEN];
	char building[BINDEX];
	char entrance;
	int floor;
}; 
typedef struct Customer_record Customer;

struct Event_record {
	int time;
	char event;
	int orig_cust;
	int dest_cust;
	int weight;
};
typedef struct Event_record Event;

struct Delivery_record {
	int package_no;
	int orig_cust;
	int dest_cust;
	int pickup_time;
	int delivery_time;
};
typedef struct Delivery_record Delivery;

struct node {
	Event event;
	struct node* next;
}; /*Linked list to store events*/
typedef struct node List;



//Creating a header record for the files. It helps to set a base address for operation.
struct Header {
	long first_id;
};
typedef struct Header Header;

/*Functions for the events linked list*/
//It's done in a linked list because of sequential file organization
extern void initialize_list(List** list); 
extern void add_to_list(List** list, Event* new_event);
List* swap(List* ptr1, List* ptr2);
extern int bubbleSort(List** head, int count);
extern void display_list(List* list);
extern void free_mem(List** ptr);

/*Function(s) to execute deliveries*/
extern void execute_event();

/*Functions for the customer file - Relative organization*/
extern void init_custheader_and_makerelative();
extern int returnindex(int i);


int time_elapsed;//Emulation time variable
int list_count;
FILE* EF;//Event file pointer - Text file

char Event_Execute[LENGTH];
char* execute_tok;
/*Update: I was able to initialize the event elements, right now im creating a function to add to the events linked list*/