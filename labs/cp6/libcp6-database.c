#include "libcp6-database.h"
#include "libcp6-log.h"

FILE* db_open(const char* filename) { return fopen(filename, "a+b"); }

bool db_read(FILE* db, Abiturient* abit) {
    return fread(abit, sizeof(Abiturient), 1, db) == 1;
}

void db_close(FILE* db) { fclose(db); }

Abiturient db_find(FILE* db, uint16_t param, bool (*f)(Abiturient, uint16_t)) {
    Abiturient a;
    while(!feof(db) && !f(a, param))
        db_read(db, &a);
    return a;
}

bool db_append(FILE* db, Abiturient abit) {
    return fwrite(&abit, sizeof(Abiturient), 1, db) == 1;
}

void db_printrecord(Abiturient abit) {
    char g = abit.gender ? 'm' : 'f';
    char m = abit.medalist ? 'y' : 'n';
    char e = abit.passed_essay ? 'y' : 'n';
    printf("| %16s | %2s | %6c | %5hu | %5c | %3hu | %4hu | %3hu | %5c |\n", 
    abit.surname,
    abit.initials,
    g,
    abit.school_number,
    m,
    abit.e_ict_pts,
    abit.e_math_pts,
    abit.e_rus_pts,
    e);
}

bool db_fromtextfile(FILE* f, FILE* db) {
    if(!db)
        return false;
    Abiturient abit;
    
    while(fscanf(f, "%s %s %hhu %hu %hhu %hu %hu %hu %hhu",
        abit.surname,
        abit.initials,
        &abit.gender,
        &abit.school_number,
        &abit.medalist,
        &abit.e_ict_pts,
        &abit.e_math_pts,
        &abit.e_rus_pts,
        &abit.passed_essay) == 9) {
        fwrite(&abit, sizeof(Abiturient), 1, db);
    }
    return true;
}