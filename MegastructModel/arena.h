#pragma once
//#include <stddef.h>
//#include <stdint.h>
//#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif


typedef struct Arena
{
	unsigned char* buffer; //byte buffer
	size_t bufferLength; //byte length
	size_t previousOffset; //previous bytes we had running through the arena before the recent allocation
	size_t currentOffset; //how many bytes we have run through in the arena
} Arena;

uintptr_t alignForward(uintptr_t ptr, size_t align);
uintptr_t alignForward(uintptr_t ptr, size_t align);
void arena_init(Arena* arena, void* backingBuffer, size_t backingBufferLength);
void* arenaAlloc(Arena* arena, size_t size);
void* arenaGetBlock(Arena* arena, size_t size, void* ptr);
void arenaFree(Arena* arena);
