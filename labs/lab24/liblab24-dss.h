#pragma once

#include <math.h>
#include "liblab24-token.h"
#include "liblab24-stack.h"
#include "liblab24-queue.h"

bool read_expression(TQueue* out);

bool dijkstra_sort(TQueue* expr, TQueue* out, double xval);

bool calculate(TQueue* polish, double* res);