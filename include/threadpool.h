/*
File: threadPool.h
Author: Sappir Bohbot
Date: 4/30/2023.
Code Based on: https://nachtimwald.com/2019/04/12/thread-pool-in-c/
*/

#ifndef __TPOOL_H__
#define __TPOOL_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>

/*
Since the work queue is implemented as a linked list work_first and work_last are used to push and pop work objects.
There is a single mutex (work_mutex) which is used for all locking.
*/
typedef struct tpool tpool_t;

typedef void (*thread_func_t)(void *arg);

/*When creating the pool the default is two threads if zero was specified. Otherwise, the caller specified number will be used.
Params: Nums = number of threadds to open*/
tpool_t *tpool_create(size_t num);

/*
destroy will only be called when all work is done and nothing is processing.
However, it’s possible someone is trying to force processing to stop. In which case there will be work queued and we need to get clean it up.
*/
void tpool_destroy(tpool_t *tm);

/*
Adding to the work queue consists of creating a work object, locking the mutex and adding the object to the liked list.
*/
bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg);

/*
This is a blocking function that will only return when there is no work.
The mutex is locked and we we wait in a conditional if there are any threads processing,
 if there is still work to do or if the threads are stopping and not all have exited.
*/
void tpool_wait(tpool_t *tm);

#endif /* __TPOOL_H__ */

