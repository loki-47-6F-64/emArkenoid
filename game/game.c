#include "game.h"
#include "collision.h"

#include "DogM.h"
#include "dogmBuffer.h"

#include "../interrupts.h"
#include "../emMalloc.h"
#include "../emAssert.h"


volatile ButtonDown button;

extern unsigned char ball[];
extern unsigned int ball_width;
extern unsigned int ball_height;

struct _gameState gameState;

Object *player;
Ball *ball_p;

Object* allocBrick(int x, int y, int width, int height) {
    Object *brick = emMalloc(sizeof (Object));

    brick->height = height;
    brick->width = width;

    brick->origin.x = x;
    brick->origin.y = y;

    brick->collPoint = emMalloc(sizeof (CollPoint) * MAX_COLLPOINT_BUF(brick));

    initCollpoints_brick(brick);

    return brick;
}

Object* allocPlayer(int x, int y, int width, int height) {
    Object *player = emMalloc(sizeof (Object));

    player->height = height;
    player->width = width;

    player->origin.x = x;
    player->origin.y = y;

    player->collPoint = emMalloc(sizeof (CollPoint) * MAX_COLLPOINT_BUF(player));
    
    initCollpoints_player(player);

    return player;
}

void freeBrick(Object *brick) {
    int x, size = MAX_COLLPOINT_BUF(brick);

    clearBrick(brick);
    // Remove collPoints from tree.
    for (x = 0; x < size; x++) {
        binRemove(collTree, &brick->collPoint[x]);
    }

    emFree(brick->collPoint);
    emFree(brick);

    gameState.bricks_left--;
}

Ball* allocBall(int x, int y, int width, int height, unsigned char *bitmap) {
    Ball *ball = emMalloc(sizeof (Ball));

    Object *brick = &(ball->base);

    brick->origin.x = x;
    brick->origin.y = y;

    brick->height = height;
    brick->width = width;
    brick->collPoint = emMalloc(sizeof (CollPoint)*4);

    initCollpoints_ball(brick);
    ball->bitmap = bitmap;

    ball->delay.x = gameState.delay_ball_x;
    ball->delay.y = gameState.delay_ball_y;

    ball->direction.x = 1;
    ball->direction.y = 1;

    return ball;
}

void freeBall(Ball *ball) {
    int x, size = 4;

    Object *brick = &ball->base;

    // Remove collPoints from tree.
    for (x = 0; x < size; x++) {
        binRemove(collTree, &brick->collPoint[x]);
    }

    emFree(brick->collPoint);
    emFree(brick);
}

void loadBoundary() {
    // Generate boundaries
    int x;
    for (x = 0; x < 128; x++) {
        setPixel(x, 0);
        setPixel(x, 63);
    }

    int y;
    for (y = 0; y < 64; y++) {
        setPixel(0, y);
        setPixel(127, y);
    }
}

void clearBoundary() {
    // Generate boundaries
    int x;
    for (x = 0; x < 128; x++) {
        clearPixel(x, 0);
        clearPixel(x, 64);
    }

    int y;
    for (y = 0; y < 64; y++) {
        clearPixel(0, y);
        clearPixel(127, y);
    }
}

void loadBrick(Object *brick) {
    int x, y, rowL, columnL;

    columnL = brick->origin.x;
    rowL = brick->origin.y;

#ifdef _DEBUG_COLLISION
    for (y = 0; y < MAX_COLLPOINT_BUF(brick); y++) {
        setPixel(brick->collPoint[y].x, brick->collPoint[y].y);
    }
#else
    y = 0;
    while (y < brick->height) {
        for (x = 0; x < brick->width; x++) {
            setPixel(columnL + x, rowL + y);
        }
        y++;
    }
#endif
}

void clearBrick(Object* brick) {
    int x, y, rowL, columnL;

    columnL = brick->origin.x;
    rowL = brick->origin.y;

#ifdef _DEBUG_COLLISION
    for (y = 0; y < MAX_COLLPOINT_BUF(brick); y++) {
        clearPixel(brick->collPoint[y].x, brick->collPoint[y].y);
    }
#else
    y = 0;
    while (y < brick->height) {
        for (x = 0; x < brick->width; x++) {
            clearPixel(columnL + x, rowL + y);
        }
        y++;
    }
#endif
}

void loadBall(Ball *ball) {
    Object *brick = &ball->base;
    int x, y, rowL, columnL;

    columnL = brick->origin.x;
    rowL = brick->origin.y;

#ifdef _DEBUG_COLLISION
    for (y = 0; y < 4; y++) {
        setPixel(brick->collPoint[y].x, brick->collPoint[y].y);
    }
#else
    loadBitmap(ball->bitmap, columnL, rowL, brick->width, brick->height / brick->width);
#endif
}

void clearBall(Ball *ball) {
    Object *brick = &ball->base;
    int x, y, rowL, columnL;

    columnL = brick->origin.x;
    rowL = brick->origin.y;

#ifdef _DEBUG_COLLISION
    for (y = 0; y < 4; y++) {
        clearPixel(brick->collPoint[y].x, brick->collPoint[y].y);
    }
#else
    clearBitmap(ball->bitmap, columnL, rowL, brick->width, brick->height / brick->width);
#endif
}

void moveLeft(Object* brick) {
    if (brick->origin.x <= 0) {
        return;
    }

    clearBrick(brick);

    brick->origin.x--;

    //assert(!(binGet(collTree, &brick->origin)));

    //assert(binCopies(collTree, &brick->origin) < 0);

    movePoints(brick->collPoint,
            MAX_COLLPOINT_BUF(brick),
            -1, 0);

    collide(brick->collPoint, MAX_COLLPOINT_BUF(brick));

    loadBrick(brick);
}

void moveRight(Object* brick) {
    if (brick->origin.x + brick->width >= 128) {
        return;
    }


    clearBrick(brick);

    brick->origin.x++;

    //assert(binCopies(collTree, &brick->origin) <= 0);

    movePoints(brick->collPoint,
            MAX_COLLPOINT_BUF(brick),
            1, 0);

    collide(brick->collPoint, MAX_COLLPOINT_BUF(brick));

    loadBrick(brick);
}

void moveBall(Ball *ball) {
    Object *base = &ball->base;

    // Bitmap height == base->height / base->width
    clearBitmap(ball->bitmap, base->origin.x, base->origin.y, base->width, base->height / base->width);

    base->origin.x += ball->delay.x ? 0 : ball->direction.x;
    base->origin.y += ball->delay.y ? 0 : ball->direction.y;

    movePoints(base->collPoint, 4,
            ball->delay.x ? 0 : ball->direction.x,
            ball->delay.y ? 0 : ball->direction.y);

    loadBitmap(ball->bitmap, base->origin.x, base->origin.y, base->width, base->height / base->width);
}

void changeDelay(Ball *ball) {    
    int playerL = player->width / 4;
    int playerR = player->width - player->width / 4;

    int ball_x = ball->base.origin.x - player->origin.x;;

    if(ball_x < playerL) {
        gameState.delay_ball_x = DELAY_FAST_X;
        gameState.delay_ball_y = DELAY_SLOW_Y;

        ball->direction.x = -1;
    }
    else if(ball_x > playerR) {
        gameState.delay_ball_x = DELAY_FAST_X;
        gameState.delay_ball_y = DELAY_SLOW_Y;

        ball->direction.x = 1;
    }
    else {
        gameState.delay_ball_x = DELAY_SLOW_X;
        gameState.delay_ball_y = DELAY_FAST_Y;
    }

    ball->direction.y = -1;
}

int gameMain() {
    if (button.right) {
        //assert(1 - 1);
        //writeString(boldFont, 0x00, 0x00, ":(");
        moveRight(player);
        // updateScreen(dogmBuffer, 0, 0, 8, 128);
    } else if (button.left) {
        //assert(0);
        moveLeft(player);
        // updateScreen(dogmBuffer, 0, 0, 8, 128);
    }
    if (!ball_p->delay.x || !ball_p->delay.y) {

        moveBall(ball_p);

        loadBoundary();

        // Check for collision and act accordenly.
        handleCollision(ball_p);
    }

    if (!ball_p->delay.x) {
        ball_p->delay.x = gameState.delay_ball_x;
    } else {
        ball_p->delay.x--;
    }

    if (!ball_p->delay.y) {
        ball_p->delay.y = gameState.delay_ball_y;
    } else {
        ball_p->delay.y--;
    }

    return 0;
}

int isGameOver() {
    if(gameState.game_over) {
        clearDisplay();

        writeString(boldFont, 0x01, 0x03, "Game over...");
        writeString(boldFont, 0x03, 0x03, "Muhahaha >:)");
        return 1;
    }
    else if(!gameState.bricks_left) {
        clearDisplay();

        writeString(boldFont, 0x01, 0x03, "Nooooo!");
        writeString(boldFont, 0x03, 0x03, "How dare you!");
        writeString(boldFont, 0x04, 0x03, "You will pay for this. >:/");
        return 1;
    }

    return 0;
}

initMap() {
    ball_p = allocBall(15, 15, ball_width, ball_width, ball);
    player = allocPlayer(30, 52, 16, 3);

    loadBall(ball_p);
    loadBrick(player);

    int x;
    for (x = 0; x < 13; x++) {
        loadBrick(allocBrick(x * 5 + 30, (x % 2)*4 + 10, 10, 3));
        gameState.bricks_left++;
    }
    loadBoundary();
}

void initGame() {
    gameState.game_over = 0;
    gameState.bricks_left = 0;

    gameState.delay_ball_x = DELAY_SLOW_X;
    gameState.delay_ball_y = DELAY_SLOW_Y;

    collTree = binAllocTree(compare);

    clearDisplay();

    initMap();
}