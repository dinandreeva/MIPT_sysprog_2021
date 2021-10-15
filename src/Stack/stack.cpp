#include <stdio.h>
#include "stack.h"

int main() {
    Stack stk = {nullptr, nullptr};
    StackCtor(&stk, sizeof(int), 10);
    StackPush(&stk, );
    StackDtor(&stk)
    return 0;
}

void StackCtor (Stack* stk, size_t t_size, size_t capacity) {
    stk = (Stack*) calloc (1, sizeof (Stack));
    stk->data = calloc (capacity, sizeof (t_size));
    stk->s_info->s_length = 0;
    stk->s_info->size = sizeof (StackInfo);
    stk->s_info->capacity = capacity;
}

void StackDtor (Stack* stk) {
    stack* cur_stack = NULL;
    while (s_head->prev_data != NULL) {
        cur_stack = s_head->prev_item;
        free (cur_stack);
    }
}


int StackPush(Stack* stk, ) {
    s_head->
}

stack* stackPop(fst)




