#pragma once
#include <stddef.h>
#include "tokens.h"

Instruction * tokenize(char * source, size_t *tokens_len);
