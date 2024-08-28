#pragma once

#include <stdio.h>

// Logs error message to stdout
void log_error(const char* message);

// Logs info message to stdout
void log_info(const char* message);

// Handles SIGINT
void stop_handler(int param);