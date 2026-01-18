#pragma once
#include "cells.h"

void ptr_right(int * ptr, int count);
void ptr_left(int * ptr, int count);

void cell_inc(int ptr, Cells cells, int count);
void cell_dec(int ptr, Cells cells, int count);

void print_val(int ptr, Cells cells);
int input_val(int ptr, Cells cells);
