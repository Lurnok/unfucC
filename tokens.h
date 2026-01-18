#pragma once

#define FOREACH_TOKEN(TOKEN) \
        TOKEN(PTL)   \
        TOKEN(PTR)  \
        TOKEN(INC)   \
        TOKEN(DEC)  \
        TOKEN(PRT)  \
        TOKEN(IPT)  \
        TOKEN(LPS)  \
        TOKEN(LPE)  \
        TOKEN(CMT)  \
        TOKEN(ERR)  \
        TOKEN(ENF)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum TOKEN_ENUM {
    FOREACH_TOKEN(GENERATE_ENUM)
};

static const char *TOKEN_STRING[] = {
    FOREACH_TOKEN(GENERATE_STRING)
};

typedef struct Instruction {
    enum TOKEN_ENUM token;
    int count;
} Instruction;