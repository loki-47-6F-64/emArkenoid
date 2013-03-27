/* 
 * File:   eMalloc.h
 * Author: Loki
 *
 * Created on 04 March 2013, 20:05
 */


#ifndef MALLOC_H
#define	MALLOC_H

#define NULL 0

#define CHUNCK_SIZE sizeof(memBlock)
#define MAX_CHUNCKS 575
#define MAX_MEMORY (CHUNCK_SIZE*MAX_CHUNCKS)

#define HIGH_BIT( x ) (1 << (sizeof(x)*8 - 1))
#define HIGH_BIT_0( x ) (~HIGH_BIT(x))
#define HIGH_BIT_1( x ) HIGH_BIT(x)

typedef unsigned char byte;
typedef unsigned int size_t;
/* Represents a block of memory.
 * If a block is allocated, only chuncks is used. */
typedef struct _memBlock {
    size_t chuncks;

    struct _memBlock *prev; // used only if free
    //struct _memBlock *next; // used only if free
} memBlock;

/* Request memory from heap.
 */
void *emMalloc(size_t);

/* Split unused block into an unused block and an used block.
 * Block points to the used block.
 */
void emSplit(memBlock *block, size_t chuncks);

/* Free memory from heap
 */
void emFree(void*);

/*
 * copy bytes from memory in buffer.
 */
__inline void emMemcpy(void*, const void*, size_t);
__inline void emMemset(void*, int, size_t);

void emInit();

#endif	/* MALLOC_H */

