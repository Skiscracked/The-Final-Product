#pragma once
/*
 - Task 5 header file. Updates/Progress made are as follows:

 - Was able to define row and column sizes
 - Was able to memory allocate space for rows and columns
 - Was able to use a function to create the map rows and columns assigning enough columns for each row
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>		/* kbhit() */

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
enum Cell_dir { UP, DOWN, RIGHT, LEFT, BI};

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

/* External functions (different modules) */
extern void status_window();
extern int check_kb();
extern void move(CAR* v1[], int* y);
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

//struct Building* addBuilding(struct Building* head, int x, int y, const char* type, const char* quad);
