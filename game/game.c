#include "game.h"
#include "dogmBuffer.h"

#include "../interrupts.h"
#include "DogM.h"
#include "../emMalloc.h"
#include "../ioTree/ioTree.h"
#include "../emAssert.h"
ioTree *collTree;

volatile ButtonDown button;

extern unsigned char ball[];
extern unsigned int ball_width;
extern unsigned int ball_height;

#define MAX_DELAY_BALL 1
struct _gameState gameState;

Object *player;
Ball *ball_p;

// Used by ioTree

int compare(void* dataKey, void* currKey) {
    CollPoint *data = (CollPoint*) dataKey;
    CollPoint *curr = (CollPoint*) currKey;

    if (data->x < curr->x)
        return -1;
    else if (data->x > curr->x)
        return 1;

    else if (data->y < curr->y)
        return -1;
    else if (data->y > curr->y)
        return 1;

    return 0;
}

// Used by ioTree

__inline int compContainer(void* dataKey, void* currKey) {
    return ((CollPoint*) dataKey)->container != ((CollPoint*) currKey)->container;
}

//

void initCollpoints_brick(Object *brick) {
    int x;
    int middle_y = brick->height / 2 + brick->height %2;

    CollPoint *colPoint = brick->collPoint;

    for (x = 0; x < brick->width; x++) {
        colPoint[x].container = brick;
        colPoint[x].x = brick->origin.x + x;
        colPoint[x].y = brick->origin.y + middle_y;

        colPoint[x].type = BRICK_TOP;
/*
        colPoint[x + brick->width].container = brick;
        colPoint[x + brick->width].x = brick->origin.x + x;
        colPoint[x + brick->width].y = brick->origin.y + brick->height - 1;

        colPoint[x + brick->width].type = BRICK_TOP;
*/
        binInsert(collTree, &colPoint[x], &colPoint[x]);
//        binInsert(collTree, &colPoint[x + brick->width], &colPoint[x + brick->width]);
    }

    x = brick->width;

    int y = 0;
    while (y < brick->height) {
        colPoint[x + y].container = brick;
        colPoint[x + y].x = brick->origin.x;
        colPoint[x + y].y = brick->origin.y + y + 1;

        colPoint[x + y].type = BRICK_SIDE;

        colPoint[x + y + brick->height].container = brick;
        colPoint[x + y + brick->height].x = brick->origin.x + brick->width - 1;
        colPoint[x + y + brick->height].y = brick->origin.y + y + 1;

        colPoint[x + y + brick->height].type = BRICK_SIDE;

        binInsert(collTree, &colPoint[x + y], &colPoint[x + y]);
        binInsert(collTree, &colPoint[x + y + brick->height], &colPoint[x + y + brick->height]);
        y++;
    }
}

void initCollpoints_player(Object *brick) {
    int x;
    int middle_y = brick->height / 2 + brick->height %2;

    CollPoint *colPoint = brick->collPoint;

    for (x = 0; x < brick->width; x++) {
        colPoint[x].container = brick;
        colPoint[x].x = brick->origin.x + x;
        colPoint[x].y = brick->origin.y + middle_y;

        colPoint[x].type = PLAYER;
/*
        colPoint[x + brick->width].container = brick;
        colPoint[x + brick->width].x = brick->origin.x + x;
        colPoint[x + brick->width].y = brick->origin.y + brick->height - 1;

        colPoint[x + brick->width].type = PLAYER;
*/
        binInsert(collTree, &colPoint[x], &colPoint[x]);
//        binInsert(collTree, &colPoint[x + brick->width], &colPoint[x + brick->width]);
    }

    x = brick->width;

    int y = 0;
    while (y < brick->height) {
        colPoint[x + y].container = brick;
        colPoint[x + y].x = brick->origin.x;
        colPoint[x + y].y = brick->origin.y + y + 1;

        colPoint[x + y].type = PLAYER;


        colPoint[x + y + brick->height].container = brick;
        colPoint[x + y + brick->height].x = brick->origin.x + brick->width - 1;
        colPoint[x + y + brick->height].y = brick->origin.y + y + 1;

        colPoint[x + y + brick->height].type = PLAYER;

        binInsert(collTree, &colPoint[x + y], &colPoint[x + y]);
        binInsert(collTree, &colPoint[x + y + brick->height], &colPoint[x + y + brick->height]);
        y++;
    }
}

void initCollpoints_ball(Object *brick) {
    int x;

    int middle_x = brick->width / 2; // + brick->width % 2;
    int middle_y = brick->height / 2; // + brick->height % 2;

    CollPoint *collPoint = brick->collPoint;
    collPoint[0].x = brick->origin.x;
    collPoint[0].y = brick->origin.y + middle_y;

    collPoint[1].x = brick->origin.x + middle_x;
    collPoint[1].y = brick->origin.y;

    collPoint[2].x = brick->origin.x + middle_x;
    collPoint[2].y = brick->origin.y + brick->height - 1;

    collPoint[3].x = brick->origin.x + brick->width - 1;
    collPoint[3].y = brick->origin.y + middle_y;

    for (x = 0; x < 4; x++) {
        collPoint[x].container = brick;
        binInsert(collTree, &collPoint[x], &collPoint[x]);
    }
}

Object* allocBrick(int x, int y, int width, int height) {
    Object *brick = emMalloc(sizeof (Object));

    brick->height = height;
    brick->width = width;

    brick->origin.x = x;
    brick->origin.y = y;

    brick->collPoint = emMalloc(sizeof (CollPoint) * MAX_COLLPOINT_BUF(brick));
    //AssertFailed("0",5,"0");
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
    //AssertFailed("0",5,"0");
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
    ball->speed = 1;

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

CollPoint* collide(CollPoint *collPoint, unsigned int size) {
    CollPoint * collPointBuf[10];

    unsigned int x;
    for (x = 0; x < size; x++) {

        // If collision
        if (binGetAll(collTree, &collPoint[x], collPointBuf,
                sizeof (CollPoint),
                sizeof (collPointBuf) / sizeof (CollPoint*)) > 1) {
            // Return other collisionPoint
            return (collPointBuf[0]->type == collPoint->type) ? collPointBuf[1] : collPointBuf[0];
        }
    }

    return 0;
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

// Moves collision points and updates collTree.

void movePoints(CollPoint *p, unsigned int size, int x, int y) {
    int i;

    CollPoint tmp;

    for (i = 0; i < size; i++) {
        tmp = p[i];

        tmp.x += x;
        tmp.y += y;

        // update collTree
        binReassign(collTree, &p[i], &tmp);
    }
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

    base->origin.x += ball->direction.x;
    base->origin.y += ball->direction.y;

    movePoints(base->collPoint, 4, ball->direction.x, ball->direction.y);

    loadBitmap(ball->bitmap, base->origin.x, base->origin.y, base->width, base->height / base->width);
}

// Give a node a new key.

void binReassign(ioTree* tree, void* currKey, void* newKey) {
    int result = 0;

    // First detach node
    Node *parent = 0, *curr = tree->root;
    while (curr) {
        result = tree->compare(currKey, curr->key);

        if (!result) {
            // ===================================================
            // If current point doesn't have the same container as currKey.
            if (curr->right &&
                    ((CollPoint*) curr->key)->container != ((CollPoint*) currKey)->container) {
                assert(curr->right);

                parent = curr;
                curr = curr->right;
                continue;
            }
            // ===================================================
            void *data = curr->data;
            void *key = curr->key;
            // If curr is a parent
            if (curr->left || curr->right) {
                if (!parent && !curr->right) {
                    tree->root = curr->left;
                } else {
                    Node *successor = getSuccessor(parent, curr);

                    curr->data = successor->data;
                    curr->key = successor->key;

                    curr = successor;
                }
            } else if (parent) {
                if (parent->left == curr) {
                    parent->left = 0;
                } else {
                    parent->right = 0;
                }
            }

            // =========================================================
            curr->data = data;
            curr->key = key;

            CollPoint *p = key;
            CollPoint *pNew = newKey;

            // p->container = pNew->container;

            p->x = pNew->x;
            p->y = pNew->y;
            // =========================================================
            curr->left = 0;
            curr->right = 0;
            break;
        }
        parent = curr;

        if (result < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    // Node is detached.

    // If root is NULL
    assert(!result);
    assert(curr);
    // Reattach Node
    Node *child = curr;

    curr = tree->root;
    while (curr) {
        result = tree->compare(child->key, curr->key);

        parent = curr;
        if (!result)
            curr = curr->right;
        else if (result < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }
    assert(parent != child);

    if (result < 0)
        parent->left = child;
    else
        parent->right = child;
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
    if (!gameState.delay_ball--) {
        moveBall(ball_p);
        gameState.delay_ball = MAX_DELAY_BALL;



        loadBoundary();

        // If ball hit boundary
        if (ball_p->base.origin.x + ball_p->base.width >= 128 ||
                ball_p->base.origin.x <= 0) {
            ball_p->direction.x *= -1;
        }

        if (ball_p->base.origin.y <= 0) {
            ball_p->direction.y *= -1;
        }
        else if(ball_p->base.origin.y + ball_p->base.height >= 64) {
            gameState.game_over = 1;
            return;
        }

        // Check for collision with ball_p and any other object
        CollPoint *collPoint = collide(ball_p->base.collPoint, 4);
        if (collPoint) {
            switch (collPoint->type) {
                case PLAYER:
                    ball_p->direction.y *= -1;

                    break;
                case BRICK_SIDE:
                    ball_p->direction.x *= -1;

                    freeBrick(collPoint->container);
                    break;
                case BRICK_TOP:
                    ball_p->direction.y *= -1;

                    freeBrick(collPoint->container);
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}

initMap() {
    ball_p = allocBall(15, 15, ball_width, ball_width, ball);
    player = allocPlayer(30, 52, 10, 3);

    ball_p->direction.x = 1;
    ball_p->direction.y = -1;

    loadBall(ball_p);
    loadBrick(player);

    int x;
    for(x = 0; x < 10; x++) {
        loadBrick(allocBrick(x*5 + 30, (x%2)*4 + 10, 10, 3));
    }
    loadBoundary();
}
void initGame() {
    gameState.game_over = 0;
    gameState.delay_ball = MAX_DELAY_BALL;

    collTree = binAllocTree(compare);

    clearDisplay();

    initMap();
}