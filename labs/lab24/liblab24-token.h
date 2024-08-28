#pragma once

#include <stdbool.h>
#include "liblab24-utils.h"

typedef enum OpAssoc {
    OA_LEFT,
    OA_RIGHT,
} OpAssoc;

typedef enum Operator {
    OP_PLUS, // +
    OP_MINUS, // -
    OP_MULT, // *
    OP_DIVIDE, // /
    OP_POW, // ^
    OP_UMINUS, // !
} Operator;

typedef enum TokenType {
    TT_CONST, // Number constant
    TT_VAR, // X variable
    TT_OPERATOR,
    TT_UNKNOWN,
    TT_LEFT_BR,
    TT_RIGHT_BR,
} TokenType;

typedef struct Token {
    TokenType type;
    union  {
        double number;
        char unknown;
        Operator op;
    };
} Token;

typedef enum TOKEN_READ_RESULT {
    TRR_OK,
    TRR_EOF,
    TRR_ERR,
} TOKEN_READ_RESULT;

OpAssoc op_assoc(Operator op);

int op_priority(Operator op);

int op_to_char(Operator op);

void print_token(Token t);

TOKEN_READ_RESULT read_token(Token* out, TokenType prev_type);