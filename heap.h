// PUNEET KAUR

#ifndef heap_h
#define heap_h
#include "data_structures.h"

HEAP* init(int capacity);
void insert(HEAP *heap, double key, int flag);
void extractMin(HEAP *heap, int flag);
void decreaseKey(HEAP *heap, int position, double newKey);
void printHeap(HEAP *heap);

HEAP* minHeapify(HEAP *heap, int i); 
HEAP* buildMinHeap(HEAP *heap);

HEAP* write(HEAP*heap, const char *filename);
HEAP* read(HEAP *heap, const char *fp, int flag); 

#endif