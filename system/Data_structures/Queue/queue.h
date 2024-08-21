

#ifndef _QUEUE_ARRAY_H
#define _QUEUE_ARRAY_H
#include "../../typedef.h"
typedef struct{
    void **QueueArray;
    uint32_t QueueMaxSize;
    sint32 ElementCount;
    sint32 QueueFront;
    sint32 QueueRear;
}Queue_t;

typedef enum {
    QUEUE_NOK=0,
    QUEUE_OK,
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_NULL_POINTER
}QueueStatus_t;

Queue_t *CreateQueue(uint32_t maxSize,QueueStatus_t *ret_status);
QueueStatus_t EnqueueElement(Queue_t *queue_obj , void *ItemPtr);
void *DequeueElement(Queue_t *queue_obj ,QueueStatus_t *ret_status);
void *QueueFront(Queue_t *queue_obj ,QueueStatus_t *ret_status);
void *QueueRear(Queue_t *queue_obj ,QueueStatus_t *ret_status);
QueueStatus_t GetQueueCount(Queue_t *queue_obj , uint32_t *QueueCount);
QueueStatus_t DestroyQueue(Queue_t *queue_obj);

#endif // _QUEUE_ARRAY_H
