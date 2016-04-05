//
//  main.c
//  Knights tour, each tile, one time only
//
//  Created by Guy Erb on 6/29/15.
//  Copyright (c) 2015 Guy Erb. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>


#define BOARD_SUCCESS	1
#define BOARD_FAILURE	0

#define NUM_COLUMNS	8
#define NUM_ROWS	8
#define NUM_TILES	(NUM_ROWS * NUM_COLUMNS)

int board[NUM_ROWS][NUM_COLUMNS] = {{0,0}};
int tiles_visited = 0;
int total_visits = 0;

int is_empty(int x, int y)
{
    int empty = 0;

    if (board[x][y] == 0)
        empty = 1;

    return empty;
}

int is_valid(int x, int y)
{
    int valid = 0;

    if (x >= 0 && x < NUM_ROWS)
        if (y >= 0 && y < NUM_COLUMNS)
            valid = 1;

    return valid;
}

int is_available(int x, int y)
{
    int avail = 0;

    if (is_valid(x,y) && is_empty(x,y))
        avail = 1;

    return avail;
}

void set_tile(int x, int y, int value)
{
    board[x][y] = value;
}

void clear_tile(int x, int y)
{
    if (!is_valid(x,y)) {
        printf("%s invalid tile (%d,%d)\n", __func__, x, y);
        exit(EXIT_FAILURE);	/* WTF */
    }
    if (is_empty(x,y)) {
        printf("%s already cleared (%d,%d)\n", __func__, x, y);
        exit(EXIT_FAILURE);	/* WTF */
    }
    
    set_tile(x, y, 0);
}

void mark_tile(int x, int y)
{
    if (!is_valid(x,y)) {
        printf("%s invalid tile (%d,%d)", __func__, x, y);
        exit(EXIT_FAILURE);	/* WTF */
    }
    set_tile(x, y, 1);
}

void visit_tile(int x, int y)
{
    if (!is_valid(x,y)) {
        printf("%s invalid tile (%d,%d)", __func__, x, y);
        exit(EXIT_FAILURE);	/* WTF */
    }
    if (!is_empty(x,y)) {
        printf("%s already set (%d,%d)", __func__, x, y);
        exit(EXIT_FAILURE);	/* WTF */
    }

    set_tile(x, y, 1);
}

int next_move(int *x, int *y, int tries)
{
	int newx, newy;
	int avail = 0;

    switch (tries) {
    case 0:
	    newx = *x-1; newy = *y-2;
	    break;
    case 1:
	    newx = *x-1; newy = *y+2;
	    break;
    case 2:
	    newx = *x+1; newy = *y-2;
	    break;
    case 3:
	    newx = *x+1; newy = *y+2;
	    break;
    case 4:
	    newx = *x-2; newy = *y-1;
	    break;
    case 5:
	    newx = *x-2; newy = *y+1;
	    break;
    case 6:
	    newx = *x+2; newy = *y-1;
	    break;
    case 7:
	    newx = *x+2; newy = *y+1;
	    break;
    default:
	    printf("%s: bad value %d\n", __func__, tries);
	    exit(EXIT_FAILURE);	/* WTF */
    }

    avail = is_available(newx, newy);

/*     printf("%s: (%d,%d)->(%d,%d) visited=%d try=%d avail=%d\n", __func__,  */
/* 	   *x, *y, newx, newy, tiles_visited, tries, avail); */

    if (avail) {
        *x = newx;
        *y = newy;
    }

    return avail;
}

int visit(int x, int y)
{
    int status = BOARD_FAILURE;
    int newx, newy;
    int tries = 0; 			/* knight can try eight positions */

    visit_tile(x, y);
    tiles_visited++;
    total_visits++;

    printf("%s(%x,%d): tiles_visited=%d\n", __func__, x, y, tiles_visited);

    if (tiles_visited == NUM_TILES) {
    	printf("We did it!!\n");
	   return BOARD_SUCCESS;
    }

    newx = x;
    newy = y;

    do {
	    if (next_move(&newx, &newy, tries) != 0) {
		    status = visit(newx, newy);
		    newx = x;
		    newy = y;
	    }
	    tries++;
    } while ( tries <= 7 && status != BOARD_SUCCESS );

    /* print our path as we pop back up the stack */
    if (status == BOARD_SUCCESS)
	    printf("%s: (%d,%d)\n", __func__, x, y);
    else {
	    clear_tile(x, y);
	    tiles_visited--;
    }

    return status;
}

int main (int argc, char * argv[])
{
    printf("knights tour: brute force! Let's do this thing!\n");
    visit(0, 0);
    printf("completed with %d total visits\n", total_visits);
    
}
