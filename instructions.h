#pragma once
#include "cells.h"

void ptr_right(int * ptr);
void ptr_left(int * ptr);

void cell_inc(int ptr, Cells cells);
void cell_dec(int ptr, Cells cells);

void print_val(int ptr, Cells cells);
int input_val(int ptr, Cells cells);
