#include "../emAssert.h"
#include "game.h"
#include "collision.h"
#include "../ioTree/ioTree.h"

ioTree *collTree;

// Used by ioTree
int compare(void* dataKey, void* currKey) {
    CollPoint *data = (CollPoint*) dataKey;
    CollPoint *curr = (CollPoint*) currKey;

    if (data->y < curr->y)
        return -1;
    else if (data->y > curr->y)
        return 1;

    else if (data->x < curr->x)
        return -1;
    else if (data->x > curr->x)
        return 1;

    return 0;
}

// Used by ioTree
__inline int compContainer(void* dataKey, void* currKey) {
    return ((CollPoint*) dataKey)->container != ((CollPoint*) currKey)->container;
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

// Check for collision
// Returns NULL if no collsion detected.
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

void initCollpoints_brick(Object *brick) {
    int x;
    int middle_y = brick->height / 2 + brick->height % 2;

    CollPoint *colPoint = brick->collPoint;

    for (x = 0; x < brick->width; x++) {
        colPoint[x].container = brick;
        colPoint[x].x = brick->origin.x + x;
        colPoint[x].y = brick->origin.y + middle_y;

        colPoint[x].type = BRICK_TOP;

        binInsert(collTree, &colPoint[x], &colPoint[x]);
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
    int middle_y = brick->height / 2 + brick->height % 2;

    CollPoint *colPoint = brick->collPoint;

    for (x = 0; x < brick->width; x++) {
        colPoint[x].container = brick;
        colPoint[x].x = brick->origin.x + x;
        colPoint[x].y = brick->origin.y + middle_y;

        colPoint[x].type = PLAYER;

        binInsert(collTree, &colPoint[x], &colPoint[x]);
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

void handleCollision(Ball *ball) {
    // If ball hit boundary
    if (!ball->delay.x &&
            (ball->base.origin.x + ball->base.width >= 128 ||
            ball->base.origin.x <= 0))
    {
        ball->direction.x *= -1;
    }

    if (!ball->delay.y &&
            (ball->base.origin.y <= 0))
    {
        ball->direction.y *= -1;
    } else if (ball->base.origin.y + ball->base.height >= 64) {
        gameState.game_over = 1;
        return;
    }

    // Check for collision with ball_p and any other object
    CollPoint *collPoint = collide(ball->base.collPoint, 4);
    if (collPoint) {
        switch (collPoint->type) {
            case PLAYER:
                // If ball is not moved on its y axis, it could hit the player two times.
                if(!ball->delay.y) {
                    changeDelay(ball);
                }
                break;
            case BRICK_SIDE:
                ball->direction.x *= -1;

                freeBrick(collPoint->container);
                break;
            case BRICK_TOP:
                ball->direction.y *= -1;

                freeBrick(collPoint->container);
                break;
            default:
                assert(0);
        }
    }
}