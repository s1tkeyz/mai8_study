#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#define SURNAME_LENGTH 16

// Abituruent structure
typedef struct Abiturient {
    char surname[SURNAME_LENGTH];
    char initials[3];
    uint8_t gender;
    uint16_t school_number;
    uint8_t medalist;
    uint16_t e_ict_pts;
    uint16_t e_math_pts;
    uint16_t e_rus_pts;
    uint8_t passed_essay;
} Abiturient;

// Reads abiturient info from stdin [dialog]
bool ab_fromstdin(Abiturient* a);
