#pragma once

#include <stdio.h>
#include <stdbool.h>

bool is_sep(int c);

bool is_operator(int c);

bool is_digit(int c);

int get_next_char();