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

void testLinkQueue() {

}

int main() {
    printf("stack and queue\n");
    testLinkStack();
    // testLinkQueue();
    return 0;
}