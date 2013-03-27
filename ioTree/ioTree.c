#include "ioTree.h"
#include "../emAssert.h"
#include "../emMalloc.h"

/**
 * Initialy, ioTree used emMalloc to allocate new memory.
 * However, it uses to much extra space to keeps taps on all nodes seperately.
 */

// 22 Collpoints * Number of objects + 4 collPoints of ball.
#define MAX_NODE 22*11+4

Node node[MAX_NODE];
Node *next;

Node* binAllocNode(void *data, void *key) {
    // Make sure next is within bounds of node array.
    assert(next < node + MAX_NODE);

    Node *tree = next++;
    tree->data = data;
    tree->key = key;

    tree->left = tree->right = 0;
}

ioTree* binAllocTree(int (*compare)(void*, void*)) {
    // Initialize pointer to node.
    next = node;
    
    ioTree *tree = emMalloc(sizeof (ioTree));

    tree->compare = compare;
    tree->root = 0;
}

void binFree(Node *curr) {
    assert(next > node);

    while(curr < next) {
        *curr = *(++curr);
    }

    next--;
}

int binCopies(ioTree *tree, void *key) {
    int result, x = -1;
    Node *curr = tree->root;

    while (curr) {
        result = tree->compare(key, curr->key);

        if (!result) {
            curr = curr->right;
            x++;
        } else if (result < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return x;
}

int binInsert(ioTree* tree, void *data, void *key) {
    if (!tree->root) {
        tree->root = binAllocNode(data, key);
        return 1;
    }

    int result = 0;
    Node *parent, *curr = tree->root;

    while (curr) {
        result = tree->compare(key, curr->key);

        parent = curr;
        if (!result)
            curr = curr->right;
        else if (result < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }


    if (result < 0)
        parent->left = binAllocNode(data, key);
    else
        parent->right = binAllocNode(data, key);

    return 1;
}

// Put all pointers to data that match key in data
int binGetAll(ioTree *tree, void *key, void *buf, unsigned int sizeData, unsigned int sizeBuf) {
    int result, x;

    Node *curr = tree->root;
    x = 0;
    while( curr && x < sizeBuf ) {
        result = tree->compare(key, curr->key);

        if (!result) {

            // Copy pointers to data
            emMemcpy(buf + x++*sizeData, &curr->data, sizeData);
            curr = curr->right;
        }
        else if (result < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return x;
}

void* binGet(ioTree* tree, void* key) {
    int result;
    Node *curr = tree->root;

    while (curr) {
        result = tree->compare(key, curr->key);

        if (!result)
            return curr->data;
        else if (result < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return 0;
}

/* When a node to be freed is a parent, a successor must be found.*/
Node *getSuccessor(Node *parent, Node *curr) {
    if (!curr->right) {
        // If curr is not root
        if (parent) {
            if (parent->left == curr) {
                parent->left = curr->left;
            } else {
                parent->right = curr->left;
            }
        } else {
            curr = curr->left;
        }
        return curr;
    }

    parent = curr;
    curr = curr->right;

    if (!curr->left) {
        parent->right = curr->right;
        return curr;
    }

    parent = curr;
    while (curr->left) {
        parent = curr;
        curr = curr->left;
    }

    parent->left = curr->right;
    return curr;
}

// ======================================
// Evil, not fully independent, but necessary.
extern __inline int compContainer( void* dataKey, void* currKey );
// ======================================
int binRemove(ioTree* tree, void* key) {
    int result = 0;

    // First detach node
    Node *parent = 0, *curr = tree->root;
    while (curr) {
        result = tree->compare(key, curr->key);

        if (!result) {
// ======================================
            if(compContainer(curr->key, key)) {
                curr = curr->right;
                continue;
            }
// ======================================
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
            binFree(curr);
            break;
        }
        parent = curr;

        if (result < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    // curr is non-zero if success
    return (int) curr;
}

// Free subtree.
void binFreeSubTree(Node *subTree) {
    if (!subTree)
        return;

    binFreeSubTree(subTree->left);
    binFreeSubTree(subTree->right);

    binFree(subTree);
}

// Free entire tree.
void binFreeTree(ioTree *tree) {
    emFree(tree->root);

    // reset tree.
    next = node;
}