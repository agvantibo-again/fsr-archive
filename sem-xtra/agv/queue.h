#include <stdio.h>
#include <stdlib.h>

#include "common.h"

/// DO NOT INCLUDE THIS FILE DIRECTLY ///
#ifndef AGV_QUEUE
#define AGV_QUEUE

void print_impl(char* restrict);
struct Queue mkQueue();
enum RetCode Queue_push(struct Queue* q, int const a);
enum RetCode Queue_front(struct Queue* const q, int* a);
enum RetCode Queue_pop(struct Queue* q, int* a);
enum RetCode Queue_clear(struct Queue* q);

#endif // AGV_QUEUE