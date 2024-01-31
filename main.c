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

// 12. remove =k elements
// 13. rotate right
// 14. get intersection
// 15. check palinkdrome

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

void free_linked_list(SinglyLinkedNode **head_ref) {
    if (*head_ref == NULL) return;
    SinglyLinkedNode *current = *head_ref;
    while (current) {
        SinglyLinkedNode *next_node = current->next;
        current->next = NULL;
        free(current);
        current = next_node;
    }
    *head_ref = NULL;
}

void print_linked_list(SinglyLinkedNode *head) {
    SinglyLinkedNode *current = head;
    while (current) {
        printf("value = %d\n", current->data);
        current = current->next;
    }
}

void test_create_print_free() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);

    print_linked_list(head);

    free_linked_list(&head);
}

void test_insert() {
    SinglyLinkedNode *head = NULL;
    insert_node(&head, 3);
    insert_node(&head, 2);
    insert_node(&head, 1);

    print_linked_list(head);

    free_linked_list(&head);
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

void test_reverse() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    print_linked_list(head);

    printf("---\n");
    reverse(&head);
    print_linked_list(head);

    free_linked_list(&head);
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

void test_circle() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);

    head->next->next->next->next = head;

    int has_circle = check_circle(head);
    printf("has circle = %d\n", has_circle);

    free_linked_list(&head);
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

void test_middle_node() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);

    SinglyLinkedNode *middle_node = find_middle_node(head);
    printf("middle node value = %d\n", middle_node->data);

    free_linked_list(&head);
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

    free_linked_list(&head);
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

    free_linked_list(&c);
}

void remove_node(SinglyLinkedNode **head_ref, int value) {
    SinglyLinkedNode *head = *head_ref;
    if (head == NULL) return;

    SinglyLinkedNode *current = head;
    SinglyLinkedNode *prev_node = NULL;

    while (current->next) {
        SinglyLinkedNode *next_node = current->next;
        if (current->data == value) {
            if (prev_node == NULL) {
                *head_ref = next_node;
            } else {
                prev_node->next = next_node;
            }
            free(current);
        } else {
            prev_node = current;
        }
        current = next_node;
    }
}

void test_remove_elements() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 2);
    append_node(&head, 5);

    // remove_node(&head, 1);
    // print_linked_list(head);

    remove_node(&head, 2);
    print_linked_list(head);

    free_linked_list(&head);
}

SinglyLinkedNode *remove_node_ret(SinglyLinkedNode *head, int value) {
    if (head == NULL) return head;

    SinglyLinkedNode dummy;
    dummy.next = head;

    SinglyLinkedNode *current = head;
    SinglyLinkedNode *prev_node = &dummy;
    while (current->next) {
        SinglyLinkedNode *next_node = current->next;
        if (current->data == value) {
            prev_node->next = next_node;
            free(current);
        } else {
            prev_node = current;
        }
        current = next_node;
    }

    return dummy.next;
}

void test_remove_elements_ret() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 2);
    append_node(&head, 5);

    SinglyLinkedNode *removed_head = remove_node_ret(head, 2);
    print_linked_list(removed_head);
}

void rotate_right(SinglyLinkedNode **head_ref, int k) {
    SinglyLinkedNode *head = *head_ref;
    // 1. tail link head
    int len = 1;
    SinglyLinkedNode *tail = head;
    while (tail->next) {
        tail = tail->next;
        len++;
    }
    tail->next = head;

    // 2. find new head node, prev
    SinglyLinkedNode *current = head;
    SinglyLinkedNode *prev_node = NULL;
    for (int i = 0; i < len - (k % len); i++) {
        prev_node = current;
        current = current->next;
    }

    // 3. change
    if (current && prev_node) {
        prev_node->next = NULL;
        *head_ref = current;
    }
}

void test_rotate() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);

    rotate_right(&head, 2);

    print_linked_list(head);
    
    free_linked_list(&head);
}

SinglyLinkedNode *get_intersection_node(SinglyLinkedNode *headA, SinglyLinkedNode *headB) {
    if (headA == NULL || headB == NULL) return NULL;

    SinglyLinkedNode *a = headA;
    SinglyLinkedNode *b = headB;
    while (a != b) {
        a = (a == NULL) ? headB : a->next;
        b = (b == NULL) ? headA : b->next;
    }

    return a;
}

void test_get_intersection() {
    SinglyLinkedNode *common = create_node(10);

    SinglyLinkedNode *headA = NULL;
    append_node(&headA, 1);
    headA->next = common;
    append_node(&headA, 2);
    append_node(&headA, 3);
    append_node(&headA, 4);

    SinglyLinkedNode *headB = NULL;
    append_node(&headB, 1);
    append_node(&headB, 2);
    headB->next->next = common;

    SinglyLinkedNode *intersection_node = get_intersection_node(headA, headB);
    if (intersection_node) {
        printf("intersection node = %d\n", intersection_node->data);
    }

    free_linked_list(&headA);
    free_linked_list(&headB);
}

// 1 2 3 2 1
int check_palindrome(SinglyLinkedNode *head) {
    if (head == NULL) return 0;

    SinglyLinkedNode *middle_node = find_middle_node(head);
    reverse(&(middle_node->next));

    SinglyLinkedNode *left = head;
    SinglyLinkedNode *right = middle_node->next;
    while (right->next) {
        if (left->data != right->data) {
            return 0;
        }
        left = left->next;
        right = right->next;
    }
    return 1;
}

void test_palinkdrome() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 2);
    // append_node(&head, 1);

    int is_palindrome = check_palindrome(head);
    printf("is palindrome = %d\n", is_palindrome);

    free_linked_list(&head);
}

int main(void) {
    printf("--- begin ---\n");
    // test_create_print_free();
    // test_insert();
    // test_reverse();
    // test_circle();
    // test_middle_node();
    // test_delete_last_kth();
    // test_merge_sorted_linked_list();
    // test_remove_elements();
    // test_remove_elements_ret();
    // test_rotate();
    // test_get_intersection();
    // test_palinkdrome();
    printf("--- end ---\n");
    return 0;
}