#include <stdio.h>
#include <stdlib.h>

// 1. define
// 2. create 
// 3. append
// 4. insert
// 5. print
// 6. free

// 7. reverse
// 8. check circle
// 9. merge sorted linked list
// 10. delete last kth
// 11. find middle node

typedef struct SinglyLinkedNode {
    int data;
    struct SinglyLinkedNode *next;
} SinglyLinkedNode;

SinglyLinkedNode *create_node(int value) {
    SinglyLinkedNode *new_node = (SinglyLinkedNode *)malloc(sizeof(SinglyLinkedNode));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(SinglyLinkedNode **head_ref, int value) {
    SinglyLinkedNode *new_node = create_node(value);
    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        SinglyLinkedNode *current = *head_ref;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void insert_node(SinglyLinkedNode **head_ref, int value) {
    SinglyLinkedNode *new_node = create_node(value);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void free_linked_list(SinglyLinkedNode *head) {
    SinglyLinkedNode *current = head;
    while (current) {
        SinglyLinkedNode *next_node = current->next;
        current->next = NULL;
        free(current);
        current = next_node;
    }
}

void print_linked_list(SinglyLinkedNode *head) {
    SinglyLinkedNode *current = head;
    while (current) {
        printf("value = %d\n", current->data);
        current = current->next;
    }
}

void reverse(SinglyLinkedNode **head_ref) {
    SinglyLinkedNode *current = *head_ref;
    SinglyLinkedNode *prev_node = NULL;
    while (current) {
        SinglyLinkedNode *next_node = current->next; // tail
        if (next_node == NULL) {
            *head_ref = current;
        }
        current->next = prev_node;
        prev_node = current;
        current = next_node;
    }
}

int check_circle(SinglyLinkedNode *head) {
    SinglyLinkedNode *slow, *fast;
    slow = fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

SinglyLinkedNode *find_middle_node(SinglyLinkedNode *head) {
    SinglyLinkedNode *slow, *fast;
    slow = fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void delete_last_kth(SinglyLinkedNode **head_ref, int k) {
    // 1. fast move k step
    SinglyLinkedNode *fast = *head_ref;
    for (int i = 0; i < k; i++) {
        fast = fast->next;
    }

    // 2. move slow and fast
    SinglyLinkedNode *slow = *head_ref;
    SinglyLinkedNode *prev_node = NULL;
    while (fast) {
        fast = fast->next;
        prev_node = slow;
        slow = slow->next;
    }
    
    // 3. delete kth node
    if (prev_node == NULL) {
        *head_ref = (*head_ref)->next;
    } else {
        prev_node->next = slow->next;
    }

    // 4. free
    free(slow);
}

// 1 3 5 | 2 4 6 -> 3 5 | 2 4 6
void move_node(SinglyLinkedNode **dest_ref, SinglyLinkedNode **src_head_ref) {
    SinglyLinkedNode *new_node = *src_head_ref;
    *src_head_ref = new_node->next;
    new_node->next = *dest_ref;
    *dest_ref = new_node;
}

SinglyLinkedNode *merge_sorted_linked_list(SinglyLinkedNode *a , SinglyLinkedNode *b) {
    SinglyLinkedNode result;
    SinglyLinkedNode *dest = &result;

    while (1) {
        if (a == NULL) {
            dest->next = b;
            break;
        } else if (b == NULL) {
            dest->next = a;
            break;
        }

        if (a->data < b->data) {
            move_node(&(dest->next), &a);
        } else {
            move_node(&(dest->next), &b);
        }
        dest = dest->next;
    }

    return result.next;
}

void test_create_print_free() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);

    print_linked_list(head);

    free_linked_list(head);
}

void test_insert() {
    SinglyLinkedNode *head = NULL;
    insert_node(&head, 3);
    insert_node(&head, 2);
    insert_node(&head, 1);

    print_linked_list(head);

    free_linked_list(head);
}

void test_reverse() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    print_linked_list(head);

    printf("---\n");
    reverse(&head);
    print_linked_list(head);

    free_linked_list(head);
}

void test_circle() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);

    head->next->next->next->next = head;

    int has_circle = check_circle(head);
    printf("has circle = %d\n", has_circle);

    free_linked_list(head);
}

void test_middle_node() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);

    SinglyLinkedNode *middle_node = find_middle_node(head);
    printf("middle node value = %d\n", middle_node->data);

    free_linked_list(head);
}

void test_delete_last_kth() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);
    print_linked_list(head);

    delete_last_kth(&head, 2);
    print_linked_list(head);

    free_linked_list(head);
}

void test_merge_sorted_linked_list() {
    SinglyLinkedNode *a = NULL;
    append_node(&a, 1);
    append_node(&a, 3);
    append_node(&a, 5);

    SinglyLinkedNode *b = NULL;
    append_node(&b, 2);
    append_node(&b, 4);
    append_node(&b, 6);

    SinglyLinkedNode *c = merge_sorted_linked_list(a, b);
    print_linked_list(c);

    free_linked_list(c);
}

int main(void) {
    printf("--- begin ---\n");
    // test_create_print_free();
    // test_insert();
    // test_reverse();
    // test_circle();
    // test_middle_node();
    // test_delete_last_kth();
    test_merge_sorted_linked_list();
    printf("--- end ---\n");
    return 0;
}