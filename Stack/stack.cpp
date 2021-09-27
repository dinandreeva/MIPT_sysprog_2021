#include <stdio.h>

int main() {

}


typedef struct StackInfo {
    Stack* stack;
    int s_length;
}

typedef struct Stack {
    void* data[];
    void* prev_data;
    struct* StackInfo s_info;
}

int StackConstructor () {
    Stack* new_s_pointer = calloc (1, sizeof(void*));
    *new_s_pointer = {NULL, NULL, {new_s_pointer, 1}};
}

int StackDestructor (Stack* s_head) {
    Stack* cur_stack = NULL;
    while (s_head->prev_data != NULL) {
        cur_stack = s_head->prev_item;
        free(cur_stack);
    }
}


int StackPush(Stack* s_head, int* item[]) {
    s_head->
}

Stack* StackPop(fst)




