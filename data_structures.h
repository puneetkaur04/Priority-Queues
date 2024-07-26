// PUNEET KAUR

#ifndef data_structures_h
#define data_structures_h

typedef struct TAG_ELEMENT{
    double key;
}ELEMENT;

typedef struct TAG_HEAP{
    int capacity; /* capacity of the heap */
    int size; /* current size of the heap */
    ELEMENT **H; /* array of pointers to ELEMENT */
}HEAP;

#endif