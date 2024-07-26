// PUNEET KAUR

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <utility>

// count variable to keep track of the total number of Heapify calls
int count = 0;

HEAP* minHeapify(HEAP *heap, int i){

    // left child 
    int left =  2 * i + 1; 

    // right child 
    int right = 2 * i + 2; 

    int smallest = i;

    // smallest being left child 
    if(left < heap->size && heap->H[left]->key < heap->H[smallest]->key)
    {
        smallest = left; 
    }

    // smallest being right child 
    if(right < heap->size && heap->H[right]->key < heap->H[smallest]->key)
    {
        smallest = right; 
    }

    if(smallest != i)
    {
        // swap 
        std::swap(heap->H[i], heap->H[smallest]);

        // increase count 
        count++; 

        //printf("minHeapify called for index: %d\n", i);
        heap = minHeapify(heap, smallest);
    }

    return heap; 
}

HEAP* buildMinHeap(HEAP *heap){

    for(int i = (heap->size/2) - 1; i >= 0; i--)
    {
        // increase count 
        count++; 
        heap = minHeapify(heap, i);
    }
    return heap; 
}

HEAP* init(int capacity){

    // Print the line
    fprintf(stdout,"Instruction: Init %d\n", capacity);

    // Allocate memory for an object of type HEAP
    HEAP *theHeap = (HEAP *)malloc(sizeof(HEAP));

    // return a null pointer when memory allocation fails
    if(!theHeap){
        return NULL;
    }

    // allocate memory for an heap array of size <Capacity>
    theHeap->H = (ELEMENT**)malloc(capacity*sizeof(ELEMENT*));

    // return a null pointer when memory allocation fails
    if(!theHeap->H)
    {
        //  free the object allocated in the first memory allocation
        free(theHeap); 
        return NULL; 
    }
    
    // You should also set the size of this HEAP object to 0.
    theHeap->size = 0; 
    theHeap-> capacity = capacity; 

    // return a pointer to this object. 
    return theHeap;
}

void printHeap(HEAP *heap){

    // If the heap is NULL, print error message
    if (heap == NULL)
    {
        fprintf(stderr, "Error: heap is NUll\n");

    }else{

        // if the heap's size is negative
        if(heap->size < 0)
        {
            // set the size to zero 
            heap->size = 0; 
        }

        // the program writes to stdout the size of the heap 
        fprintf(stdout, "%d\n", heap->size);
       
        // followed by the key values of the elements in the heap 
        for(int i = 0; i < heap->size; i++){
            fprintf(stdout, "%lf\n", heap->H[i]->key);
        }
    }  
}

 HEAP* write(HEAP*heap, const char *fp)
 {
    // Print the following line
    fprintf(stdout, "Instruction: Write\n"); 

    // if the heap is NULL
    if(heap == NULL)
    {
        fprintf(stderr, "Error: heap is NULL");
    }

    // Opens the file argv[3] in write mode.
    FILE *outputFile = fopen(fp, "w");

    // If the file is not opened successfully
    if (!outputFile){
        fprintf(stderr, "Error: cannot open file %s\n", fp);
    }

    // the size of the heap 
    fprintf(outputFile, "%d\n", heap->size);

    // Write the heap information to the file argv[3] 
    for(int i = 0; i < heap->size; i++)
    {
        fprintf(outputFile, "%lf\n", heap->H[i]->key);
    }

    // Close the file argv[3].
    fclose(outputFile);

    return heap; 
 }

HEAP* read(HEAP *heap, const char *fp, int flag)
{
    // Print the following line
    fprintf(stdout,"Instruction: Read\n");

    // if the heap is NULL
    if(heap == NULL)
    {
        fprintf(stderr, "Error: heap is NULL");
    }

    // Open the file argv[2] in read mode
    FILE *fileR = fopen(fp, "r");

    // If the file is not opened successfully
    if (!fileR){
        fprintf(stderr, "Error: cannot open file %s\n", fp);
    }

    // Read in the first integer, n, from the file opened
    int n; 
    fscanf(fileR, "%d", &n); 
    heap->size = n; 

    //  heap->capacity is smaller than n
    if(heap->capacity < n)
    {
        fprintf(stderr, "Error: capacity is smaller than n %s\n", fp);
        // close file
        fclose(fileR);
    }
    
    // For each value of j = 1, 2, . . . , n, read in keyj from the input file
    for(int j = 0; j < n ;j++)
    {
        double key; 
        if (fscanf(fileR, "%lf", &key) == 1){
            // dynamically allocate memory for an object of type ELEMENT
            ELEMENT* obj = (ELEMENT*)malloc(sizeof(ELEMENT));

            // sets the key field of this object to keyj
            obj->key = key;  

            // let the j-th element of the corresponding array in the heap point to this object
            heap->H[j] = obj; 

        }else{
            break; 
        }
    }

    // Close the file
    fclose(fileR);
  
    // If the input array does NOT satisy the heap order, i.e., the input array is not a MinHeap
    bool isSatisfy = true;

    for (int i = (heap->size / 2) - 1; i >= 0; i--) {

        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (!((l < heap->size && heap->H[l]->key > heap->H[i]->key) && (r < heap->size && heap->H[r]->key > heap->H[i]->key))) {
            isSatisfy = false;
            break; 
        }
    }

    if (isSatisfy == false) {
        // set count to 0 
        count = 0; 
        // Call BuildHeap
        heap = buildMinHeap(heap);
    }

    // If flag is 2 or 3
    if ((flag == 2 || flag == 3) && isSatisfy == false) {
        printf("Input array is NOT a MinHeap\n");
        printf("Call BuildHeap\n");
        printf("Number of Heapify calls triggered by BuildHeap: %d\n", count);
    }

    return heap; 
}

void extractMin(HEAP *heap, int flag){

    // Print the line
   fprintf(stdout,"Instruction: ExtractMin\n");

    // If the heap is NULL, print error message
    if (heap == NULL)
    {
        fprintf(stderr, "Error: heap is NUll\n");
    }

    // If the heap is empty,
    if(heap->size == 0)
    {
        //fprintf(stderr, "Error: heap is empty\n");
    }

    // Perform the ExtractMin operation
    ELEMENT *min = heap->H[0];
    heap->H[0] = heap->H[heap->size - 1];
    heap->size--;
    
    // set count to zero 
    count = 0;

    if (heap->size > -1) {
        count++;
        heap = minHeapify(heap, 0);
    }

    if(heap->size >= 0)
    {
        // If flag is not 2 or 3
        if ((flag == 2 || flag == 3)) {
            printf("Element with key %lf extracted from the heap\n", min->key);
            printf("Number of Heapify calls triggered by ExtractMin: %d\n", count);
        } else {
            printf("Element with key %lf extracted from the heap\n", min->key);
        }
    }
}

void insert(HEAP *heap, double key, int flag){

    // If the heap is NULL
    if(heap == NULL)
    {
        printf("Error: heap is NULL");
        return; 
    }

    // If the heap is full,
    if(heap->size == heap->capacity)
    {
        // Print the line
        fprintf(stdout,"Instruction: Insert %f\n", key);
        return; 
    }

    // Dynamically allocate memory for an object of type ELEMENT
    ELEMENT *item = (ELEMENT*)malloc(sizeof(ELEMENT));
   
    // Set the key field of this object to <Key>
    item->key = key;

    // Insert this object to the min heap
    heap->H[heap->size] = item; 

    // increase to size of the heap by one 
    heap->size++;

    // Print the line
    fprintf(stdout,"Instruction: Insert %f\n", key);

    // Heapify upwards 
    int index = heap->size - 1;
    while (index > 0 && heap->H[(index - 1) / 2]->key > heap->H[index]->key) {
        std::swap(heap->H[index], heap->H[((index-1)/2)]);
        index = (index - 1) / 2;
    } 

    // If flag is not 1 or 3
    if (flag == 1 || flag == 3) {
        printf("Element with key %lf inserted at location %d of the heap array\n", key, index+1);
    } else {
        printf("Element with key %lf inserted into the heap\n", key);
    }
}

void decreaseKey(HEAP *heap, int position, double newKey){
    
    // Print the following line
    printf("Instruction: DecreaseKey %d %f\n", position+1, newKey);

    // If the heap is NULL
    if(heap == NULL)
    {
        printf("Error: heap is NULL");
    }

    // If the heap is empty 
    if(heap->size == 0)
    {
        printf("Error: heap is empty");
    }

    // If <Position> if out of range or <NewKey> is not smaller than the corrent key
    // so pos is less than 0
    if(position < 0 || position >= heap->size || newKey >= heap->H[position]->key)
    {
        printf("Error: invalid call to DecreaseKey\n");
    }

    // decrease the key field of the corresponding object to <NewKey>
    heap->H[position]->key = newKey; 

    // perform the corresponding operations on the min heap
    while (position > 0) {
        int index = (position-1)/2;

        // compare the parent key to the current key 
        if (heap->H[index]->key <= heap->H[position]->key) {
            break;
        }

        std::swap(heap->H[position], heap->H[index]);

        // update the value of position 
        position = index;
    }
}