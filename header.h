#pragma once

#include "cells.h"
#include "lexer.h"
#include "tokens.h"
#include "stack.h"

int build_pairs(int * pairs, Instruction * tokens, size_t tokens_len,int loop_count);
