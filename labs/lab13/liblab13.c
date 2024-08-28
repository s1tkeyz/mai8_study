#include <stdio.h>
#include "liblab13.h"

bool is_separator(int c) {
    if(c == EOF || c == '\t' || c == ',' || c == ' ' || c == '\n' || c == '\0' || c == 0)
        return true;
    return false;
}

bool is_letter(int c) {
    if((c >= LAT_CAP_A && c <= LAT_CAP_Z) || (c >= LAT_A && c <= LAT_Z) || (c >= CYR_CAP_A && c <= CYR_CAP_YA) || (c >= CYR_A && c <= CYR_YA) || c == CYR_YO || c == CYR_CAP_YO)
        return true;
    return false;
}

bool is_cyrillic(int c) {
    if((c >= CYR_CAP_A && c <= CYR_CAP_YA) || (c >= CYR_A && c <= CYR_YA) || c == CYR_YO || c == CYR_CAP_YO)
        return true;
    return false;
}

bool is_capital(int c) {
    if((c >= LAT_CAP_A && c <= LAT_CAP_Z) || (c >= CYR_CAP_A && c <= CYR_CAP_YA) || c == CYR_CAP_YO)
        return true;
    return false;
}

int to_lower(int c) {
    if(is_capital(c)) {
        if(is_cyrillic(c))
            if(c == CYR_CAP_YO)
                c = CYR_YO;
            else
                c += (CYR_A - CYR_CAP_A);
        else
            c += (LAT_A - LAT_CAP_A);
    }
    return c;
}

int get_utf8_letter() {
    int c = getchar();
    if(c == EOF)
        return -1;
    if(((c >> 5) & 6) == 6) {
        int d = getchar();
        return (c - 0xC2) * 64 + d;
    }
    return c;
}

int get_letter_idx(int c) {
    if(is_letter(c)) {
        c = to_lower(c);
        if(is_cyrillic(c)) {
            int k = c - CYR_A + 26;
            return (c == CYR_YO) ? 32 : k + (k > 31);
        }
        else
            return c - LAT_A;
    }
    return -1;
}

set set_from_letter(int c) {
    if(is_letter(c))
        return 1ull << get_letter_idx(c);
    return 0ull;
}

int get_letter_from_idx(int idx) {
    if(idx > -1 && idx < 59) {
        if(idx < 26)
            return idx + LAT_A;
        else
            return (idx == 32) ? CYR_YO : idx + CYR_A - 26 - (idx > 32);
    }
    return -1;
}

void put_utf8_letter(int n) {
    if(is_letter(n)) {
        if(!is_cyrillic(n))
            putchar(n);
        else {
            int j = (n > 1087) ? 0xD1 : 0xD0;
            putchar(j);
            putchar(n - 64 * (j - 0xC2));
        }
    }
}