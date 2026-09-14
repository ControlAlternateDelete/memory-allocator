# Memory Allocator (C)

A basic custom memory allocator implementing `malloc`/`free`-style dynamic memory management, using a linked-list-based free list to track and reuse memory blocks.

This project was built to understand how allocators actually work under the hood — block headers, free-list traversal, splitting, and coalescing — rather than to be a production-ready implementation.

## Features

- Custom `my_malloc` / `my_free` functions
- Linked-list free list for tracking available memory blocks
- Block splitting and reuse of freed memory
- Coalescing of adjacent free blocks

## How it works

Rather than requesting memory from the OS via `sbrk`/`mmap`, this allocator manages a fixed pool of memory and hands out chunks from it, using a linked list to track which blocks are free.

Each allocated block currently has a 32-byte header storing block size, a pointer to the next free block, and an allocation flag. This is larger than it needs to be - a known area for improvement (see below).

## Building & Running

This project uses CMake.

```bash
mkdir build && cd build
cmake ..
cmake --build .
./untitled
```

## Example usage

```c
void *ptr = my_malloc(64);
my_free(ptr);
```

## What I learned / Challenges

A segfault that occurred because I had forgotten to initialise the memory pool defined at the beginning caused me to independently trace through the workings of the entire program, as I was under the impression that it was my malloc function.  

## Known limitations / future improvements

- Header size (32 bytes) could be reduced — currently oversized relative to what it needs to store
- No use of `sbrk`/`mmap` yet to request memory dynamically from the OS

## Acknowledgments

Based on a tutorial approach to memory allocator design, extended and debugged independently. 
https://dev.to/farhadrahimiklie/how-i-built-malloc-and-free-in-c-from-scratch-3had

This is a line-by-line tutorial, though I still learnt a lot through implementation.

## License
No license yet, feel free to reference for learning purposes. Not entirely my work (see above).
