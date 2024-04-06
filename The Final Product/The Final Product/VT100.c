/*
 - VT-100 demo s/w
 - Moves a "vehicle" in a figure-8 around two buildings with buildings placed at UL, 
   UR, LL, and LR
 - Shows:
   - Shows some VT-100 commands
   - How screen can be resized and redrawn
   - VT-100's two screens (Main and Alternate)
   - Shows how to use kbhit() function

 - Use:
   - Start program
   - Resize window, type 'R' (or 'r') to resize
   - Type '#' to end
   - Any other character displays vehicle status

 - Chapter 3 of the VT-100 manual with the control sequences defined can be
   found at:
https://www.vt100.net/docs/vt100-ug/contents.html

 - VT-100 Terminal Control Escape Sequences (Microsoft)
https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences

 - XTerm control sequences (VT-100):
https://invisible-island.net/xterm/ctlseqs/ctlseqs.html

 - ECED 3401
 - 23 Oct 23
*/
#include "Emulation.h"

void print_msg(char* msg)
{
/*
 - Display message in diagnostic area (LL of active screen)
*/
CUP(1, scr_size.Y)
EL(scr_size.Y)
printf(CSI "%d;%dm%s", BGBLUE, FGWHITE, msg);
printf(CSI "0m"); /* Restore FG & BG colour */
}

void box(int ulx, int uly, char *name, int colour)
{
/* 
 - Draw a 3 high by 4 wide box at position ulx, uly 
 - If not on screen, no dianostics are given
 - Change the box colour
 - Name must be 2 chars max
*/
printf(CSI "%dm", colour);
printf(ESC "(0");		/* DEC line drawing character set */
CUP(ulx, uly)
printf("lqk");			/* UL Hor Hor UR*/
CUP(ulx, uly+1)
printf("x%s", name);	/* Vert name Vert */
CUP(ulx, uly+2)
printf("mqj");			/* LL Hor Hor LR */
printf(ESC "(B");		/* Return to ASCII */
printf(CSI "0m");		/* Return to default FG anf BG */
}

void populate_map()
{
    /*
         - Draw the map
         - Put buildings (boxes) at 4 corners
         - Additional box on top row for vehicle
        */
    printf(CSI "2J"); /* Clear screen */
    //struct Building* current = head;
    int index = 0;

    for (int i = 0; i < ybuild; i++) {
        int ycord = 2 + (4 * i);//2 + (4 *0)
        for (int j = 0; j < xbuild; j++) {
            int xcord = 2 + (4 * j);
            char ID[3];
            ID[0] = 'A' + i;
            ID[1] = 'A' + j;
            ID[2] = '\0';
            const char* name = ID;
            building[index].x = xcord;
            building[index].y = ycord;
            building[index].name[0] = ID[0];
            building[index].name[1] = ID[1];
            box(xcord, ycord, name, BGBLUE);
            index++;
        }
    }
}

int create_map(void) {

    /** Create ROWS x COLS array of contiguous CELLs **/

    /* 1. Reserve space for map
        - map is ROWS long memory of pointers to map_rows
        - map_rows contains all the rows in contiguous memory
    */
    if ((map = malloc(ROWS * sizeof(CELL*))) == NULL)
    {
        printf("No space for map rows - terminating.\n");
        (void)getchar();
        return 1;
    }

    if ((map_rows = malloc(ROWS * COLS * sizeof(CELL))) == NULL)
    {
        printf("No space for map - terminating.\n");
        free(map);
        (void)getchar();
        return 1;
    }

    /* 2. Assign base address of each row
        Map_rows is the base address of memory block
        Each row has COLS entries
        Offsets are in bytes (warning can be ignored)
    */
    for (r = 0; r < ROWS; r++)
        map[r] = map_rows + (r * COLS);

    /* 3.Map should be defined as map[row][column]
     - Set the corners of the map
     - Set the
    */

    /*Here we are setting the corners of the map*/
    map[0][0].type = CNE;
    map[0][0].direction = BI;

    map[0][COLS-1].type = CNE;
    map[0][COLS-1].direction = BI;

    map[ROWS-1][COLS-1].type = CNE;
    map[ROWS-1][COLS-1].direction = BI;

    map[ROWS-1][0].type = CNE;
    map[ROWS-1][0].direction = BI;

    /*Setting the first and last columns and rows to be all bi-directionals */
    for (int i = 0; i < ROWS; i++) 
    {

        /*Setting the first and last columns to be all bi-directionals */

        /*Last column*/
        map[i][COLS - 1].direction = BI;
        map[i][COLS - 1].type = REG_RD;

        /*First column*/
        map[i][0].direction = BI;
        map[i][0].type = REG_RD;
    }
        /*Setting the first and last rows to be all bi-directionals */
    for (int i = 0; i < COLS; i++)
    {
        /*First row*/
        map[0][i].direction = BI;
        map[0][i].type = REG_RD;

        /*Last row*/
        map[ROWS-1][i].direction = BI;
        map[ROWS-1][i].type = REG_RD;
    }

    /*defining the directons of the avenues*/
    for (int x = 0; x < ROWS; x++) {

        for (int y = 1; y <= xbuild; y++) {
            int mp_rds = y * 4;

            if (((mp_rds / 4) % 2) == 0) {//if once divided by 4 it's an even number - go up
                map[x][mp_rds-1].direction = UP;
                map[x][mp_rds-1].type = REG_RD;
            }
            else if (((mp_rds / 4) % 2) == 1) {//if once divided by 4 it's an odd number - go down
                map[x][mp_rds-1].direction = DOWN;
                map[x][mp_rds-1].type = REG_RD;
            }
        }
    }

    /*Defining the directions of the streets*/
    for (int x = 1; x <= ybuild; x++) {
        int maprows = x * 4;

        for (int i = 1; i < COLS; i++) {

            if (((maprows / 4) % 2) == 1) {
                map[maprows-1][i].direction = RIGHT; /*Ex: 4, 12, 20... all move right (East)*/
                map[maprows-1][i].type = REG_RD;
            }
            else if (((maprows / 4) % 2) == 0) {
                map[maprows-1][i].direction = LEFT;/*Ex: 8, 16, 24... all move left (West)*/
                map[maprows-1][i].type = REG_RD;
            }
        }
    }

    /*
    -Now we are defining the buildings
    -Everything that isn't a road or a corner is a building
    */
    for (int rows = 0; rows < ROWS; rows++) {
        //for loop to increment the rows(collection of map cells)
        for (int cols = 0; cols < COLS; cols++) {
            //for loop to increment the columns of that row(each cell in that row)
            if ((map[rows][cols].type) != CNE && (map[rows][cols].type) != REG_RD && (map[rows][cols].type) != JUN) {
                map[rows][cols].type = BUILDING; /*If map pointer is not a corner or reg road or junction it is a building*/
            }
        }
    }
}

void freemalloc() 
{
    for (r = 0; r < ROWS; r++)
        free(map[r]);
    free(map);

}

void terminate(char* msg)
{
/* Fatal error detected - terminate */
printf("Error: %s\n", msg);
(void) getchar();
exit(1);
}


