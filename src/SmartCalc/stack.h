#ifndef SRC_STACK_H_
#define SRC_STACK_H_

struct stack {
    char op;
    double value;
    struct stack *prev;
};

struct stack* init_stack(char op);
struct stack* push(struct stack* elem, char op);
struct stack* pop(struct stack* elem);
void destroy_stack(struct stack* root);
void output_stack(struct stack* head);

#endif  // SRC_STACK_H_
