#include <stdlib.h>
#include <stdio.h>

typedef struct Block { // a block is the header that contains the size of the memory, and it points to other blocks in linked list
    size_t size; // - 8
    int free; // free bool - 4
    struct Block *next; // pointer to next block - 8 bytes on x64
} Block;

#define POOL_SIZE (1024 * 1024)  // 1 MB
char __attribute__((aligned(16))) memory_pool[POOL_SIZE];
Block *free_list = (Block*)memory_pool;

void init_pool() { // temp func?
    free_list->size = POOL_SIZE - sizeof(Block);
    free_list->free = 1;
    free_list->next = NULL;
}

void* my_malloc(size_t size) {
    Block*curr = free_list; // current block is free
    while (curr) { // while searching through free list
        if (curr -> free && curr->size >= size) {
            // split block if too large

            if (curr-> size > size + sizeof(Block)) {
                // new block is the size of the block + header-space of 32 bytes
                Block *new_block = (Block*)((char*)curr + sizeof(Block) + size);
                // size of newblock (newblock.size) is oldblock.size - mallocsize - header
                // the newblock is obviously leftover
                // free space and the other space will be taken by malloc
                new_block -> size = curr -> size - size - sizeof(Block);
                new_block-> free = 1; // mark new block as free, see above
                new_block -> next = curr -> next; // updates linked list of last block
                curr -> next = new_block; // updates
                curr->size = size;
            }
            curr-> free = 0; // no longer free memory, allocated
            return (char*)curr + sizeof(Block); // change size of next block
        }
        curr = curr -> next; // move pointer
    }
    return NULL; // OOM
}

void my_free(void* ptr) {
    if (!ptr) return; //return if completely free

    Block *block = (Block*)((char*)ptr - sizeof(Block));
    block -> free = 1;

    // coalesce adjacent free blocks
    Block *curr = free_list;
    while (curr) {
        if (curr->free && curr->next && curr->next->free) {
            curr ->size += sizeof(Block) + curr->next->size;
            curr->next = curr->next->next;
        } else
            curr = curr-> next;
    }
}


int main() { //test, allocates no 1 to 10 using methods before freeing memory
    init_pool();
    int *arr = (int*)my_malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++)
        arr[i] = i;

    for (int i = 0; i < 10; i++) //increment i until 10
        printf("%d ", arr[i]);
    printf("\n");


    //my_free(arr);
    return 0;
}