#include "liblab24-queue.h"

static bool expand_buffer(TQueue* q) {
    int new_capacity = q->capacity * BUFF_EXPAND_MULT;
    Token* new_buffer = (Token*)realloc(q->buffer, new_capacity * sizeof(Token));

    if(!new_buffer)
        return false;

    q->buffer = new_buffer;

    for(int i = 0; i < q->head; ++i) {
        q->buffer[i + q->capacity] = q->buffer[i];
    }

    q->capacity = new_capacity;
    return true;
}

static bool shrink_buffer(TQueue* q) {
    if(q->capacity == MIN_CAPACITY)
        return false;

    int new_capacity = q->capacity / BUFF_EXPAND_MULT;

    if(q->head + q->size > q->capacity) {
        for(int i = q->capacity - 1; i >= q->head; --i)
            q->buffer[i - new_capacity] = q->buffer[i];
        q->head -= new_capacity;
    } else {
        if(q->head >= new_capacity) {
            for(int i = q->head; i < q->head + q->size; ++i)
                q->buffer[i - new_capacity] = q->buffer[i];
            q->head -= new_capacity;
        }
        else {
            if(q->head + q->size >= new_capacity) {
                for(int i = new_capacity; i < q->head + q->size; ++i)
                    q->buffer[i - new_capacity] = q->buffer[i];
            }
        }
    }
    q->buffer = (Token*)realloc(q->buffer, new_capacity * sizeof(Token));
    q->capacity = new_capacity;
    return true;
}

TQueue TQueue_create() {
    TQueue q;
    Token* buff = (Token*)malloc(MIN_CAPACITY * sizeof(Token));
    if (buff != NULL)
        q.buffer = buff;
    q.capacity = MIN_CAPACITY;
    q.head = -1;
    q.size = 0;
    return q;
}

void TQueue_destroy(TQueue* queue) {
    free(queue->buffer);
    free(queue);
}

bool TQueue_empty(TQueue* queue) { return queue->size == 0; }

bool TQueue_push(TQueue* queue, Token value) {
    if(queue->head == -1) {
        queue->head = 0;
        queue->size = 1;
        queue->buffer[queue->head] = value;
        return true;
    }
    if(queue->size == queue->capacity)
        if(!expand_buffer(queue))
            return false;
    queue->buffer[(queue->head + queue->size) % queue->capacity] = value;
    queue->size++;
    return true;
}

Token TQueue_pop(TQueue* queue) {
    Token val = queue->buffer[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
    if(BUFF_EXPAND_MULT * BUFF_EXPAND_MULT * queue->size <= queue->capacity)
        shrink_buffer(queue);
    if(queue->size == 0)
        queue->head = -1;
    return val;
}

void TQueue_print(TQueue* queue) {
    int cnt = 0;
    while(cnt < queue->size) {
        int idx = (cnt + queue->head) % queue->capacity;
        print_token(queue->buffer[idx]);
        cnt++;
    }
    putchar('\n');
}