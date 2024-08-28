#include "enum.h"

const char* CITIES[CITY_DB_SIZE] = {"empty", "moscow", "madrid",
                                    "detroit", "toronto", "tokyo",
                                    "miami", "omsk", "berlin",
                                    "sydney", "minsk", "paris",
                                    "rome"};

const char* c_to_string(City city) { return CITIES[city]; }

City c_from_string(char* string) {
    for(int i = 1; i < CITY_DB_SIZE; ++i) {
        if(!strcmp(string, CITIES[i]))
            return i;
    }
    return EMPTY;
}