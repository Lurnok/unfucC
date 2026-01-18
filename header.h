#pragma once

#include "cells.h"
#include "lexer.h"
#include "instructions.h"
#include "tokens.h"
#include "stack.h"

int execute_instruction(Instruction instruction,int * ptr, Cells cells, int * instruction_ptr, int * pairs, int loop_count);
int build_pairs(int * pairs, Instruction * tokens, size_t tokens_len,int loop_count);
