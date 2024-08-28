#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "libcp6-database.h"
#include "libcp6-log.h"

#define DEFAULT_EXAM_SCORE 245

// Help message for user
void print_help() { printf("Usage: program -p <parameter> -f <filename>\n"); }

bool filter(Abiturient a, uint16_t param) {
    uint16_t p = a.e_ict_pts + a.e_math_pts + a.e_rus_pts;
    if(p < param && a.medalist)
        return true;
    return false;
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        print_help();
        exit(EXIT_FAILURE);
    }
    
    int i = 1;

    uint16_t parameter = DEFAULT_EXAM_SCORE;
    char* filename = NULL;

    while(i < argc) {
        if(i + 1 >= argc) {
            log_error("Missing key value");
            exit(EXIT_FAILURE);
        }
        if(strcmp(argv[i], "-p") == 0) {
            parameter = strtoul(argv[i + 1], NULL, 10);
            if(parameter == 0 || parameter == UINT32_MAX) {
                log_error("Invalid parameter value");
                exit(EXIT_FAILURE);
            }
        } else if(strcmp(argv[i], "-f") == 0) {
            filename = argv[i + 1];
        }
        i += 2;
    }

    if(parameter == DEFAULT_EXAM_SCORE)
        log_info("Using default parameter value");

    if(!filename) {
        log_error("Missing filename. Key -f required");
        exit(EXIT_FAILURE);
    }

    FILE* db = db_open(filename);
    if(!db) {
        log_error("Can't open file");
        exit(EXIT_FAILURE);
    }

    printf("Parameter = %hu\n", parameter);
    printf("|     SURNAME      | IN | GENDER | SCH_N | MEDAL | ICT | MATH | RUS | ESSAY |\n");
    Abiturient _a;
    while(db_read(db, &_a)) {
        if(feof(db))
            break;
        if(ferror(db)) {
            log_error("File seems to be corrupted");
            break;
        }
        if(filter(_a, parameter))
            db_printrecord(_a);
    }
    return EXIT_SUCCESS;
}