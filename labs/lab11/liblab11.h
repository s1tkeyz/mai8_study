#ifndef LIBLAB11_H
#define LIBLAB11_H

typedef enum {
    false,
    true,
} bool;

typedef enum {
    STATE_OUT_OF_WORD,
    STATE_WORD_DECODING,
    STATE_SKIP_WORD,
} state;

bool is_separator(int c);

bool is_capital(int c);

bool is_letter(int c);

int get_letter_idx(int c);

int get_letter_from_idx(int idx, bool cap); 

#endif