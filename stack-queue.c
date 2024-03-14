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

int main() {
    // testLinkStack();
    testLinkQueue();
    return 0;
}