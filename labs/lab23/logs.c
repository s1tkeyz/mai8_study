#include "logs.h"
#include <signal.h>

void log_error(const char* message) { fprintf(stderr, "[ERROR]: %s\n", message); }

void log_info(const char* message) { printf("[INFO]: %s\n", message); }

void stop_handler(int param) {
    signal(SIGINT, stop_handler);
    log_info("Recieved SIGINT");
}