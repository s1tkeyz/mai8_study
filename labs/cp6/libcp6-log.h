#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

// Logs info message to the stdout
void log_info(const char* message);

// Logs error to the stderr
void log_error(const char* message);

// Handles Ctrl+C
void stop_handler(int param);
