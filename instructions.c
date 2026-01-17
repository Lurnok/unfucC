#include "instructions.h"
#include "cells.h"
#include <stdio.h>

void ptr_right(int * ptr){
    if(*ptr == MAX_CELLS_INDEX) {
        *ptr = MIN_CELLS_INDEX;
    } else {
        *ptr += 1;
    }
}

void ptr_left(int * ptr){
     if(*ptr == MIN_CELLS_INDEX) {
        *ptr = MAX_CELLS_INDEX;
    } else {
        *ptr -= 1;
    }
}

void cell_inc(int ptr, Cells cells){
    cells[ptr] += 1;
}

void cell_dec(int ptr, Cells cells){
    cells[ptr] -= 1;
}

void print_val(int ptr, Cells cells){
    putchar(cells[ptr]);
}

int input_val(int ptr, Cells cells){
    int val;

    do {
        int result = scanf("%d", &val);

        if (result == EOF) {
            return 1;
        }
        if (result == 0) {
            while (fgetc(stdin) != '\n');
        }
    }while (val < 0 || val > 255);
    
    cells[ptr] = (unsigned char)val;

    return 0;
}