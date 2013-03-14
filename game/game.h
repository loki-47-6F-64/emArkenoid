/* 
 * File:   game.h
 * Author: Loki
 *
 * Created on 07 March 2013, 23:44
 */

#ifndef GAME_H
#define	GAME_H

#define _DEBUG_COLLISION

// Used often. Macro it for clarity
#define MAX_COLLPOINT_BUF( brick ) ((brick->width+(brick->height - 2))*2)
struct Brick;
/* The engine of the game.
 * Handle Movement, Collision detection and Graphics.
 */
typedef struct point {
    int x;
    int y;

    struct Brick *container;
} point;

typedef struct Brick {
    point origin;
    point *collPoint; // Points used for collision detection.

    int height;
    int width;
} Brick;

typedef struct Ball {
    Brick brick;

    int speed;
    unsigned char *bitmap;
} Ball;

Brick* allocBrick( int x, int y, int height, int width );
void loadBrick( Brick* );
void clearBrick( Brick* );

int gameMain(void);
void initGame(void);

void moveLeft( Brick* );
void moveRight( Brick* );

void moveBall( Ball* );
// Detect collision at point.
int collide(point *collPoint, unsigned int size);

/* An addition to the binary tree specificly designed to reorder nodes within the binary tree.
 * Because the positions of the points are used as keys, when one point gets moved, the other points get moved as well.
 * For this reason, BinReassign needs to be tailored for collision detection.
 * That is why it is placed in game.c, not ioTree.c */
struct ioTree;
void BinReassign( struct ioTree* tree, void* currKey, void* newKey );

#endif	/* GAME_H */

