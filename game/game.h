/* 
 * File:   game.h
 * Author: Loki
 *
 * Created on 07 March 2013, 23:44
 */

#ifndef GAME_H
#define	GAME_H

//#define _DEBUG_COLLISION

// Used often. Macro it for clarity
#define MAX_COLLPOINT_BUF( brick ) (brick->width+(brick->height)*2)

/* The engine of the game.
 * Handle Movement, Collision detection and Graphics.
 */

typedef enum ObjType {
    PLAYER,
    BRICK_SIDE,
    BRICK_TOP,
    DEFAULT
} ObjType;

struct Object;

// State of current game.
struct _gameState {
    int game_over;
    int delay_ball;
};

extern struct _gameState gameState;

typedef struct Point {
    int x;
    int y;

} Point;

typedef struct CollPoint {
    int x;
    int y;


    ObjType type;
    struct Object *container;
} CollPoint;

typedef struct Object {
    Point origin;
    CollPoint *collPoint; // Points used for collision detection.

    int height;
    int width;
} Object;

typedef struct Ball {
    // Emulate inheritence
    Object base;
    Point direction;

    int speed;

    unsigned char *bitmap;
} Ball;

Object* allocBrick(int x, int y, int width, int height);
void freeBrick(Object *brick);

Ball* allocBall(int x, int y, int width, int height, unsigned char *bitmap);
void freeBall(Ball *ball);


void loadBrick(Object*);
void clearBrick(Object*);

int gameMain(void);
void initGame(void);

void moveLeft(Object*);
void moveRight(Object*);

void moveBall(Ball*);
// Detect collision at point.
CollPoint* collide(CollPoint *collPoint, unsigned int size);

/* An addition to the binary tree specificly designed to reorder nodes within the binary tree.
 * Because the positions of the points are used as keys, when one point gets moved, the other points get moved as well.
 * For this reason, BinReassign needs to be tailored for collision detection.
 * That is why it is placed in game.c, not ioTree.c */
struct ioTree;
void binReassign(struct ioTree* tree, void* currKey, void* newKey);

#endif	/* GAME_H */

