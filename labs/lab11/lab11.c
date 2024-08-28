#include <stdio.h>
#include "liblab11.h"

int main(void) {
    int c = getchar();
    
    int word_idx = 0;
    state state = STATE_OUT_OF_WORD;

    while(c != EOF) {
        if(is_separator(c)) {
            state = STATE_OUT_OF_WORD;
            if(c == '\n' || c == '\0')
                word_idx = 0;
        }
        else {
            if(state == STATE_OUT_OF_WORD) {
                word_idx++;
                if(word_idx == 26) {
                    state = STATE_SKIP_WORD;
                    word_idx = 0;
                }
                else
                    state = STATE_WORD_DECODING;   
            }

            if(state == STATE_WORD_DECODING && is_letter(c)) {
                bool wc = is_capital(c);
                int e = get_letter_idx(c);
                int d = e - word_idx;

                if(d >= 0)
                    c = get_letter_from_idx(d, wc);
                else 
                    c = get_letter_from_idx(26 - (-d % 26), wc);
            }
        }
        putchar(c);
        c = getchar();
    }
    return 0;
}