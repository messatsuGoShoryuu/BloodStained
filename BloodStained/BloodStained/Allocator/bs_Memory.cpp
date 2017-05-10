#include "bs_Memory.h"

void* operator new(std::size_t size)
{
	bs::Profiler::addUsedBytes(size);
	bs::Profiler::addAllocatedBytes(size);
	bs::Profiler::addNewCount(1);
	return setHeader(size);
}

void operator delete(void* ptr)
{
	ui32 size = readHeader(ptr);
	bs::Profiler::removeAllocatedBytes(size);
	bs::Profiler::removeUsedBytes(size);
	bs::Profiler::addDeleteCount(1);
}

void* operator new[](std::size_t size)
{
	bs::Profiler::addUsedBytes(size);
	bs::Profiler::addAllocatedBytes(size);
	bs::Profiler::addNewCount(1);
	return setHeader(size);
}

void operator delete[](void* ptr)
{
	ui32 size = readHeader(ptr);
	bs::Profiler::removeAllocatedBytes(size);
	bs::Profiler::removeUsedBytes(size);
	bs::Profiler::addDeleteCount(1);
}



void* setHeader(ui32 size)
{
	ui32* ptr = (ui32*)malloc(sizeof(ui32) + size);
	*ptr = size;
	ptr++;
	return (void*)ptr;
}

ui32 readHeader(void* ptr)
{
	ui32* item = (ui32*)ptr;
	item--;
	ptr = (void*)item;
	ui32 result = *item;
	free(ptr);
	return result;
}