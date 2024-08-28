#include "liblab11.h"

bool is_separator(int c) {
    if ((c == '\n') || (c == '\0') || (c == ' ') || (c == ',') || (c == '\t'))
        return true;
    return false; 
}

bool is_capital(int c) {
    if(c >= 'A' && c <= 'Z')
        return true;
    return false;
}

bool is_letter(int c) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return true;
    return false;
}

int get_letter_idx(int c) {
    if(c >= 'a' && c <= 'z')
        return c - 'a';
    else if(c >= 'A' && c <= 'Z')
        return c - 'A';
    return -1;
}

int get_letter_from_idx(int idx, bool cap) {
    if(idx < 26) {
        int c = idx + 'a';
        return cap ? c - ('a' - 'A') : c;
    }
    return -1;
}