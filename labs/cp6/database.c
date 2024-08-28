#include "abiturient.h"
#include "libcp6-database.h"
#include "libcp6-log.h"

void print_help() {
    printf("Database operation program. Use commands:\n");
    printf("o - open database from file\nc - close database\np - print database content\n");
    printf("a - add record\nq - quit program\nh - help message\n");
}

int main(void) {
    bool opened = false;
    FILE* db = NULL;
    signal(SIGINT, stop_handler); 
    while(true) {
        int c = getchar();
        if(c == ' ' || c == '\t' || c == '\n' || c == '\0')
            continue;
        if(c == EOF) {
            log_info("Recieved EOF");
            exit(EXIT_SUCCESS);
        }
        switch (c) {
        case 'o':
            if(opened) {
                log_error("Database is already opened");
                continue;
            }
            printf("Filemname: ");
            char filename[32];
            if(!scanf("%s", filename)) {
                log_error("Unable to read filename");
                continue;
            }
            db = db_open(filename);
            if(!db) {
                log_error("Failed to read file");
                continue;
            }
            opened = true;
            log_info("Successfully opened database");
            break;
        case 'c':
            if(!opened) {
                log_error("No database opened");
                continue;
            }
            db_close(db);
            opened = false;
            log_info("Database has been closed");
            break;
        case 'p':
            if(!opened) {
                log_error("No database opened");
                continue;
            }
            rewind(db);
            printf("|     SURNAME      | IN | GENDER | SCH_N | MEDAL | ICT | MATH | RUS | ESSAY |\n");

            Abiturient _a;
            while(db_read(db, &_a)) {
                if(feof(db))
                    break;
                if(ferror(db)) {
                    log_error("File seems to be corrupted");
                    break;
                }
                db_printrecord(_a);
            }
            break;
        case 'a':
            if(!opened) {
                log_error("No database opened");
                continue;
            }
            Abiturient a;
            if(!ab_fromstdin(&a)) {
                log_error("Incorrect input detected. Try again");
                continue;
            }
            if(!db_append(db, a)) {
                log_error("Unable to add record");
                continue;
            }
            log_info("Record added");
            break;
        case 'f':
            if(!opened) {
                log_error("No database opened");
                continue;
            }
            printf("Enter text file name: ");
            char tfn[32];
            scanf("%s", tfn);
            FILE* f = fopen(tfn, "r");
            db_fromtextfile(f, db);
            break;
        case 'q':
            log_info("Exit");
            exit(EXIT_SUCCESS);
            break;
        case 'h':
            print_help();
            break;
        default:
            log_error("Unknown command");
            break;
        }
    }
    return 0;
}