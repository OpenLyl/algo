#include <stdio.h>
#include <stdlib.h>

// define
// create
// push
// pop
// dump
// destroy

typedef struct LinkStackNode {
    int data;
    struct LinkStackNode *next;
} LinkStackNode;

typedef struct LinkStack {
    LinkStackNode *top;
} LinkStack;

#define LINK_STACK_IS_EMPTY(link_stack) (link_stack->top == NULL)

LinkStack *linkStackCreate() {
    LinkStack *link_stack = (LinkStack *)malloc(sizeof(LinkStack));
    if (link_stack == NULL) {
        return NULL;
    }
    link_stack->top = NULL;
    return link_stack;
}

int linkStackPush(LinkStack *link_stack, int value) {
    if (link_stack == NULL) {
        return -1;
    }

    LinkStackNode *node = (LinkStackNode *)malloc(sizeof(LinkStackNode));
    if (node == NULL) {
        return -1;
    }
    
    node->data = value;
    node->next = link_stack->top;
    link_stack->top = node;
    return 0;
}

int linkStackPop(LinkStack *link_stack, int *value) {
    if (LINK_STACK_IS_EMPTY(link_stack)) {
        return -1;
    }

    LinkStackNode *top = link_stack->top;
    *value = top->data;
    link_stack->top = top->next;
    free(top);
    return 0;
}

int linkStackIsEmpty(LinkStack *link_stack) {
    return LINK_STACK_IS_EMPTY(link_stack);
}

void linkStackDump(LinkStack *link_stack) {
    LinkStackNode *top = link_stack->top;
    int index = 0;
    while (top) {
        printf("link stack item[%d] = %d\n", index, top->data);
        top = top->next;
        index++;
    }
    printf("\r\n");
}

void linkStackDestroy(LinkStack *link_stack) {
    if (link_stack == NULL) {
        return;
    }

    while (!LINK_STACK_IS_EMPTY(link_stack)) {
        LinkStackNode *top = link_stack->top;
        link_stack->top = top->next;
        free(top);
    }

    free(link_stack);
}

void testLinkStack() {
    LinkStack *link_stack = linkStackCreate();

    for (int i = 0; i < 4; i++) {
        int res = linkStackPush(link_stack, i);
        if (res < 0) {
            printf("link stack push failed\n");
        }
    }
    linkStackDump(link_stack);

    int value;
    for (int i = 0; i < 5; i++) {
        int res = linkStackPop(link_stack, &value);
        if (res < 0) {
            printf("link stack pop failed\n");
        } else {
            printf("link stack pop value = %d\n", value);
        }
    }
    linkStackDump(link_stack);
    
    linkStackDestroy(link_stack);
}

// define
// create
// enqueue
// dequeue
// dump
// destroy

typedef struct LinkQueueNode {
    int data;
    struct LinkQueueNode *next;
} LinkQueueNode;

typedef struct LinkQueue {
    LinkQueueNode *head;
    LinkQueueNode *tail;
} LinkQueue;

#define LINK_QUEUE_IS_EMPTY(link_queue) (link_queue->head == NULL)

LinkQueue *linkQueueCreate() {
    LinkQueue *link_queue = (LinkQueue *)malloc(sizeof(LinkQueue));
    if (link_queue == NULL) {
        return NULL;
    }

    link_queue->head = NULL;
    link_queue->tail = NULL;

    return link_queue;
}

int linkQueueEnqueue(LinkQueue *link_queue, int value) {
    LinkQueueNode *node = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if (node == NULL) {
        return -1;
    }
    node->data = value;
    node->next = NULL;

    if (link_queue->head == NULL) {
        link_queue->head = node;
    } else {
        link_queue->tail->next = node;
    }
    link_queue->tail = node;

    return 0;
}

int linkQueueDequeue(LinkQueue *link_queue, int *value) {
    if (LINK_QUEUE_IS_EMPTY(link_queue)) {
        return -1;
    }

    LinkQueueNode *head = link_queue->head;
    *value = head->data;
    link_queue->head = head->next;
    if (link_queue->head == NULL) {
        link_queue->tail = NULL;
    }
    free(head);

    return 0;
}

int linkQueueIsEmpty(LinkQueue *link_queue) {
    return LINK_QUEUE_IS_EMPTY(link_queue);
}

void linkQueueDump(LinkQueue *link_queue) {
    LinkQueueNode *node = link_queue->head;
    int index = 0;
    while (node) {
        printf("link queue items[%d] = %d\n", index, node->data);
        node = node->next;
        index++;
    }
    printf("\r\n");
} 

void linkQueueDestroy(LinkQueue *link_queue) {
    if (link_queue == NULL) {
        return;
    }

    int value;
    while (!LINK_QUEUE_IS_EMPTY(link_queue)) {
        linkQueueDequeue(link_queue, &value);
    }
    free(link_queue);
}

void testLinkQueue() {
    LinkQueue *link_queue = linkQueueCreate();

    for (int i = 0; i < 5; i++) {
        int res = linkQueueEnqueue(link_queue, i);
        if (res < 0) {
            printf("link queue enqueue failed\n");
        }
    }
    linkQueueDump(link_queue);

    int value;
    for (int i = 0; i < 6; i++) {
        int res = linkQueueDequeue(link_queue, &value);
        if (res < 0) {
            printf("link queue dequeue failed\n");
        } else {
            printf("link queue dequeue value = %d\n", value);
        }
    }

    int res = linkQueueEnqueue(link_queue, 100);
    if (res < 0) {
        printf("link queue enqueue 100 failed\n");
    }
    linkQueueDump(link_queue);

    linkQueueDestroy(link_queue);
}

typedef struct {
    LinkQueue *main_queue;
    LinkQueue *temp_queue;
} QueueStack;

QueueStack *queueStackCreate() {
    QueueStack *queue_stack = (QueueStack *)malloc(sizeof(QueueStack));
    if (queue_stack == NULL) {
        return NULL;
    }

    queue_stack->main_queue = linkQueueCreate();
    queue_stack->temp_queue = linkQueueCreate();

    return queue_stack;
}

int queueStackPush(QueueStack *queue_stack, int value) {
    int main_dequeue_value;
    while(!LINK_QUEUE_IS_EMPTY(queue_stack->main_queue)) {
        int res = linkQueueDequeue(queue_stack->main_queue, &main_dequeue_value);
        if (res == 0) {
            linkQueueEnqueue(queue_stack->temp_queue, main_dequeue_value);
        }
    }

    int res = linkQueueEnqueue(queue_stack->main_queue, value);

    int temp_dequeue_value;
    while(!LINK_QUEUE_IS_EMPTY(queue_stack->temp_queue)) {
        int res = linkQueueDequeue(queue_stack->temp_queue, &temp_dequeue_value);
        if (res == 0) {
            linkQueueEnqueue(queue_stack->main_queue, temp_dequeue_value);
        }
    }

    return res;
}

int queueStackPop(QueueStack *queue_stack, int *value) {
    return linkQueueDequeue(queue_stack->main_queue, value);
}

int queueStackPeek(QueueStack *queue_stack) {
    return queue_stack->main_queue->head->data;
}

int queueStackIsEmpty(QueueStack *queue_stack) {
    return linkQueueIsEmpty(queue_stack->main_queue);
}

void queueStackDump(QueueStack *queue_stack) {
    linkQueueDump(queue_stack->main_queue);
}

void queueStackDestroy(QueueStack *queue_stack) {
    linkQueueDestroy(queue_stack->main_queue);
    linkQueueDestroy(queue_stack->temp_queue);
    free(queue_stack);
}

void testStackUseQueue() {
    QueueStack *queue_stack = queueStackCreate();
    if (queue_stack == NULL) {
        printf("queue stack create failed\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        int res = queueStackPush(queue_stack, i);
        if (res < 0) {
            printf("queue stack push value failed\n");
        }
    }
    queueStackDump(queue_stack);

    int value;
    int res = queueStackPop(queue_stack, &value);
    if (res < 0) {
        printf("queue stack pop failed\n");
    } else {
        printf("queue stack pop value = %d\n", value);
    }
    queueStackDump(queue_stack);  

    value = queueStackPeek(queue_stack);
    printf("queue stack top value = %d\n", value);

    int is_empty = queueStackIsEmpty(queue_stack);
    printf("queue stack is empty %d\n", is_empty);

    queueStackDestroy(queue_stack);
}

typedef struct  {
    LinkStack *main_stack; // queue sequence
    LinkStack *temp_stack; // stack sequence
} StackQueue;

StackQueue *stackQueueCreate() {
    StackQueue *stack_queue = (StackQueue*)malloc(sizeof(StackQueue));
    if (stack_queue == NULL) {
        return NULL;
    }

    stack_queue->main_stack = linkStackCreate();
    stack_queue->temp_stack = linkStackCreate();

    return stack_queue;
}

void exchangeStack(StackQueue *stack_queue) {
    int value;
    while(!linkStackIsEmpty(stack_queue->temp_stack)) {
        linkStackPop(stack_queue->temp_stack, &value);
        linkStackPush(stack_queue->main_stack, value);
    }
}

int stackQueueEnqueue(StackQueue *stack_queue, int value) {
    return linkStackPush(stack_queue->temp_stack, value);
}

int stackQueueDequeque(StackQueue *stack_queue, int *value) {
    if (linkStackIsEmpty(stack_queue->main_stack)) {
        exchangeStack(stack_queue);
    }
    return linkStackPop(stack_queue->main_stack, value);
}

int stackQueuePeek(StackQueue *stack_queue) {
    if (linkStackIsEmpty(stack_queue->main_stack)) {
        exchangeStack(stack_queue);
    }
    return stack_queue->main_stack->top->data;
}

int stackQueueIsEmpty(StackQueue *stack_queue) {
    return linkStackIsEmpty(stack_queue->main_stack) && linkStackIsEmpty(stack_queue->temp_stack);
}

void stackQueueDump(StackQueue *stack_queue) {
    if (linkStackIsEmpty(stack_queue->main_stack)) {
        exchangeStack(stack_queue);
    }
    return linkStackDump(stack_queue->main_stack);
}

void stackQueueDestory(StackQueue *stack_queue) {
    linkStackDestroy(stack_queue->temp_stack);
    linkStackDestroy(stack_queue->main_stack);
    free(stack_queue);
}

void testQueueUseStack() {
    StackQueue *stack_queue = stackQueueCreate();
    if (stack_queue == NULL) {
        printf("stack queue create failed\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        int res = stackQueueEnqueue(stack_queue, i);
        if (res < 0) {
            printf("stack queue enqueue %d failed\n", i);
        }
    }
    stackQueueDump(stack_queue);

    int value;
    int res = stackQueueDequeque(stack_queue, &value);
    if (res < 0) {
        printf("stack queue dequeue failed\n");
    } else {
        printf("stack queue dequeue value = %d\n", value);
    }

    value = stackQueuePeek(stack_queue);
    printf("stack queue peek value = %d\n", value);
    stackQueueDump(stack_queue);

    for (int i = 0; i < 3; i++) {
        stackQueueDequeque(stack_queue, &value);
    }

    int is_empty = stackQueueIsEmpty(stack_queue);
    printf("stack queue is empty %d\n", is_empty);

    stackQueueDestory(stack_queue);
}

int main() {
    // testLinkStack();
    // testLinkQueue();
    // testStackUseQueue();
    testQueueUseStack();
    return 0;
}