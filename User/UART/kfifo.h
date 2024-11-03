#ifndef _KFIFO_H
#define _KFIFO_H

#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "cmsis_gcc.h"
// #include "FreeRTOS.h"

#define uint32_min(x, y) ({       \
    uint32_t _min1 = (x);         \
    uint32_t _min2 = (y);         \
    (void) (&_min1 == &_min2);    \
    _min1 < _min2 ? _min1 : _min2;})

#define KFIFO_STATIC_BUF_SIZE 256

// #define MEMALLOC(size) pvPortMalloc(size)
// #define MEMFREE(ptr) vPortFree(ptr)

#define MEMALLOC(size) malloc(size)
#define MEMFREE(ptr) free(ptr)

__STATIC_INLINE uint32_t roundup_pow2(uint32_t data)
{
    return (1UL << (32UL - (uint32_t) __CLZ((data))));
}

typedef struct kfifo_t
{
    uint32_t size;
    uint32_t in;
    uint32_t out;
    char *buffer;
}kfifo_t;

typedef struct kfifo_static_t
{
    uint32_t size;
    uint32_t in;
    uint32_t out;
    char buffer[KFIFO_STATIC_BUF_SIZE];
}kfifo_static_t;

__STATIC_INLINE uint32_t kfifo_used(kfifo_t *fifo)
{
    return (fifo->in - fifo->out);
}
__STATIC_INLINE uint32_t kfifo_unused(kfifo_t *fifo)
{
    return (fifo->size) - (fifo->in - fifo->out);
}
__STATIC_INLINE void kfifo_flush(kfifo_t *fifo)
{
    fifo->in = 0;
    fifo->out = 0;
}

__STATIC_INLINE uint32_t kfifo_used_s(kfifo_static_t *fifo)
{
    return (fifo->in - fifo->out);
}
__STATIC_INLINE uint32_t kfifo_unused_s(kfifo_static_t *fifo)
{
    return (fifo->size) - (fifo->in - fifo->out);
}
__STATIC_INLINE void kfifo_flush_s(kfifo_static_t *fifo)
{
    fifo->in = 0;
    fifo->out = 0;
}

kfifo_t *kfifo_init(uint32_t size);
uint32_t kfifo_put(kfifo_t *fifo, char *buffer, uint32_t len);
uint32_t kfifo_peek(kfifo_t *fifo, char *buffer, uint32_t len);
uint32_t kfifo_get(kfifo_t *fifo, char *buffer, uint32_t len);

void kfifo_init_s(kfifo_static_t *fifo, uint32_t size);
uint32_t kfifo_put_s(kfifo_static_t *fifo, char *buffer, uint32_t len);
uint32_t kfifo_peek_s(kfifo_static_t *fifo, char *buffer, uint32_t len);
uint32_t kfifo_get_s(kfifo_static_t *fifo, char *buffer, uint32_t len);

#endif