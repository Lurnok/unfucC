#include "lexer.h"
#include "tokens.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Instruction * tokenize(char * source, size_t *tokens_len){
    if (!source || !tokens_len) {
        return NULL;
    }

    size_t len = strlen(source) + 1;

    Instruction *ret = malloc(len * sizeof(Instruction));
    if (!ret) {
        return NULL;
    }

    size_t out = 0;
    int to_skip = 0;

    for (size_t i = 0; i < len ; ++i){
        if (to_skip != 0){
            to_skip -= 1;
        } else {
            Instruction inst;
            switch (source[i]){
                case '>':
                    if (i > 0) {
                        if (source[i - 1] == '>'){
                            ret[out - 1].count += 1;
                        } else {
                            inst.token = PTR;
                            inst.count = 1;
                            ret[out++] = inst; 
                        }
                    } else {
                        inst.token = PTR;
                        inst.count = 1;
                        ret[out++] = inst; 
                    }
                    
                    break;
                case '<': 
                    if (i > 0) {
                        if (source[i - 1] == '<'){
                            ret[out - 1].count += 1;
                        } else {
                            inst.token = PTL;
                            inst.count = 1;
                            ret[out++] = inst; 
                        }
                    } else {
                        inst.token = PTL;
                        inst.count = 1;
                        ret[out++] = inst; 
                    }
                    
                    break;
                case '.':
                    inst.token = PRT;
                    inst.count = 1;
                    ret[out++] = inst;
                    break;
                case ',':
                    inst.token = IPT;
                    inst.count = 1;
                    ret[out++] = inst;
                    break;
                case '+':
                    if (i > 0) {
                        if (source[i - 1] == '+'){
                            ret[out - 1].count += 1;
                        } else {
                            inst.token = INC;
                            inst.count = 1;
                            ret[out++] = inst; 
                        }
                    } else {
                        inst.token = INC;
                        inst.count = 1;
                        ret[out++] = inst; 
                    }
                    
                    break;
                case '-':
                    if (i > 0) {
                        if (source[i - 1] == '-'){
                            ret[out - 1].count += 1;
                        } else {
                            inst.token = DEC;
                            inst.count = 1;
                            ret[out++] = inst; 
                        }
                    } else {
                        inst.token = DEC;
                        inst.count = 1;
                        ret[out++] = inst; 
                    }
                    
                    break;
                case '[':
                    if (i < len - 5){
                        if (source[i+1] == '-' && source[i+2] == '>' && source[i+3] == '+' && source[i+4] == '<' && source[i+5] == ']'){
                            inst.token = ADC;
                            inst.count = 1;
                            ret[out++] = inst;
                            to_skip = 5;
                        } else  if (source[i+1] == '-' && source[i+2] == ']'){
                            inst.token = CLR;
                            inst.count = 1;
                            ret[out++] = inst;
                            to_skip = 2;
                        } else {
                            inst.token = LPS;
                            inst.count = 1;
                            ret[out++] = inst;
                        }
                    } else if (i < len - 2){
                        if (source[i+1] == '-' && source[i+2] == ']'){
                            inst.token = CLR;
                            inst.count = 1;
                            ret[out++] = inst;
                            to_skip = 2;
                        } else {
                            inst.token = LPS;
                            inst.count = 1;
                            ret[out++] = inst;
                        }
                    } else {
                        inst.token = LPS;
                        inst.count = 1;
                        ret[out++] = inst;
                    }
                    break;
                case ']':
                    inst.token = LPE;
                    inst.count = 1;
                    ret[out++] = inst;
                    break;
                case '\n':
                    break;
                default:
                    if (i > 0) {
                        if (source[i - 1] != '-' && source[i - 1] != '+' && source[i - 1] != '.' && source[i - 1] != ',' && source[i - 1] != '[' && source[i - 1] != ']' && source[i - 1] != '<' && source[i - 1] != '>' && source[i - 1] != '\n'){
                            ret[out - 1].count += 1;
                        } else {
                            inst.token = CMT;
                            inst.count = 1;
                            ret[out++] = inst; 
                        }
                    } else {
                        inst.token = CMT;
                        inst.count = 1;
                        ret[out++] = inst; 
                    }
                    
                    break;
            }
        }
    }

    Instruction inst;
    inst.token = ENF;
    inst.count = 1;
    ret[out++] = inst;

    *tokens_len = out;
    return ret;
}