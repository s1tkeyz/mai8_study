#include "liblab24-utils.h"

bool is_sep(int c) { return (c == ' ') || (c == '\t'); }

bool is_operator(int c) {
    return (c == '/') || (c == '*') || (c == '+') || (c == '-') || (c == '!') || (c == '^');
}

bool is_digit(int c) { return (c >= '0' && c <= '9'); }

int get_next_char() {   
    int c;
    while(is_sep(c = getchar()));
    return c;
}