/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA1
* Lex.c
* File containing the main program execution.
***/ 

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

    int count = 0;
    FILE *in, *in2, *out;
    char line[300];
    char* token;

    if (argc != 3) {
        fprintf(stderr, "Invalid Arguments.\nUsage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    in2 = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL) {
        printf("Unable to open file %s for reading.\n", argv[1]);
        exit(1);
    }

    if (in2 == NULL) {
        printf("Unable to open file %s for reading.\n", argv[1]);
        exit(1);
    }

    if (out == NULL) {
        printf("Unable to open file %s for writing.\n", argv[2]);
        exit(1);
    }

    while (fgets(line, 300, in2) != NULL) {
        token = line;
        count++;
    }

    char** tokenList = calloc(count, sizeof(char*));
    int n = 0;

    while (fgets(line, 300, in) != NULL) {
        if (strcmp(line, "\n") == 0) {
            token = line;
        }

        else {
            token = strtok(line, "\n");
        }

        char* temp = calloc(count, sizeof(char*) + 1);
        strcpy(temp, token);
        tokenList[n] = temp;
        n++;
    }

    List L = newList();

    for (int j = 1; j < count; j++) {
        char* temp = tokenList[j];
        int i = j - 1;

        if (length(L) == 0) {
            prepend(L, 0);
        }

        if (length(L) > 0) {
            moveFront(L);
            
            while (index(L) != i) {
                moveNext(L);
            }
        }

        while (i >= 0 && strcmp(temp, tokenList[get(L)]) < 0) {
            movePrev(L);
            i--;
        }

        if (index(L) == -1) {
            prepend(L, j);
        }

        else {
            insertAfter(L, j);
        }
    }

    moveFront(L);

    for (int i = 0; i < count; i++) {
        fprintf(out, "%s\n", tokenList[get(L)]);
        moveNext(L);
    }

    freeList(&L);

    for (int i = 0; i < count; i++) {
        free(tokenList[i]);
    }
    free(tokenList);

    fclose(in);
	fclose(in2);
    fclose(out);
}