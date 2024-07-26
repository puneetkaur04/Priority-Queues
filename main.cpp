// PUNEET KAUR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "heap.h"

int main(int argc, char **argv){
    FILE *inputFile;
    HEAP *theHeap;

    double key;
    int flag = atoi(argv[1]);
    int pos; 

    int returnV;
    char Word[1000];

    if (argc < 4){
        fprintf(stderr, "Usage: %s flag <ifile> <ofile>\n", argv[0]);
        exit(0);
    }

    theHeap = NULL;
    inputFile = NULL;

    // Open the input file for reading
    inputFile = fopen(argv[2], "r");
    if (!inputFile){
        fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
        exit(0);
    }

    // Allocate memory 
    theHeap = (HEAP *) calloc(1, sizeof(HEAP));
    if (!theHeap){
        fprintf(stderr, "Error: calloc failed\n");
        fclose(inputFile);
        exit(0);
    }
    
    theHeap->capacity = 0;
    theHeap->size = 0;
    theHeap->H = NULL;

    while (1){
        returnV = nextInstruction(Word, &key, &pos);

    // Works
        if (returnV == 0){
            fprintf(stderr, "Warning: Invalid instruction: %s\n", Word);
            continue;
        }

    // Works
        if (strcmp(Word, "Stop")==0){
            fprintf(stdout,"Instruction: Stop\n");
            return 0;
        }

    // Works 
        if (strcmp(Word, "Init")==0){
            theHeap = init((int)key);
            continue;
        }
    // Works 
         if (strcmp(Word, "Read")==0){
            theHeap = read(theHeap, argv[2], flag);
            continue;
        }
    // Works 
        if (strcmp(Word, "Write")==0){
            theHeap = write(theHeap, argv[3]);
            continue;
        }
    // Works 
        if (strcmp(Word, "Print")==0){

            // Print the line
            fprintf(stdout,"Instruction: Print\n");

            printHeap(theHeap);
            continue;
        }
    // Works 
        if (strcmp(Word, "Insert")==0){
            insert(theHeap, key, flag); 
            continue;
        }
    // Works 
        if (strcmp(Word, "ExtractMin")==0){
            extractMin(theHeap, flag); 
            continue;
        }
    // Works 
        if (strcmp(Word, "DecreaseKey")==0){
            decreaseKey(theHeap, pos-1, key);
            continue;
        }
    } 
    return 1;
}