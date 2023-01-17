#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "polish.h"

struct stack* init_stack(char op) {
    struct stack *first;
    first = (struct stack*)malloc(sizeof(struct stack));
    first->op = op;
    first->prev = NULL;
    return first;
}

struct stack* push(struct stack* head, char op) {
    int flag = 0;
    struct stack *temp = NULL;
    if (head == NULL) {
        flag = 1;
    } else {
        temp = (struct stack*)malloc(sizeof(struct stack));
        temp->prev = head;
        temp->op = op;
    }
    return flag ? init_stack(op) : temp;
}

struct stack* pop(struct stack* head) {
    int flag = 0;
    struct stack *temp;
    if (head == NULL) {
        flag = 1;
    } else {
        temp = head->prev;
        free(head);
    }
    return flag ? NULL : temp;
}

void destroy_stack(struct stack* head) {
    if (head != NULL) {
        struct stack *curr, *prev;
        curr = head;
        do {
            prev = curr->prev;
            free(curr);
            curr = prev;
        } while (curr != NULL);
    }
}

void output_stack(struct stack* head) {
    struct stack *curr;
    curr = head;
    do {
        printf("%c", curr->op);
        printf(" ");
        curr = curr->prev;
    } while (curr != NULL);
}
