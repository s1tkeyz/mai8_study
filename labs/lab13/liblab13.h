#ifndef LIBLAB13_H
#define LIBLAB13_H

#include <inttypes.h>

#define CYR_CAP_A 1040
#define CYR_CAP_YA 1071
#define CYR_CAP_YO 1025
#define CYR_A 1072
#define CYR_YA 1103
#define CYR_YO 1105

#define LAT_CAP_A 65
#define LAT_CAP_Z 90
#define LAT_A 97
#define LAT_Z 122

typedef uint64_t set;

typedef enum {
    STATE_OUT_OF_WORD,
    STATE_IN_WORD,
} state;

typedef enum {
    false,
    true,
} bool;

bool is_separator(int c);

bool is_letter(int c);

bool is_cyrillic(int c);

bool is_capital(int c);

int to_lower(int c);

int get_utf8_letter();

set set_from_letter(int c);

int get_letter_idx(int c);

int get_letter_from_idx(int idx);

void put_utf8_letter(int n);

#endif