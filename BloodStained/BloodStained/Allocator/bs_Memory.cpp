#include "bs_Memory.h"


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