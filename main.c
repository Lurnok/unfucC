#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"
#include "instructions.h"
#include "stack.h"
#include "tokens.h"

int main(int argc, char * argv[]){

    if(argc != 2){
        printf("1 argument expected, got %d\n",argc - 1);
        return EXIT_FAILURE;
    }

    FILE * source = fopen(argv[1], "r");
    
    if(source == 0){
        printf("Error reading file %s : %s\n",argv[1],strerror(errno));
        return EXIT_FAILURE;
    }

    char * content = 0;
    long length;

    fseek(source,0,SEEK_END);
    length= ftell(source);
    fseek(source,0,SEEK_SET);
    content = malloc(length + 1);
    
    if(!content){
        perror("malloc");
        return EXIT_FAILURE;
    }

    if(content){
        fread(content, 1, length, source);
        content[length] = '\0';
    }

    if(fclose(source) != 0){
        printf("Unexpected error while closing file : %s\n",strerror(errno));
        free(content);
        return EXIT_FAILURE;
    }

    size_t tokens_len;

    Instruction * tokens = tokenize(content, &tokens_len);

    int instruction_ptr = 0;
    int ptr = 0;
    Cells cells;

    int loop_count = 0;

    for(int i = 0; i < tokens_len; ++i){
        if(tokens[i].token == LPS){
            loop_count += 1;
        }
    }

    int * pairs = malloc(tokens_len * sizeof(int));

    if(!pairs){
        printf("Failed to allocate memory.\n");
        free(tokens);
        free(content);
        return EXIT_FAILURE;
    }

    if (build_pairs(pairs, tokens, tokens_len,loop_count) == 1) {
        free(tokens);
        free(content);
        free(pairs);
        return EXIT_FAILURE;
    };

    while(1){
        if (tokens[instruction_ptr].token == ENF){
            break;
        } else {
            if(execute_instruction(tokens[instruction_ptr], &ptr, cells, &instruction_ptr,pairs,loop_count) != 0){
                free(tokens);
                free(content);
                free(pairs);
                printf("Unexpected error ._.");
                return EXIT_FAILURE;
            }
        }


    }

    free(tokens);
    free(content);
    free(pairs);
    return EXIT_SUCCESS;
}






int execute_instruction(Instruction instruction, int * ptr, Cells cells, int * instruction_ptr, int * pairs, int loop_count){
    switch (instruction.token) {

    case PTL:
        ptr_left(ptr,instruction.count);
        *instruction_ptr += 1;
        break;
    case PTR:
        ptr_right(ptr,instruction.count);
        *instruction_ptr += 1;
        break;
    case INC:
        cell_inc(*ptr, cells,instruction.count);
        *instruction_ptr += 1;
        break;
    case DEC:
        cell_dec(*ptr, cells,instruction.count);
        *instruction_ptr += 1;
        break;
    case PRT:
        print_val(*ptr, cells);
        *instruction_ptr += 1;
        break;
    case IPT:
        if(input_val(*ptr, cells) == 1){
            return 1;
        };
        *instruction_ptr += 1;
        break;
    case LPS:
        if(cells[*ptr] == 0){
            *instruction_ptr = pairs[*instruction_ptr] + 1;
        }  else {
            *instruction_ptr += 1;
        }
        break;
    case LPE:
        if(cells[*ptr] != 0){
            *instruction_ptr = pairs[*instruction_ptr] + 1;
        } else {
            *instruction_ptr += 1;
        }
        break;
    case CMT:
        *instruction_ptr += 1;
        break;
    case ERR:
        return 1;
    case ENF:
        return 0;

    }

    return 0;
}

int build_pairs(int * pairs,Instruction * tokens, size_t tokens_len, int loop_count ){
    struct Stack* stack = createStack(loop_count);
        if (!stack) {
            printf("Failed to create stack.\n");
            return 1;
    }

    for(int i = 0; i < tokens_len; ++i){
        if(tokens[i].token == LPS){
            if (isFull(stack)) {
                printf("Exceeded maximum nesting capacity.\n");
                freeStack(stack);
                return 1;
            }
            push(stack, i);
        } else if (tokens[i].token == LPE) {
            if (isEmpty(stack)){
                printf("Mismatched bracket at position %d.\n",i);
                freeStack(stack);
                return 1;
            }

            pairs[i] = peek(stack);
            pairs[peek(stack)]  = i; 
            pop(stack);
        } else {
            pairs[i] = -1;
        }
    }

    if (!isEmpty(stack)){
        printf("Mismatched brackets at positions : \n");
        while (!isEmpty(stack)) {
            printf("%d\n",peek(stack));
            pop(stack);
        }
        freeStack(stack);
        return 1;
    }

    freeStack(stack);
    return 0;
}