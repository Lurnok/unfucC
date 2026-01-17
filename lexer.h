#pragma once
#include <stddef.h>
#include "tokens.h"

enum TOKEN_ENUM * tokenize(char * source, size_t *tokens_len);
