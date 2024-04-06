/*
 - Moving the vehicle
 - Vehicle '*' drawn at xy position
 - Increment (-1, 0, +1) is determined by ORG and DST
 - Vehicle drawn, pauses (speed msec), and is erased
 - Run until '#' detected

 - ECED 3401
 - 23 Oct 23
*/

#include "Emulation.h"

HANDLE scrout, keyin;
COORD scr_size;
VEHICLE v1;
/*
 - Route to be taken by vehicle - DST always ahead of vehicle
 - X,Y screen positions
 - xy[pos] is ORG and xy[pos+1] is DST
 - Wraps at 0,0
*/



void move(CAR v1[], int y)
{
    /*
     - Move the vehicle around the buildings
     - Route specified in xy[]
    */


    XYPOS org, dst;
    int pos;


    /* Move object in x or y direction */
    pos = 0;
    //for (int i = 0; i < *y; i++) {
    int i = y;
    org.x = v1[i].origin.x -1;  //v1->originx; //xy[pos];
    org.y = v1[i].origin.y -1;
    dst.x = v1[i].dest.x; //xy[pos + 1]
    dst.y = v1[i].dest.y;
    int dir_x = (org.x < dst.x) ? 1 : -1;
    int dir_Y = (org.y < dst.y) ? 1 : -1;

    int carx = v1[i].car.x;


    //map[v1[i].car.x][v1[i].car.y].direction;// How to access the cars current location in reference to the map memory

    //v1.speed = 100;
    while ((map[v1[i].car.x][v1[i].car.y].type) != BUILDING) {
        if (org.x != dst.x)
        {
            /* Moving in X direction */

            v1[i].yinc = 0;
            v1[i].car.x = v1[i].origin.x;
            v1[i].car.y = v1[i].origin.y;
            /* Stop of '#' of when x DST reached */

            if (v1[i].car.x < dst.x) {

                if (streetdir(AEDV, i) == 'B' || streetdir(AEDV, i) == 'R') {
                    /*
                    -This if statement checks if the street allows you to go right (ONLY IF ITS ODD)
                    -And also if it is a bidirectional street(the first and the last one)
                    */
                    moveright(AEDV, i, dst.x);
                }
                else {
                    if (avenuedir(AEDV, i) == 'B' || avenuedir(AEDV, i) == 'D') {
                        movedown(AEDV, i, (v1[i].car.y) + 4);
                    }
                    else if (avenuedir(AEDV, i) == 'B' || avenuedir(AEDV, i) == 'U') {
                        moveup(AEDV, i, (v1[i].car.y) - 4);
                    }
                    moveright(AEDV, i, dst.x);
                }

            }

            else if (v1[i].car.x > dst.x) {


                if (streetdir(AEDV, i) == 'B' || streetdir(AEDV, i) == 'L') {
                    /*
                    -This if statement is for if the street is even (LEFT)
                    */
                    moveleft(AEDV, i, dst.x);
                }
                else {
                    if (avenuedir(AEDV, i) == 'B' || avenuedir(AEDV, i) == 'D') {
                        movedown(AEDV, i, (v1[i].car.y) + 4);
                    }

                    else if (avenuedir(AEDV, i) == 'B' || avenuedir(AEDV, i) == 'U') {
                        moveup(AEDV, i, (v1[i].car.y) - 4);
                    }
                    moveleft(AEDV, i, dst.x);
                }
            }
        }





        if (org.y != dst.y)
        {
            /* Moving in Y direction */
            v1[i].yinc = (org.y < dst.y) ? 1 : -1;
            v1[i].xinc = 0;
            v1[i].car.y = org.y;
            /* Stop of '#' of when y DST reached */

            if (v1[i].car.y < dst.y) {


                if (avenuedir(AEDV, i) == 'B' && (map[v1[i].car.x][v1[i].car.y].direction = BI) || avenuedir(AEDV, i) == 'D' && (map[v1[i].car.x][v1[i].car.y].direction = DOWN)) {
                    /*
                    -This if statement is for if the street is even (LEFT)
                    */
                    movedown(AEDV, i, dst.y);
                }
                else {
                    if (streetdir(AEDV, i) == 'B' || streetdir(AEDV, i) == 'R') {
                        moveright(AEDV, i, (v1[i].car.x) + 4);
                    }

                    else if (streetdir(AEDV, i) == 'B' || streetdir(AEDV, i) == 'L') {
                        moveleft(AEDV, i, (v1[i].car.x) - 4);
                    }
                    movedown(AEDV, i, dst.y);
                }
            }

            else if (v1[i].car.y < dst.y) {

                if (avenuedir(AEDV, i) == 'B' || avenuedir(AEDV, i) == 'U') {
                    /*
                    -This if statement is for if the street is even (LEFT)
                    */
                    moveup(AEDV, i, dst.y);
                }
                else {
                    if (streetdir(AEDV, i) == 'B' || streetdir(AEDV, i) == 'R') {
                        moveright(AEDV, i, (v1[i].car.x) + 4);
                    }

                    else if (streetdir(AEDV, i) == 'B' || streetdir(AEDV, i) == 'L') {
                        moveleft(AEDV, i, (v1[i].car.x) - 4);
                    }
                    moveup(AEDV, i, dst.y);
                }
            }



        }
    }

    // else if () {

    // }

     /*if (!stop)
      {
          // Stop not selected, move to next position
          pos = pos + 1;
          if (xy[pos + 1].x == 0)
              pos = 0;
          // Update ORG and DST
          org = xy[pos];
          dst = xy[pos + 1];
      }*/

}

void moveup(CAR v1[], int i, int desty) {
    while (v1[i].car.y > desty && (map[(v1[i].car.x)][(v1[i].car.y) - 1].type) != BUILDING)
    {

        CUP(v1[i].car.x, v1[i].car.y);
        putchar('*');
        Sleep(speedforeyes);
        CUP(v1[i].car.x, v1[i].car.y);
        putchar(' ');
        v1[i].car.y -= 1;
    }
}

void movedown(CAR v1[], int i, int desty) {
    while (v1[i].car.y < desty && (map[(v1[i].car.x)][(v1[i].car.y)+1].type)!= BUILDING)
    {
        /*
        -This if-statement is to check if you can go down this avenue
        -Or if it is bi directional or if it's even( going down)
        */
        CUP(v1[i].car.x, v1[i].car.y);
        putchar('*');
        Sleep(speedforeyes);
        CUP(v1[i].car.x, v1[i].car.y);
        putchar(' ');
        v1[i].car.y += 1;
    }
}

void moveright(CAR v1[], int i, int destx) {
    while (v1[i].car.x < destx && (map[(v1[i].car.x) + 1][v1[i].car.y].type != BUILDING))
        /*This while loop is for when the destination is on the right of the origin*/
    {
        CUP(v1[i].car.x, v1[i].car.y);
        putchar('*');
        Sleep(speedforeyes);
        CUP(v1[i].car.x, v1[i].car.y);
        putchar(' ');
        v1[i].car.x += 1;
    }

}

void moveleft(CAR v1[], int i, int destx) {
    while (v1[i].car.x > destx && (map[(v1[i].car.x) - 1][v1[i].car.y].type != BUILDING))
    {
        /*
        -This if statement checks if the street allows you to go left (IF IT IS EVEN!!!)
        -And also if it is a bidirectional street(the first and the last one)
        */
        CUP(v1[i].car.x, v1[i].car.y);
        putchar('*');
        Sleep(speedforeyes);
        CUP(v1[i].car.x, v1[i].car.y);
        putchar(' ');
        v1[i].car.x -= 1;
    }
}

char streetdir(CAR v1[], int i) {
    if (((v1[i].car.y) == 0) && map[v1[i].car.x][v1[i].car.y].direction == BI || (v1[i].car.y == (ybuild * 4)) && map[v1[i].car.x][v1[i].car.y].direction == BI) 
    {
        /*
        -check bi-directional first
        -if it is, return a 'B'
        -this function is for checking the directions the streets allow
        */
        return 'B';
    }
    else if (((v1[i].car.y / 4) % 2 == 1) && map[v1[i].car.x][v1[i].car.y].direction == RIGHT) 
    {
        //move right
        return 'R';
    }
    else if (((v1[i].car.y / 4) % 2 == 0) && map[v1[i].car.x][v1[i].car.y].direction == LEFT) 
    {
        //move left
        return 'L';
    }
}
char avenuedir(CAR v1[], int i) {

    if (((v1[i].car.x) == 0) && (map[v1[i].car.x][v1[i].car.y].direction == BI) || v1[i].car.x == (xbuild * 4) && (map[v1[i].car.x][v1[i].car.y].direction == BI))
    {
        /*
        -check bi-directional first
        -if it is, return a 'B'
        -this function is for checking the directions the avenues allow
        */

        return 'B';
    }
    else if (((v1[i].car.x / 4) % 2 == 1) && map[v1[i].car.x][v1[i].car.y].direction == DOWN)
    {
        //move down (ODD)
        return 'D';
    }
    else if (((v1[i].car.x / 4) % 2 == 0) && map[v1[i].car.x][v1[i].car.y].direction == UP) 
    {
        //move up (EVEN)
        return 'U';
    }
}


