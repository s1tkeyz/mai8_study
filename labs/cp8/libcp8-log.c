#include "libcp8-log.h"

void log_error(const char* message) {
    fprintf(stderr, "[ERROR]: %s\n", message);
}

void log_info(const char* message) {
    printf("[INFO]: %s\n", message);
}

void log_input(const char* message) {
    printf("[INPUT]: %s >", message);
}