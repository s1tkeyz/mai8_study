#include "liblab24-token.h"

OpAssoc op_assoc(Operator op) {
    switch(op) {
        case OP_MINUS:
        case OP_PLUS:
        case OP_MULT:
        case OP_DIVIDE:
            return OA_LEFT;
        case OP_UMINUS:
        case OP_POW:
            return OA_RIGHT;
    }
    return -1;
}

int op_priority(Operator op) {
    switch (op) {
    case OP_PLUS:
    case OP_MINUS:
        return 1;
    case OP_MULT:
    case OP_DIVIDE:
        return 2;
    case OP_POW:
        return 3;
    case OP_UMINUS:
        return 4;
    default:
        return -1;
    }
}

int op_to_char(Operator op) {
    switch (op) {
    case OP_PLUS:
        return '+';
    case OP_MINUS:
        return '-';
    case OP_MULT:
        return '*';
    case OP_DIVIDE:
        return '/';
    case OP_POW:
        return '^';
    case OP_UMINUS:
        return '!';
    default:
        return -1;
    }
}

void print_token(Token t) {
    if(t.type == TT_OPERATOR) {
        switch (t.op) {
        case OP_MINUS:
        case OP_UMINUS:
            printf("%c", '-');
            break;
        case OP_PLUS:
            printf("%c", '+');
            break;
        case OP_MULT:
            printf("%c", '*');
            break;
        case OP_DIVIDE:
            printf("%c", '/');
            break;
        case OP_POW:
            printf("%c", '^');
            break;
        }
    } else if(t.type == TT_CONST) { 
        printf("%lf", t.number);
    } else if(t.type == TT_LEFT_BR) {
        printf("%c", '(');
    } else if(t.type == TT_RIGHT_BR) {
        printf("%c", ')');
    } else if(t.type == TT_VAR) {
        printf("%c", 'x');
    } else { return; }
}

TOKEN_READ_RESULT read_token(Token* out, TokenType prev_type) {
    int ch = get_next_char();
    if(ch == '\n' || ch == '\0' || ch == EOF) {
        out->type = TT_UNKNOWN;
        return TRR_EOF;
    }
    if(is_digit(ch)) {
        ungetc(ch, stdin);
        double num;
        scanf("%lf", &num);
        out->type = TT_CONST;
        out->number = num;
        return TRR_OK;
    } else if(ch == '(') {
        out->type = TT_LEFT_BR;
        return TRR_OK;
    } else if(ch == ')') {
        out->type = TT_RIGHT_BR;
        return TRR_OK;
    } else if(ch == 'x' || ch == 'X') {
        out->type = TT_VAR;
        return TRR_OK;
    } else if(is_operator(ch)) {
        out->type = TT_OPERATOR;
        switch (ch) {
        case '+':
            out->op = OP_PLUS;
            break;
        case '-':
            if(prev_type == TT_UNKNOWN || prev_type == TT_LEFT_BR || prev_type == TT_OPERATOR)
                out->op = OP_UMINUS;
            else 
                out->op = OP_MINUS;
            break;
        case '/':
            out->op = OP_DIVIDE;
            break;
        case '*':
            out->op = OP_MULT;
            break;
        case '^':
            out->op = OP_POW;
            break;
        }
        return TRR_OK;
    }
    else { 
        out->type = TT_UNKNOWN; 
        out->unknown = ch;
        return TRR_ERR;
    }
}