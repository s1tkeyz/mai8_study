#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "abiturient.h"

// Opens database from file
FILE* db_open(const char* filename);

// Reads next record from database
bool db_read(FILE* db, Abiturient* abit);

// Closes database
void db_close(FILE* db);

// Moves to next record that satisfices the filter condition
Abiturient db_find(FILE* db, uint16_t param, bool (*f)(Abiturient, uint16_t));

// Appends record to the end of database
bool db_append(FILE* db, Abiturient abit);

// Prints record to the stdout
void db_printrecord(Abiturient abit);

// Appends data from text file
bool db_fromtextfile(FILE* f, FILE* db);