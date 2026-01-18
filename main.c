#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "header.h"
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
    memset(cells, 0, sizeof cells);

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

    static void *dispatch_table[] = {
    &&PTL,  
    &&PTR,  
    &&INC,  
    &&DEC,  
    &&PRT,  
    &&IPT,  
    &&LPS,  
    &&LPE,  
    &&CMT,  
    &&CLR,  
    &&ADC,  
    &&ENF   
};

    goto *dispatch_table[tokens[instruction_ptr].token];

    PTR:
        ptr = (ptr + tokens[instruction_ptr].count) & 32767;
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];

    PTL:
        ptr = (ptr - tokens[instruction_ptr].count) & 32767;
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];

    INC:
        cells[ptr] = (unsigned char)(cells[ptr] + tokens[instruction_ptr].count);
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];
    
    DEC:
        cells[ptr] = (unsigned char)(cells[ptr] - tokens[instruction_ptr].count);
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];
            
    PRT:
        putchar(cells[ptr]);
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];
            
    IPT:
        cells[ptr] = getchar();
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];

    CLR:
        cells[ptr] = 0;
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];
    
    ADC:
        cells[(ptr + 1) & 32767] += cells[ptr];
        cells[ptr] = 0;
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];
            
    LPS:
        if(cells[ptr] == 0){
            instruction_ptr = pairs[instruction_ptr] + 1;
        }  else {
            instruction_ptr += 1;
        }
        goto *dispatch_table[tokens[instruction_ptr].token];

    LPE:
        if(cells[ptr] != 0){
            instruction_ptr = pairs[instruction_ptr] + 1;
        } else {
            instruction_ptr += 1;
        }
        goto *dispatch_table[tokens[instruction_ptr].token];

    CMT:
        instruction_ptr += 1;
        goto *dispatch_table[tokens[instruction_ptr].token];

    ENF:
        goto END;
    
    END:
    free(tokens);
    free(content);
    free(pairs);
    return EXIT_SUCCESS;
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