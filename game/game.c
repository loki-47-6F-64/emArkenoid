#include "game.h"
#include "dogmBuffer.h"

#include "../emMalloc.h"
#include "../ioTree/ioTree.h"
#include "../emAssert.h"
ioTree *collTree;

// Used by ioTree
int compare(void* dataKey, void* currKey) {
    point *data = (point*) dataKey;
    point *curr = (point*) currKey;

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

//

void initColpoints_brick(Brick *brick) {
    int x;

    point *colPoint = brick->collPoint;

    for (x = 0; x < brick->width; x++) {
        colPoint[x].container = brick;
        colPoint[x].x = brick->origin.x + x;
        colPoint[x].y = brick->origin.y;

        colPoint[x + brick->width].container = brick;
        colPoint[x + brick->width].x = brick->origin.x + x;
        colPoint[x + brick->width].y = brick->origin.y + brick->height - 1;

        binInsert(collTree, &colPoint[x], &colPoint[x]);
        binInsert(collTree, &colPoint[x + brick->width], &colPoint[x + brick->width]);
    }

    x = brick->width * 2;

    int y = 0;
    while (y < brick->height - 2) {
        colPoint[x + y].container = brick;
        colPoint[x + y].x = brick->origin.x;
        colPoint[x + y].y = brick->origin.y + y + 1;

        colPoint[x + y + brick->height - 2].container = brick;
        colPoint[x + y + brick->height - 2].x = brick->origin.x + brick->width - 1;
        colPoint[x + y + brick->height - 2].y = brick->origin.y + y + 1;

        binInsert(collTree, &colPoint[x + y], &colPoint[x + y]);
        binInsert(collTree, &colPoint[x + y + brick->height - 2], &colPoint[x + y + brick->height - 2]);
        y++;
    }
}

void initColpoints_ball(Brick *brick) {
    int x;

    point *collPoint = brick->collPoint;
    collPoint[0].x = brick->origin.x;
    collPoint[0].y = brick->origin.y + brick->height / 2 + brick->height % 2;

    collPoint[1].x = brick->origin.x + brick->width / 2 + brick->width % 2;
    collPoint[1].y = brick->origin.y;

    collPoint[2].x = brick->origin.x + brick->width / 2 + brick->width % 2;
    collPoint[2].y = brick->origin.y + brick->height - 1;

    collPoint[3].x = brick->width - 1;
    collPoint[3].y = brick->height / 2 + brick->height % 2;

    for (x = 0; x < 4; x++) {
        collPoint[x].container = brick;
        binInsert(collTree, &collPoint[x], &collPoint[x]);
    }
}

Brick* allocBrick(int x, int y, int height, int width) {
    Brick *brick = emMalloc(sizeof (Brick));

    brick->height = height;
    brick->width = width;

    brick->origin.x = x;
    brick->origin.y = y;

    brick->origin.container = brick;

    brick->collPoint = emMalloc(sizeof (point) * MAX_COLLPOINT_BUF(brick));
    //AssertFailed("0",5,"0");
    initColpoints_brick(brick);

    return brick;
}

Ball* allocBall(int x, int y, int height, int width, unsigned char *bitmap) {
    Ball *ball = emMalloc(sizeof (Ball));

    Brick *brick = &(ball->brick);
    brick->height = height;
    brick->width = width;
    brick->collPoint = emMalloc(sizeof (point)*4);

    ball->bitmap = bitmap;
    ball->speed = 1;

    return ball;
}

int collide(point *collPoint, unsigned int size) {
    unsigned int x;
    for (x = 0; x < size; x++) {
        assert(binCopies(collTree, &collPoint[x]) <= 0);
    }

    return 0;
}

void loadBrick(Brick *brick) {
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

void clearBrick(Brick* brick) {
    int x, y, rowL, columnL;

    columnL = brick->origin.x;
    rowL = brick->origin.y;

#ifdef _DEBUG_COLLISION
    for (y = 0; y < (brick->width + (brick->height - 2))*2; y++) {
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

void movePoints(point *p, unsigned int size, int x, int y) {
    int i;

    point tmp;

    for (i = 0; i < size; i++) {
        tmp = p[i];

        tmp.x += x;
        tmp.y += y;

        BinReassign(collTree, &p[i], &tmp);

        /*int x;
        for (x = 0; x < size; x++)
            printf("Double: %ld\n", binCopies(collTree, &p[x])); */
        //p[i].x += x;
        //p[i].y += y;
    }
}

void moveLeft(Brick* brick) {
    if (brick->origin.x <= 0) {
        return;
    }

    clearBrick(brick);

    point p = brick->origin;
    brick->origin.x--;

    //assert(!(binGet(collTree, &brick->origin)));

    //assert(binCopies(collTree, &brick->origin) < 0);

    movePoints(brick->collPoint,
            MAX_COLLPOINT_BUF(brick),
            -1, 0);

    collide(brick->collPoint, MAX_COLLPOINT_BUF(brick));

    loadBrick(brick);
}

void moveRight(Brick* brick) {
    if (brick->origin.x + brick->width >= 128) {
        return;
    }


    clearBrick(brick);

    point p = brick->origin;
    brick->origin.x++;

    //assert(binCopies(collTree, &brick->origin) <= 0);

    movePoints(brick->collPoint,
            MAX_COLLPOINT_BUF(brick),
            1, 0);

    //collide(brick->collPoint, MAX_COLLPOINT_BUF(brick));

    loadBrick(brick);
}

// Give a node a new key.

void BinReassign(ioTree* tree, void* currKey, void* newKey) {
    int result = 0;

    // First detach node
    node *parent = 0, *curr = tree->root;
    while (curr) {
        result = tree->compare(currKey, curr->key);

        if (!result) {
            // ===================================================
            // If current point doesn't have the same container as currKey.
            if (curr->right &&
                    ((point*) curr->key)->container != ((point*) currKey)->container) {
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
                    node *successor = getSuccessor(parent, curr);

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

            point *p = key;
            point *pNew = newKey;

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
    node *child = curr;

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
    // printf("shit\n");
    assert(parent != child);

    if (result < 0)
        parent->left = child;
    else
        parent->right = child;
}

void initGame() {
    collTree = binAllocTree(compare);
}