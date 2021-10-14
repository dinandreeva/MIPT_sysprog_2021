typedef struct stack_info {
    stack* stack;
    int s_length;
}

typedef struct stack {
    void* data[];
    struct* stack_info s_info;
}
