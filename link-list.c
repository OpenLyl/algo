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

// 16. find circle first node
// 17. reverse between
// 18. sort linked list
// 19. remove duplicated elements (1, 2)
// 20. copy random linked list

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

SinglyLinkedNode *find_circle_first_node(SinglyLinkedNode *head) {
    SinglyLinkedNode *slow, *fast;
    slow = fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return NULL;
}

void test_find_circle_first_node() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);
    
    head->next->next->next->next = head->next;

    SinglyLinkedNode *first_node = find_circle_first_node(head);
    if (first_node) {
        printf("first node = %d\n", first_node->data);
    }

    free_linked_list(&head);
}

SinglyLinkedNode *reverse_between(SinglyLinkedNode *head, int left, int right) {
    SinglyLinkedNode dummy;
    dummy.next = head;
    
    // 1. find left node
    SinglyLinkedNode *prev_node = &dummy;
    SinglyLinkedNode *current = head;
    for (int i = 1; i < left; i++) {
        prev_node = current;
        current = current->next;
    }

    // 2. reverse
    for (int i = 0; i < right - left; i++) {
        SinglyLinkedNode *next_node = current->next;
        current->next = next_node->next;
        next_node->next = prev_node->next;
        prev_node->next = next_node;
    }
    return dummy.next;
}

void test_reverse_between() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);

    // SinglyLinkedNode *reversed_head = reverse_between(head, 2, 4);
    SinglyLinkedNode *reversed_head = reverse_between(head, 1, 4);
    if (reversed_head) {
        print_linked_list(reversed_head);
    }

    free_linked_list(&reversed_head);
}

SinglyLinkedNode *sort_linked_list(SinglyLinkedNode *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 1. find midle node
    SinglyLinkedNode *middle_node = find_middle_node(head);
    if (middle_node == NULL) {
        return NULL;
    }

    // 2. split left right
    SinglyLinkedNode *left = head;
    SinglyLinkedNode *right = middle_node->next;
    middle_node->next = NULL;

    // 3. sort left right
    SinglyLinkedNode *sorted_left = sort_linked_list(left);
    SinglyLinkedNode *sorted_right = sort_linked_list(right);

    // 4. merge linked list
    return merge_sorted_linked_list(sorted_left, sorted_right);
}

void test_sort_linked_list() {
    SinglyLinkedNode *head = NULL;
    append_node(&head, 7);
    append_node(&head, 10);
    append_node(&head, 6);
    append_node(&head, 4);
    append_node(&head, 8);
    append_node(&head, 12);

    SinglyLinkedNode *sorted_head = sort_linked_list(head);
    if (sorted_head) {
        print_linked_list(sorted_head);
    }

    free_linked_list(&sorted_head);
}

SinglyLinkedNode *remove_duplicated_elements(SinglyLinkedNode *head) {
    SinglyLinkedNode dummy;
    dummy.next = head;

    SinglyLinkedNode *left = &dummy;
    while (left->next) {
        SinglyLinkedNode *right = left->next;
        while (right->next && right->data == right->next->data) {
            right = right->next;
        }
        if (left->next == right) {
            left = left->next;    
        } else {
            left->next = right->next;
        }
    }
    
    return dummy.next;
}

void test_remove_duplicated_elements() {
    SinglyLinkedNode *head = NULL;
    // append_node(&head, 1);
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 4);
    append_node(&head, 5);

    SinglyLinkedNode *removed_head = remove_duplicated_elements(head);
    if (removed_head) {
        print_linked_list(removed_head);
    }

    free_linked_list(&removed_head);
}

SinglyLinkedNode *remove_duplicated_keep_elements(SinglyLinkedNode *head) {
    SinglyLinkedNode dummy;
    dummy.next = head;

    SinglyLinkedNode *left = &dummy;
    while (left->next) {
        SinglyLinkedNode *right = left->next;
        while (right->next && right->data == right->next->data) {
            right = right->next;
        }
        left->next = right;
        left = left->next;
    }
    
    return dummy.next;
}

void test_remove_duplicated_keep_elements() {
    SinglyLinkedNode *head = NULL;
    // append_node(&head, 1);
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 4);
    append_node(&head, 5);

    SinglyLinkedNode *removed_head = remove_duplicated_keep_elements(head);
    if (removed_head) {
        print_linked_list(removed_head);
    }

    free_linked_list(&removed_head);
}

typedef struct ListNode {
    int data;
    struct ListNode *next;
    struct ListNode *random;
} ListNode;

ListNode *copy_random_linked_list(ListNode *head) {
    // 1. get len
    int len = 0;
    ListNode *current = head;
    while (current) {
        current = current->next;
        len++;
    }

    // 2. old_nodes[index] = node | new_nodes[index] = new_node
    ListNode *old_nodes[len];
    ListNode *new_nodes[len];
    current = head;
    int index = 0;
    while (current) {
        old_nodes[index] = current;

        ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
        new_node->data = current->data;
        new_node->next = NULL;
        new_node->random = NULL;
        new_nodes[index] = new_node;
        
        current = current->next;
        index++;
    }

    // 3. link the node
    current = head;
    index = 0;
    while (current) {
        if (current->next) {
            int next_index = 0;
            while (old_nodes[next_index] != current->next) {
                next_index++;
            }
            new_nodes[index]->next = new_nodes[next_index];
        }
        
        if (current->random) {
            int random_index = 0;
            while (old_nodes[random_index] != current->random) {
                random_index++;
            }
            new_nodes[index]->random = new_nodes[random_index];
        }

        current = current->next;
        index++;
    }

    return new_nodes[0];
}

void test_copy_random_linked_list() {
    ListNode *node1 = (ListNode *)malloc(sizeof(ListNode));
    node1->data = 1;

    ListNode *node2 = (ListNode *)malloc(sizeof(ListNode));
    node2->data = 2;

    ListNode *node3 = (ListNode *)malloc(sizeof(ListNode));
    node3->data = 3;

    ListNode *node4 = (ListNode *)malloc(sizeof(ListNode));
    node4->data = 4;

    ListNode *node5 = (ListNode *)malloc(sizeof(ListNode));
    node5->data = 5;

    node1->next = node2;
    node1->random = node5;

    node2->next = node3;
    node2->random = node4;

    node3->next = node4;
    node3->random = node1;

    node4->next = node5;
    node4->random = node2;
    
    node5->next = NULL;
    node5->random = node3;

    ListNode *current = node1;
    while (current) {
        printf("current = %d, random = %d\n", current->data, current->random->data);
        current = current->next;
    }

    ListNode *copyed_head = copy_random_linked_list(node1);
    if (copyed_head) {
        printf("---\n");
        ListNode *current = copyed_head;
        while (current) {
            printf("current = %d, random = %d\n", current->data, current->random->data);
            current = current->next;
        }
    }
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
    // test_find_circle_first_node();
    // test_reverse_between();
    // test_sort_linked_list();
    // test_remove_duplicated_elements();
    // test_remove_duplicated_keep_elements();
    test_copy_random_linked_list();
    printf("--- end ---\n");
    return 0;
}