#ifndef INC_05_ENC_DEC_FIFO_H
#define INC_05_ENC_DEC_FIFO_H
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <jemalloc/jemalloc.h>

typedef struct NODE {
    struct NODE *prev;
    struct NODE *next;
    uint8_t *data;
} node_t;

typedef struct FIFO {
    node_t *first;
    node_t *last;

    size_t count;
    pthread_mutex_t *mutex;

    size_t (*count_mutex)(struct FIFO*);
    void (*enqueue)(struct FIFO*, uint8_t*);
    uint8_t* (*dequeue)(struct FIFO*);
    void (*free)(struct FIFO**, bool);
} fifo_t;

typedef struct {
    fifo_t *input;
    fifo_t *output;
    bool kill;
} bus_t;

fifo_t *fifo_init();
void fifo_enqueue(fifo_t *queue, uint8_t *data);
uint8_t *fifo_dequeue(fifo_t *queue);
void fifo_free(fifo_t **queue, bool free_data);
size_t fifo_count(fifo_t *queue);

#ifndef TESTS_DISABLED

#include <stdio.h>

bool test_fifo_initialize();

bool test_fifo_debug_count();

bool test_fifo_empty_enqueue();

bool test_fifo_empty_dequeue();

bool test_fifo_empty_free();

bool test_fifo_singleton_dequeue();

bool test_fifo_multiple_enqueues();

bool test_fifo_multiple_dequeues();

bool test_fifo_free();

#endif
#endif //INC_05_ENC_DEC_FIFO_H