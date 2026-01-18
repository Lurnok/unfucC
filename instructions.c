#include "instructions.h"
#include "cells.h"
#include <stdio.h>

void ptr_right(int * ptr, int count){
    *ptr = (*ptr + count) % ARR_SIZE;
}

void ptr_left(int * ptr, int count){
    *ptr = (*ptr - (count % ARR_SIZE) + ARR_SIZE) % ARR_SIZE;
}

void cell_inc(int ptr, Cells cells, int count){
    cells[ptr] = (unsigned char)(cells[ptr] + count);
}

void cell_dec(int ptr, Cells cells, int count){
    cells[ptr] = (unsigned char)(cells[ptr] - count);
}

void print_val(int ptr, Cells cells){
    putchar(cells[ptr]);
}

int input_val(int ptr, Cells cells){
    unsigned char val = getchar();
    cells[ptr] = val;
    return 0;
}