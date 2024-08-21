
#include "../../Libraries/Libraries.h"

Queue_t *CreateQueue(uint32_t maxSize,QueueStatus_t *ret_status){
    Queue_t *my_Queue;
    my_Queue =(Queue_t *)malloc(sizeof(Queue_t));
    if(NULL == my_Queue){
        *ret_status = QUEUE_NULL_POINTER;
        my_Queue = NULL;
    }
    else{
        my_Queue->QueueArray = (void **)calloc(maxSize , sizeof(void *));
        if(NULL == my_Queue->QueueArray){
            *ret_status = QUEUE_NULL_POINTER;
            my_Queue = NULL;
        }
        else{
            my_Queue->ElementCount=0;
            my_Queue->QueueFront=-1;
            my_Queue->QueueRear=-1;
            my_Queue->QueueMaxSize=maxSize;
            *ret_status = QUEUE_OK;
        }
    }
    return my_Queue;
}
QueueStatus_t EnqueueElement(Queue_t *queue_obj , void *ItemPtr){
    QueueStatus_t Status = QUEUE_NOK;
    if((queue_obj== NULL) || (ItemPtr == NULL)){
        Status = QUEUE_NULL_POINTER;
    }
    else{
            if(queue_obj->ElementCount == queue_obj->QueueMaxSize){
                Status = QUEUE_FULL;
            }
            else{
                    (queue_obj->QueueRear)++;
                    if(queue_obj->QueueRear == queue_obj->QueueMaxSize){
                        queue_obj->QueueRear = 0;
                    }
                    queue_obj->QueueArray[queue_obj->QueueRear]= ItemPtr;
                    if(queue_obj->ElementCount ==0 ){
                         queue_obj->QueueFront = 0;
                         queue_obj->ElementCount = 1;
                    }
                    else{
                        (queue_obj->ElementCount)++;
                    }
                     Status = QUEUE_OK;
            }
    }
    return Status;
}
void *DequeueElement(Queue_t *queue_obj ,QueueStatus_t *ret_status){
    void *ReturnElem= NULL;
    if((queue_obj== NULL) || (ret_status == NULL))
    {
        *ret_status = QUEUE_NULL_POINTER;
        ReturnElem= NULL;
    }
    else
    {
        if(queue_obj->ElementCount == 0)
        {
            *ret_status = QUEUE_EMPTY;
            ReturnElem= NULL;
        }
        else
        {
            ReturnElem = queue_obj->QueueArray[queue_obj->QueueFront];
            (queue_obj->QueueFront)++;
            if(queue_obj->QueueFront == queue_obj->QueueMaxSize)
            {
                queue_obj->QueueFront =0 ;
            }
            if(1== queue_obj->ElementCount)
            {
                queue_obj->QueueFront = -1;
                queue_obj->QueueRear = -1;
            }
            (queue_obj->ElementCount)--;

            *ret_status = QUEUE_OK;
        }
    }
    return ReturnElem ;
}
void *QueueFront(Queue_t *queue_obj ,QueueStatus_t *ret_status){
    void *ReturnElem= NULL;
    if((queue_obj== NULL) || (ret_status == NULL))
    {
        *ret_status = QUEUE_NULL_POINTER;
        ReturnElem= NULL;
    }
    else
    {
        if(queue_obj->ElementCount == 0)
        {
            *ret_status = QUEUE_EMPTY;
            ReturnElem= NULL;
        }
        else
        {
            ReturnElem = queue_obj->QueueArray[queue_obj->QueueFront];
            *ret_status = QUEUE_OK;
        }
    }
    return ReturnElem ;
}
void *QueueRear(Queue_t *queue_obj ,QueueStatus_t *ret_status){
    void *ReturnElem= NULL;
    if((NULL == queue_obj)||(NULL == ret_status)){
        *ret_status = QUEUE_NULL_POINTER;
        ReturnElem= NULL;
    }
    else{
        if(queue_obj->ElementCount == 0){
            *ret_status = QUEUE_EMPTY;
            ReturnElem= NULL;
        }
        else{
            ReturnElem= queue_obj->QueueArray[queue_obj->QueueRear];
            *ret_status = QUEUE_OK;
        }
    }
    return ReturnElem;
}
QueueStatus_t GetQueueCount(Queue_t *queue_obj , uint32_t *QueueCount){
    QueueStatus_t status = QUEUE_NOK;
    if((NULL == queue_obj) || (NULL == QueueCount)){
        status = QUEUE_NULL_POINTER;
    }
    else{
        if(queue_obj->ElementCount == 0){
            *QueueCount = 0;
        }
        else{
            *QueueCount = queue_obj->ElementCount;
        }
        status = QUEUE_OK;
    }
    return status;
}
QueueStatus_t DestroyQueue(Queue_t *queue_obj){
    QueueStatus_t status = QUEUE_NOK;
    if(NULL == queue_obj){
        status = QUEUE_NULL_POINTER;
    }
    else{
            free(queue_obj->QueueArray);
            free(queue_obj);
            status = QUEUE_OK;
    }
    return status;
}

