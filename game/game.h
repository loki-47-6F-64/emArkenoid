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

// Ball delay
#define DELAY_FAST_X 0
#define DELAY_SLOW_X 1

#define DELAY_FAST_Y 0
#define DELAY_SLOW_Y 1
// State of current game.
struct _gameState {
    int game_over;

    // The amount of bricks currently in-game
    int bricks_left;

    // Max delays of ball
    int delay_ball_x;
    int delay_ball_y;
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
    Point delay;

    Point direction;

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

int isGameOver();
#endif	/* GAME_H */

