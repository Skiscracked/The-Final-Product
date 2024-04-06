#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include <io.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>	

#define NAMELEN 33
#define BINDEX 3
#define EINDEX 1
#define LENGTH 256
#define TRUE 1
#define FALSE 0
#define ELENGTH 2
#define START 1000

#define TRUNCATE(name)		name[strlen(name)-1] = '\0'


#define NUL	'\0'

/* Prefixes for ESC sequences */
#define ESC "\x1b"	/* Escape */
#define CSI "\x1b["	/* Control Sequence Introducer */

#define TRUE	1
#define FALSE	0
#define COLS (4* xbuild)
#define ROWS (4* ybuild)
#define MAXVs 4
#define speedforeyes 800 /*defining a macro for the speed function,
						  slow enough for the eyes to see*/
						  /* Some commonly used VT-100 commands */
#define CUP(c,r)	printf(CSI "%d;%dH", (r), (c)); /* Move cursor position to col, row */
#define EL(r)		printf(CSI "%d;1H" CSI "K", (r)); /* Erase in Line */
#define CLRSCR		printf(CSI "2J");


int xbuild, ybuild; //Global variables to scan the number of x and y buildings from the input file
enum VT100_COLOURS {
	FGWHITE = 32,
	BGRED = 41,
	BGGREEN = 42,
	BGYELLOW = 43,
	BGBLUE = 44,
	BGCYAN = 46
};

/* A very simple definition of a vehicle */
typedef struct vehicle
{
	int speed;			/* Speed of redraw in msec */
	int x, y;			/* Position on screen */
	int xinc, yinc;		/* X,Y increments */
} VEHICLE;

/* Structure for vehicle movement */
typedef struct xypos
{
	int x;
	int y;
} XYPOS;

/* Array of cells (map elements) */
enum Cell_type { CNE = 1, REG_RD = -1, JUN = 0, BUILDING = 2 };
enum Cell_dir { UP, DOWN, RIGHT, LEFT, BI };

struct cell
	/*
	- Cell structure was edited to contain a cell direction and a cell type
	*/
{
	enum Cell_dir direction;
	enum Cell_type type;
};

typedef struct cell CELL;

/*The map :
-map points to a pointer to a CELL
- map is a base address for an array of pointers to CELLs
- map_rows points to a CELL
- map_rows is a base address for an array of CELLs
*/
CELL** map;
CELL* map_rows;

unsigned long long r, lx, ly; /* Used with 8-byte addresses */
unsigned int c;
char ch;

/** Create ROWS x COLS array of contiguous CELLs **/

typedef struct car
{
	/*int originx;//x coordinate origin of the car
	int originy;//y coordinate origin of the car*/
	XYPOS origin;
	char carsym;//symbol for the car
	XYPOS car;//the current location coordinates of the car
	XYPOS dest;//the destination coordinates for the car
	int xinc, yinc;

	//CELL LOCATE; //Pointer to determine cars location on map
} CAR;

/*struct prompt {//structure for prompts for enum selection
	char* name;
	int code;
};*/

/* External data */
extern HANDLE scrout, keyin;
extern COORD scr_size;
//extern VEHICLE v1;
//extern XYPOS xy[];

int numofv;//global variable containing the number of vehicles the user wishes to create
//in the int main function, the move vehicle is going to receive this as a parameter
CAR AEDV[MAXVs];






// Define a struct for a building
struct Building {
	int x;
	int y;
	char name[2];
	char type[20];
	char quad[3];
	struct Building* next;
};

struct Building building[100];
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


/* External functions (different modules) */
/*Functions necessary to move the car*/
extern void status_window();
extern int check_kb();
extern void move(CAR v1[], int y);
extern void screen_size();
extern void print_msg(char* msg);
extern void box(int ulx, int uly, char* name, int colour);
extern void populate_map();
extern int create_map(void);
extern void freemalloc();
extern void moveup(CAR v1[], int i, int desty);
extern void movedown(CAR v1[], int i, int desty);
extern void moveright(CAR v1[], int i, int destx);
extern void moveleft(CAR v1[], int i, int destx);
extern char streetdir(CAR v1[], int i);
extern char avenuedir(CAR v1[], int i);



extern void eventlist();//This function calls the other functions beneath it(The linked list functions)
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


#pragma once
