typedef struct {
    Stack* stack;
    int s_length;
    size_t t_size
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
