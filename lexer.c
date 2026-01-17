#include "lexer.h"
#include "tokens.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

enum TOKEN_ENUM * tokenize(char * source, size_t *tokens_len){
    if (!source || !tokens_len) {
        return NULL;
    }

    size_t len = strlen(source) + 1;

    enum TOKEN_ENUM *ret = malloc(len * sizeof(enum TOKEN_ENUM));
    if (!ret) {
        return NULL;
    }

    size_t out = 0;

    for (size_t i = 0; i < len - 1; ++i){
        switch (source[i]){
            case '>':
                ret[out++] = PTR; 
                break;
            case '<': 
                ret[out++] = PTL;
                break;
            case '.':
                ret[out++] = PRT;
                break;
            case ',':
                ret[out++] = IPT;
                break;
            case '+':
                ret[out++] = INC;
                break;
            case '-':
                ret[out++] = DEC;
                break;
            case '[':
                ret[out++] = LPS;
                break;
            case ']':
                ret[out++] = LPE;
                break;
            case '\n':
                break;
            default:
                ret[out++] = CMT;
                break;
        }
    }

    ret[out++] = ENF;

    *tokens_len = out;
    return ret;
}