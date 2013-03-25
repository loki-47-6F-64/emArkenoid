#include "ioTree.h"
#include "../emAssert.h"
#include "../emMalloc.h"

node* binAllocNode(void *data, void *key) {
    node *tree = emMalloc(sizeof (node));
    tree->data = data;
    tree->key = key;

    tree->left = tree->right = 0;
}

ioTree* binAllocTree(int (*compare)(void*, void*)) {
    ioTree *tree = emMalloc(sizeof (ioTree));

    tree->compare = compare;
    tree->root = 0;
}

int binCopies(ioTree *tree, void *key) {
    int result, x = -1;
    node *curr = tree->root;

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
    node *parent, *curr = tree->root;

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

int binGetAll(ioTree *tree, void *key, void *buf, unsigned int sizeData, unsigned int sizeBuf) {
    int result, x;

    node *curr = tree->root;
    x = 0;
    while( curr && x < sizeBuf ) {
        result = tree->compare(key, curr->key);

        if (!result) {
            emMemcpy(buf + x++*sizeData, curr->data, sizeData);
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
    node *curr = tree->root;

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
node *getSuccessor(node *parent, node *curr) {
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
    node *parent = 0, *curr = tree->root;
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
            emFree(curr);
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

void binFree(node *subTree) {
    if (!subTree)
        return;

    binFree(subTree->left);
    binFree(subTree->right);

    emFree(subTree);
}

void binFreeTree(ioTree *tree) {
    if (!tree->root)
        return;

    binFree(tree->root->left);
    binFree(tree->root->right);

    emFree(tree->root);
    emFree(tree);
}