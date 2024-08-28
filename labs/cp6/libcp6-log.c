#include "libcp6-log.h"

void log_info(const char* message) { printf("[INFO]: %s\n", message); }

void log_error(const char* message) { fprintf(stderr, "[ERROR]: %s\n", message); }

void stop_handler(int param) {
    log_info("Recieved SIGINT");
    exit(EXIT_SUCCESS);
}