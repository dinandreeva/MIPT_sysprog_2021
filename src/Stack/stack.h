typedef struct {
    int s_length;
    size_t t_size;
    size_t capacity;
    size_t size;
} StackInfo;

typedef struct {
    StackInfo* s_info;
    void* data;
} Stack;

typedef enum {
    LOTOFMEM = 4096
} MEMORY_AM;



void StackCtor (Stack* stk, size_t t_size, size_t capacity);


void StackDtor (Stack* stk);

void StackPush(Stack* stk, size_t t_elem, void* elem);
