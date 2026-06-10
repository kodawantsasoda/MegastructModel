#include "arena.h"

bool isPowerofTwo(uintptr_t x)
{
	return (x & (x - 1)) == 0;
}

uintptr_t alignForward(uintptr_t ptr, size_t align)
{
	uintptr_t p, a, modulo;
	assert(isPowerofTwo(align));

	p = ptr;
	a = (uintptr_t)align;

	//p % a
	modulo = p & (a - 1);

	if (modulo != 0)
	{
		p += a - modulo;
	}
	return p;
}

void arena_init(Arena* arena, void* backingBuffer, size_t backingBufferLength) 
{
	arena->buffer = (unsigned char*)backingBuffer;
	arena->bufferLength = backingBufferLength;
	arena->currentOffset = 0;
	arena->previousOffset = 0;
	arena ->freeList = NULL;
}

void* arenaAlloc(Arena* arena, size_t size)
{
	FreeList* node = arena->freeList;
	while (node)
	{
		if (size <= node->currentOffset + node->size)
		{
			//not sure if it needs to get aligned? if it already got aligned via the first alloc? not sure....
			void* ptr = &arena->buffer[node->currentOffset];
			arena->freeList = node->nextOffset;
			memset(ptr, 0, size);
			return ptr;
		}
		node = node->nextOffset;
	}
	//alignning forward
	uintptr_t currentPointer = (uintptr_t)arena->buffer + (uintptr_t)arena->currentOffset; //this is just arena's address + the number of bytes already used in our arena
	uintptr_t offset = alignForward(currentPointer, DEFAULT_ALIGNMENT); //the address of the current pointer after alignment
	offset -= (uintptr_t)arena->buffer; //number of bytes in our offset to play nicely with our Arena members

	//checking space in backing memory. the offset is a value in address form adding to the size of the requested allocation to make sure we have room in the arena
	if (offset + size < arena->bufferLength) //Bug Alert: the only reason why this is less than and not less than or equal to, because I want my indexes to line up with init-ing with size_t
	{
		void* ptr = &arena->buffer[offset];
		arena->previousOffset = offset;
		arena->currentOffset = offset + size;

		//zero out the new memory
		//memset(ptr, 0, size);
		return ptr;
	}
	//arena is out of memory
	return NULL;
}

void* arenaDealloc(Arena* arena, void* deallocLocation, size_t size)
{
	//zero out the new memory
	//memset(deallocLocation, 0, size); might not need because of the memset in alloc already

	FreeList* deallocNode = NULL;

	//uintptr_t currentPointer = (uintptr_t)arena->buffer + (uintptr_t)arena->currentOffset; //this is just arena's address + the number of bytes already used in our arena
	uintptr_t offset = alignForward((uintptr_t)deallocLocation, DEFAULT_ALIGNMENT); //the address of the current pointer after alignment
	offset -= (uintptr_t)arena->buffer; //number of bytes in our offset to play nicely with our Arena members

	/* gets the index...
	uintptr_t currentPointer = (uintptr_t)deallocLocation - (uintptr_t)arena->buffer; //this is just arena's address + the number of bytes already used in our arena
	uintptr_t offset = alignForward(currentPointer, DEFAULT_ALIGNMENT); //the address of the current pointer after alignment
	offset -= (uintptr_t)arena->buffer; //number of bytes in our offset to play nicely with our Arena members
	*/
	deallocNode = (FreeList*)deallocLocation;
	deallocNode->currentOffset = offset;
	deallocNode->size = size;
	deallocNode->nextOffset = NULL;

	FreeList* node = arena->freeList;
	
	if (!node)
	{
		arena->freeList = deallocNode;
		return deallocLocation;
	}

	while (node->nextOffset)
	{
		node = node->nextOffset;
	}

	node->nextOffset = deallocNode;

	return deallocLocation;
}

void arenaFree(Arena* arena)
{
	arena->currentOffset = 0;
	arena->previousOffset = 0;
}