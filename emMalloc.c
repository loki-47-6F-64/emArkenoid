/* 
 * File:   malloc.c
 * Author: Loki
 *
 * Created on 04 March 2013, 20:05
 */

#include "emMalloc.h"
#include "emAssert.h"

volatile byte emHeap[MAX_MEMORY];

volatile int emptyBlocks;

#define BUF_UNUSED MAX_CHUNCKS/8
volatile memBlock *unused[BUF_UNUSED];

// Updates the reference to curr from next.
void updatePrev(memBlock *curr) {
    memBlock *next = ((byte*) curr) + (curr->chuncks * CHUNCK_SIZE);
    if( next < emHeap + MAX_MEMORY ) {
        if(next->chuncks & HIGH_BIT_0(size_t)) {
            next = ((byte*) curr) + (curr->chuncks * CHUNCK_SIZE);
//            if( next >= emHeap + MAX_MEMORY ) {
//                return;
//            }
        }
        next->prev = curr;

    }
}

void *emMalloc(size_t bytes) {
    int x;

    void *block;

    // Allocate memory to data and size
    size_t chuncks;

    assert(bytes < MAX_MEMORY);
    assert(emptyBlocks > 0);
    assert(emptyBlocks < BUF_UNUSED);
    if (emptyBlocks <= 0 || emptyBlocks >= BUF_UNUSED) {
        return 0;
    }

    // No need to allocate extra memory when a bock perfectly fits on or more chuncks
    if (!((bytes + sizeof (memBlock)) % CHUNCK_SIZE))
        chuncks = (bytes + sizeof (memBlock)) / CHUNCK_SIZE;
    else
        chuncks = (bytes + sizeof (memBlock)) / CHUNCK_SIZE + 1;


    x = emptyBlocks;

    // While smaller block hasn't been found.
    while (x > 0 && chuncks < (unused[--x]->chuncks & HIGH_BIT_0(size_t)));


    block = unused[x];

    // If not enough space.
    if ((unused[x]->chuncks & HIGH_BIT_0(size_t)) < chuncks) {
        assert(0);
        return 0;
    }

    emSplit(block, chuncks);
    
    return block + sizeof(memBlock);
}

void emRemoveUnused(memBlock *block) {
    int x = 0;
    while (unused[x] != block) {
        assert(x < emptyBlocks);
        x++;
    }

    while (x < emptyBlocks) {
        unused[x] = unused[x + 1];
        x++;
    }

    emptyBlocks--;
}

void emInsertUnused(memBlock *block) {
    int x;

    x = emptyBlocks;
    while (x > 0 && (block->chuncks | HIGH_BIT(size_t)) < unused[x - 1]->chuncks) {
        unused[x] = unused[x - 1];
        x--;
    }
    unused[x] = block;

    emptyBlocks++;
}

void emSplit(memBlock *block, size_t chuncks) {
    emRemoveUnused(block);


    // If there is no room to split the block, then don't.
    if (block->chuncks - (chuncks | HIGH_BIT(size_t))) {
        memBlock *empty = ((byte *) block) + chuncks*CHUNCK_SIZE;

        empty->prev = block;
        empty->chuncks = (block->chuncks - chuncks) | HIGH_BIT(size_t);

        emInsertUnused(empty);

        updatePrev(empty);
    }



    block->chuncks = chuncks;

}

void emFree(void *block) {
    assert(block >= emHeap && block <= (emHeap + MAX_MEMORY));

    int x;

    memBlock *curr = block - sizeof (memBlock);

    memBlock *next = ((byte*) curr) + (curr->chuncks * CHUNCK_SIZE);

    // memBlock *prev = used[x - 1];
    memBlock *prev = curr->prev;

    // If prev is free
    if (prev && prev->chuncks & HIGH_BIT(size_t)) {


        // If next is free
        if (next->chuncks & HIGH_BIT(size_t)) {
            prev->chuncks += next->chuncks & HIGH_BIT_0(size_t);

            emRemoveUnused(next);
        }

        prev->chuncks += curr->chuncks;


        // The number of chunks prev contains has increased, it needs to be rearranged.
        emRemoveUnused(prev);
        emInsertUnused(prev);

        updatePrev(prev);

    } else {
        // If next is free
        if (next->chuncks & HIGH_BIT(size_t)) {

            curr->chuncks += next->chuncks & HIGH_BIT_0(size_t);

            emRemoveUnused(next);
        }


        curr->chuncks |= HIGH_BIT(size_t);
        emInsertUnused(curr);

        updatePrev(curr);
    }
}

__inline void emMemcpy(void *buf , const void *block, size_t bytes) {
    while( bytes > 0 ) {
        bytes--;
        ((char*)buf)[bytes] = ((char*)block)[bytes];
    }
}
__inline void emMemset( void *block, const int val, size_t bytes ) {
    while( bytes > 0 ) {
        ((char*)block)[--bytes] = val;
    }
}

void emInit() {
    unused[0] = emHeap;
    unused[0]->chuncks = MAX_CHUNCKS | HIGH_BIT(size_t);
    
    unused[0]->prev = NULL;
    
    emptyBlocks = 1;
}