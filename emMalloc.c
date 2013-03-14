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
volatile int usedBlocks;

#define BUF_UNUSED MAX_CHUNCKS/8
#define BUF_USED   MAX_CHUNCKS
volatile memBlock *unused[BUF_UNUSED], *used[BUF_USED];

void *emMalloc(size_t bytes) {
    int x;
    
    void *block;
    
    // Allocate memory to data and size
    size_t chuncks;
    
    assert( bytes < MAX_MEMORY );

    
    if( !emptyBlocks || emptyBlocks >= BUF_UNUSED || usedBlocks >= BUF_USED )
    {
        assert(0); // Don't allow this execution path during debugging
        return NULL;
    }
    // No need to allocate extra memory when a bock perfectly fits on or more chuncks
    if( !((bytes + sizeof(size_t)) % CHUNCK_SIZE))
        chuncks = (bytes + sizeof(size_t)) / CHUNCK_SIZE;
    else
        chuncks = (bytes + sizeof(size_t)) / CHUNCK_SIZE + 1;
    
    
    x = emptyBlocks;
    
    // While smaller block hasn't been found.
    while( x > 0 && chuncks < (unused[--x]->chuncks &HIGH_BIT_0(size_t)) );
    
    
    block = unused[x];
    
    // If not enough space.
    if( (unused[x]->chuncks &HIGH_BIT_0(size_t)) < chuncks ) {
        assert(0); // Don't allow this execution path during debugging
        return NULL;
    }
    
    emSplit( block, chuncks );

    assert((block + sizeof(size_t) + bytes) < (emHeap + MAX_MEMORY));
    return block + sizeof(size_t);
}

void emRemoveUsed( memBlock *block ) {
    int x = 0;
    while( used[x] != block ) x++;
    
    assert( x < usedBlocks );
    
    while( x < usedBlocks ) {
        used[x] = used[x + 1];
        x++;
    }
    
    usedBlocks--;
}

void emRemoveUnused( memBlock *block ) {
    int x = 0;
    while( unused[x] != block ) x++;
    
    while( x < emptyBlocks ) {
        unused[x] = unused[x + 1];
        x++;
    }
    
    emptyBlocks--;
}

void emInsertUsed( memBlock *block ) {
    int x;
    
    x = usedBlocks;
    while( x > 0 && block <= used[x - 1] ) {
        used[x] = used[x - 1];
        x--;
    }
    used[x] = block->prev;
    
    usedBlocks++;
}
void emInsertUnused( memBlock *block ) {
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
    emRemoveUnused( block );
    
    
    // If there is no room to split the block, then don't.
    if ( block->chuncks - (chuncks | HIGH_BIT(size_t))) {
        memBlock *empty = ((byte *)block) + chuncks*CHUNCK_SIZE;
        
        
//        empty->next = block->next;
        empty->prev = block;
        empty->chuncks = (block->chuncks - chuncks) | HIGH_BIT(size_t);
        
        emInsertUnused(empty);
    }
    


    block->chuncks = chuncks;
    emInsertUsed( block );

}

void emFree( void *block ) {
    assert( block >= emHeap && block <= (emHeap + MAX_MEMORY));
    
    int x;
    
    memBlock *curr = block - sizeof(size_t);
    
    memBlock *next = ((byte*)curr) + (curr->chuncks*CHUNCK_SIZE);
    
    // Find prev
    x = 0;
    while( x < usedBlocks && used[x] < curr ) x++;
    
    memBlock *prev = used[x - 1];
    
    
    // If prev is free
    if( prev && prev->chuncks & HIGH_BIT(size_t) ) {
        // If next is free
        if( next->chuncks & HIGH_BIT(size_t)) {
//            prev->next = next->next;
            
            prev->chuncks += next->chuncks &HIGH_BIT_0(size_t);
            
            emRemoveUnused( next );
        }
        else {
//            prev->next = curr->next;
        }
        
        emRemoveUsed( prev );
        
        prev->chuncks += curr->chuncks;
        
        
        // The number of chunks prev contains has increased, it needs to be rearranged.
        emRemoveUnused( prev );
        emInsertUnused( prev );
        
        
    }
    else {
        // If next is free
        if( next->chuncks & HIGH_BIT(size_t)) {
//            curr->next = next->next;
            curr->prev = prev;
            
            curr->chuncks += next->chuncks &HIGH_BIT_0(size_t);
            
            emRemoveUnused( next );
        }
        else {
            curr->prev = prev;
//            curr->next = next;
            
        }

        emRemoveUsed( prev );
        
        curr->chuncks |= HIGH_BIT(size_t);
        emInsertUnused( curr );
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
    
//    unused[0]->next = NULL;
    unused[0]->prev = NULL;
    
    emptyBlocks = 1;
    usedBlocks  = 0;
}