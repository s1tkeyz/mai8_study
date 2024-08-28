#include "liblab24-dss.h"

bool read_expression(TQueue* out) {
    Token curr;
    TokenType prev = TT_UNKNOWN;
    TOKEN_READ_RESULT r;
    while((r = read_token(&curr, prev)) == TRR_OK) {
        TQueue_push(out, curr);
        prev = curr.type;
    }
    return (r != TRR_ERR);
}

bool dijkstra_sort(TQueue* expr, TQueue* out, double xval) {
    TStack* ops = ts_create();
    if(!ops)
        return false;
    while(!TQueue_empty(expr)) {
        Token curr = TQueue_pop(expr); 
        if(curr.type == TT_CONST)
            TQueue_push(out, curr);
        else if(curr.type == TT_LEFT_BR)
            ts_push(ops, curr);
        else if(curr.type == TT_OPERATOR) {
            Token top = ts_top(ops);
            while((top.type == TT_OPERATOR) && !ts_empty(ops)) {
                if(((op_priority(top.op) >= op_priority(curr.op)) && (op_assoc(curr.op) == OA_LEFT)) || ((op_priority(top.op) > op_priority(curr.op)) && (op_assoc(curr.op) == OA_RIGHT))) {
                    TQueue_push(out, top);
                    ts_pop(ops);
                    top = ts_top(ops);
                } else { break; }
            }
            ts_push(ops, curr);
        } else if(curr.type == TT_RIGHT_BR) {
            if(ts_empty(ops))
                return false;
            Token top = ts_top(ops);
            while(top.type != TT_LEFT_BR) {
                TQueue_push(out, top);
                ts_pop(ops);
                top = ts_top(ops);
                if(ts_empty(ops)) {
                    TQueue_print(out);
                    TQueue_print(expr);
                    ts_destroy(ops);
                    return false;
                }
            }
            ts_pop(ops);
        } else if(curr.type == TT_VAR) {
            Token xv;
            xv.number = xval;
            xv.type = TT_CONST;
            TQueue_push(out, xv);
        }
    }
    while(!ts_empty(ops))
        TQueue_push(out, ts_pop(ops));
    ts_destroy(ops);
    return true;
}

bool calculate(TQueue* polish, double* res) {
    TStack* s = ts_create();
    while(!TQueue_empty(polish)) {
        Token t = TQueue_pop(polish);
        if(t.type == TT_CONST)
            ts_push(s, t);
        else if(t.type == TT_OPERATOR) {
            if(t.op == OP_UMINUS) {
                if(s->size < 1)
                    return false;
                double r = -ts_pop(s).number;
                Token k = {.type = TT_CONST, .number = r};
                ts_push(s, k);
            } else {
                if(s->size < 2)
                    return false;
                int b = ts_pop(s).number;
                int a = ts_pop(s).number;
                switch (t.op) {
                case OP_PLUS:
                    a += b;
                    break;
                case OP_MINUS:
                    a -= b;
                    break;
                case OP_MULT:
                    a *= b;
                    break;
                case OP_DIVIDE:
                    a /= b;
                    break;
                case OP_POW:
                    a = pow(a, b);
                    break;
                }
                Token n = {.type = TT_CONST, .number = a};
                ts_push(s, n);
            }
        }
    }
    if(s->size != 1)
        return false;
    *res = ts_pop(s).number;
    return true;
}