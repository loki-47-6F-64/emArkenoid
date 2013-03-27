/* 
 * File:   ioTree.h
 * Author: Loki
 *
 * Created on 09 March 2013, 21:28
 */

#ifndef IOTREE_H
#define	IOTREE_H

typedef struct Node {
    void *data;
    void *key;

    struct Node* left;
    struct Node* right;
} Node;

typedef struct ioTree {
    int (*compare)(void*, void*);
    Node *root;
}ioTree;

// Returns the number of copies of key.
// Starts at 0
int binCopies( ioTree*, void *key );

void binFreeTree(ioTree *tree);

Node* binAllocNode( void *data, void *key );
ioTree* binAllocTree( int (*compare)(void*, void*));

void *binGet( ioTree *tree, void *key );

// Puts all data in buf.
// Returns number of data put in buf.
// sizeData = size of data in bytes
// sizeBuf = number of max elements in buffer
int binGetAll(ioTree *tree, void *key, void *buf, unsigned int sizeData, unsigned int sizeBuf);

int binInsert( ioTree *tree, void *data, void *key );

int binRemove( ioTree *tree, void *key );

Node *getSuccessor( Node *parent, Node *curr );
#endif	/* IOTREE_H */

