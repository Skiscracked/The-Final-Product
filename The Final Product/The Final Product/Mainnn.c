#include "Emulation.h"

FILE* infile;

int main(int argc, char* argv[]) {

    /*
    -AEDV is of type car, it has a pointer to a pointer of type cell, called LOCATE
    -Here we are defining the size of the array double pointer LOCATE
    -We are going to use this to compare the location of the car on the map to the CELL** map,
    determiing where we are on the map.

    */

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    if (fopen_s(&infile, argv[1], "r") != 0) {
        fprintf(stderr, "Error opening file >%s< - possibly missing\n", argv[1]);
        return 1;
    }

    struct Building* head = NULL;
    char b_info[100];

    for (int i = 0; i < 1; i++) {
        if (fgets(b_info, sizeof(b_info), infile) != NULL) {
            sscanf(b_info, "# X bldgs %d # Y bldgs %d", &xbuild, &ybuild);
        }
    }
    /*
     - Setup Main screen based on window size
     - Populate map (sparse)
    */
    long outmode;

    /* Microsoft specific commands: */
    if ((scrout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
        terminate("Can't open output");

    if (!GetConsoleMode(scrout, &outmode))
        terminate("Can't get old console mode");

    outmode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(scrout, outmode))
        terminate("Can't set console mode");

    /* Switch to VT-100 mode */
    screen_size();

    create_map(); /*Function call to create the map*/

    populate_map();
    eventlist();
    init_custheader_and_makerelative();
    execute_event();
    check_kb();
    for (int i = 0; i < numofv; i++) {
        move(AEDV, i);
    }
    print_msg("Done!");

    (void)getchar();

}