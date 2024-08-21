
#include "../../Libraries/Libraries.h"

static uint8_t StackIsEmpty (Stack_t* stack_obj);
static uint8_t StackIsFull (Stack_t* stack_obj);

Stack_t *CreateStack (uint32_t maxSize, StackStatus_t *ret_status){
    Stack_t *my_stack = NULL;
    if(NULL == ret_status){
        *ret_status = STACK_NULL_POINTER;
        my_stack = NULL;
    }
    else{

        my_stack = (Stack_t *)malloc(sizeof(Stack_t));
        if(!my_stack){
            *ret_status = STACK_NOK;
            my_stack = NULL;
        }
        else{
            my_stack->StackTop = -1;
            my_stack->ElementCount = 0;
            my_stack->StackMaxSize = maxSize;
            my_stack->StackArray = (void **)calloc(my_stack->StackMaxSize, sizeof(void *));
            if(!my_stack->StackArray){
                free(my_stack);
                my_stack = NULL;
                *ret_status = STACK_NOK;
            }
            else{
                *ret_status = STACK_OK;
            }
        }
    }
    return my_stack;
}

Stack_t *DestroyStack (Stack_t *stack_obj, StackStatus_t *ret_status){
    if((NULL == ret_status) || (NULL == stack_obj)){
        *ret_status = STACK_NULL_POINTER;
    }
    else{
        free(stack_obj->StackArray);
        free(stack_obj);
        *ret_status = STACK_OK;
    }
    return NULL;
}

StackStatus_t PushStack (Stack_t *stack_obj, void *itemPtr){
    StackStatus_t StackStatus = STACK_NOK;
    if((NULL == stack_obj) || (NULL == itemPtr)){
        StackStatus = STACK_NULL_POINTER;
    }
    else{
        if(StackIsFull(stack_obj)){
            StackStatus = STACK_FULL;
        }
        else{
            (stack_obj->StackTop)++;
            stack_obj->StackArray[stack_obj->StackTop] = itemPtr;
            (stack_obj->ElementCount)++;
            StackStatus = STACK_OK;
        }
    }
    return StackStatus;
}

void *PopStack (Stack_t *stack_obj, StackStatus_t *ret_status){
    void *dataPtrOut = NULL;
    if((NULL == stack_obj) || (NULL == ret_status)){
        *ret_status = STACK_NULL_POINTER;
        dataPtrOut = NULL;
    }
    else{
        if(StackIsEmpty(stack_obj)){
            *ret_status = STACK_EMPTY;
            dataPtrOut = NULL;
        }
        else{
            dataPtrOut = stack_obj->StackArray[stack_obj->StackTop];
            (stack_obj->StackTop)--;
            (stack_obj->ElementCount)--;
            *ret_status = STACK_OK;
        }
    }
    return dataPtrOut;
}

void *StackTop (Stack_t *stack_obj, StackStatus_t *ret_status){
    void *dataPtrOut = NULL;
    if((NULL == stack_obj) || (NULL == ret_status)){
        *ret_status = STACK_NULL_POINTER;
        dataPtrOut = NULL;
    }
    else{
        if(StackIsEmpty(stack_obj)){
            *ret_status = STACK_EMPTY;
            dataPtrOut = NULL;
        }
        else{

            dataPtrOut = stack_obj->StackArray[stack_obj->StackTop];
            *ret_status = STACK_OK;
        }
    }
    return dataPtrOut;
}

StackStatus_t StackCount (Stack_t* stack_obj, uint32_t *stack_count){
    StackStatus_t StackStatus = STACK_NOK;
    if((NULL == stack_obj) || (NULL == stack_count)){
        StackStatus = STACK_NULL_POINTER;
    }
    else{
        *stack_count = stack_obj->ElementCount;
        StackStatus = STACK_OK;
    }
    return StackStatus;
}

static uint8_t StackIsEmpty (Stack_t* stack_obj){
    return (stack_obj->ElementCount == 0);
}

static uint8_t StackIsFull (Stack_t* stack_obj){
    return (stack_obj->ElementCount == stack_obj->StackMaxSize);
}
