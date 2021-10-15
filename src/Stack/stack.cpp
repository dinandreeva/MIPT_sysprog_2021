#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

int main() {
    Stack stk = {nullptr, nullptr};
    printf("Without t_size %ld\n", sizeof(int) + 3 * sizeof(size_t));
    printf("With t_size %ld\n", (size_t) (sizeof(int) + 3 * sizeof(size_t)));
    StackCtor(&stk, sizeof(int), 10);

    // int* num_data = (int *) calloc (1, sizeof(int));
    // assert(num_data != nullptr);
    // *num_data = 5;

    // StackPush(&stk, sizeof(int), (void*) num_data);
    // StackDtor(&stk)
    // free(num_data);
    return 0;
}

void StackCtor (Stack* stk, size_t t_size, size_t n) {
    size_t s_size = sizeof(int) + 3 * sizeof(size_t);

    stk->s_info = (StackInfo*) calloc (1, s_size + n * t_size);
    stk->data = (void *) (stk->s_info + s_size + 1);
    stk->s_info->s_length = 0;
    stk->s_info->size = s_size;
    stk->s_info->capacity = n * t_size;

    // Debug info
    printf("Data address: %p\n", (void *) ((size_t) stk->s_info + stk->s_info->size));
    printf("Where is Stack Info: %p\n", (void *) ((size_t) stk->s_info));
    printf("Where is data: %p\n", stk->data);
    printf("Size of Stack Info in bytes: %ld\n", s_size);
    printf("Size of Stack Info calculated: %ld\n", (size_t) stk->data - (size_t) stk->s_info);
}

// void StackDtor (Stack* s_head) {
    // stack* cur_stack = NULL;
    // while (s_head->prev_data != NULL) {
        // cur_stack = s_head->prev_item;
        // free (cur_stack);
    // }
// }

void StackPush(Stack* s_head, size_t t_elem, void* elem) {
    printf("Where to insert: %ld", (size_t) s_head + s_head->s_info->size);
}
