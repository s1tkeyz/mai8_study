#pragma once

#include <string.h>

#define CITY_DB_SIZE 13 

extern const char* CITIES[CITY_DB_SIZE]; 

// City names enumeration
typedef enum City {
    EMPTY, // Special default value
    C_MOSCOW,
    C_MADRID,
    C_DETROIT,
    C_TORONTO,
    C_TOKYO,
    C_MIAMI,
    C_OMSK,
    C_BERLIN,
    C_SYDNEY,
    C_MINSK,
    C_PARIS,
    C_ROME,
} City;

const char* c_to_string(City city);

City c_from_string(char* string);