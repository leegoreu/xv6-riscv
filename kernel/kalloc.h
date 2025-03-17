#ifndef KALLOC_H
#define KALLOC_H

#include "spinlock.h"

// Linked list node for free memory pages
struct run {
    struct run *next;
};

// Memory allocator structure
extern struct {
    struct spinlock lock;
    struct run *freelist;
} kmem;

void *kalloc(void);
void kfree(void *);
void freerange(void *, void *);

#endif
