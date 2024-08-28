#include <stdio.h>
#include "liblab13.h"

int main(void) {
    set similar_letters = UINT64_MAX;
    set current_word_letters = 0ull;
    
    const set VOWELS_SET = 0x700420985104111;

    int c = 0;
    state state = STATE_IN_WORD;

    do {
        c = get_utf8_letter();
        if(is_separator(c)) {
            if(state == STATE_IN_WORD) {
                similar_letters &= current_word_letters;
                current_word_letters = 0ull;
                state = STATE_OUT_OF_WORD;
            }
        }
        else {
            current_word_letters |= set_from_letter(c);
            state = STATE_IN_WORD;
        }  
    }
    while(c != EOF);

    printf("\nGLOBAL VOWELS: ");

    set vowels_found = similar_letters & VOWELS_SET;
    int idx = 0;
    while(vowels_found > 0) {
        if(vowels_found & 1) {
            put_utf8_letter(get_letter_from_idx(idx));
            putchar(' ');
        }
        idx++;
        vowels_found /= 2;
    }

    putchar('\n');
    return 0;
}