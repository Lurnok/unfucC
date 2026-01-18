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