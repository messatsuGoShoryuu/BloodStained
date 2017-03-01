#include "../Utilities/bs_define.h"

#ifdef BS_TEST_ALLOCATOR

#include <iostream>
#include "../Allocator/bs_PoolAllocator.h"
#include "../Allocator/bs_StackAllocator.h"
#include "../Allocator/bs_Memory.h"


class Foo
{
public:

	Foo() :x(0), y(0)
	{
	}

	Foo(int x, int y) :x(x), y(y)
	{
	}
	int x;
	int y;
};

void simplePoolTest();
void arrayPoolTest(int itemCount);
void simplePoolAllocatorTest();
void arrayPoolAllocatorTest(int itemCount, int poolSize);
void stackAllocatorTest(ui64 stackSize);
void mallocFreeProfilingTest();

int main()
{
	//test pool:

	bool quit = false;

	while (!quit)
	{

		std::cout << "---------------------------------------" << std::endl;
		std::cout << "Choose test :" << std::endl;
		std::cout << std::endl;
		std::cout << "1 : Simple Pool Test" << std::endl;
		std::cout << "2 : Array Pool Test" << std::endl;
		std::cout << "3 : Simple Pool Allocator Test" << std::endl;
		std::cout << "4 : Array Pool Allocator Test" << std::endl;
		std::cout << "5 : Stack Allocator Profiling Test" << std::endl;
		std::cout << "6 : Malloc Free Profiling Test" << std::endl;
		std::cout << "7 : Quit" << std::endl;

		int input = 0;
		std::cin >> input;

		switch (input)
		{
			case 1: simplePoolTest();
				break;
			case 2: arrayPoolTest(16);
				break;
			case 3: simplePoolAllocatorTest();
				break;
			case 4: arrayPoolAllocatorTest(128, 32);
				break;
			case 5: stackAllocatorTest(65536);
				break;
			case 6: mallocFreeProfilingTest();
				break;
			case 7: quit = true;
				std::cout << "Quitting" << std::endl;
				break;
			default: simplePoolTest();
				break;
		}
		if(!quit)system("Pause");
	}

	return 0;
}

void showMemoryStats()
{
	std::cout << std::endl;
	std::cout << "Memory Stats:" << std::endl;
	std::cout << "Allocated Memory : " << bs::Profiler::getAllocatedBytes() << " bytes." << std::endl;
	std::cout << "Used Memory : " << bs::Profiler::getUsedBytes() << " bytes." << std::endl;
	std::cout << "Unused Memory: " << bs::Profiler::getUnusedBytes() << " bytes." << std::endl;
	std::cout << std::endl;
}

void simplePoolTest()
{
	std::cout << "Simple Pool Test :" << std::endl;

	showMemoryStats();

	bs::Pool* pool = new bs::Pool(512, sizeof(Foo), __alignof(Foo));

	pool->initialize();

	Foo* f = new(pool->allocate()) Foo(5, 4);
	Foo* g = new(pool->allocate()) Foo(6, 7);

	std::cout << "Foo* f = new(pool->allocate()) Foo(5,4);" << std::endl;
	std::cout << "f->x = " << f->x << std::endl;
	std::cout << "f->y = " << f->y << std::endl;

	std::cout << "Foo* g = new(pool->allocate()) Foo(6,7);" << std::endl;
	std::cout << "g->x = " << g->x << std::endl;
	std::cout << "g->y = " << g->y << std::endl;

	std::cout << "pool->deallocate(f)" << std::endl;
	pool->deallocate(f);
	std::cout << "f == nullptr : " << (f == nullptr) << std::endl;


	std::cout << "f->x = " << f->x << std::endl;
	std::cout << "f->y = " << f->y << std::endl;

	pool->shutDown();

	delete pool;

	showMemoryStats();
}

void displayFooArray(Foo** f, ui32 first, ui32 count)
{
	for (ui32 i = first; i < count; i++)
	{
		std::cout << "Foo[" << i << "].x = " << f[i]->x << ", Foo[" << i << "].y = " << f[i]->y << std::endl;
	}
}

void arrayPoolTest(int itemCount)
{
	std::cout << "Array Pool Test :" << std::endl;

	bs::Pool* pool = new bs::Pool(itemCount, sizeof(Foo), __alignof(Foo));
	Foo** f = new Foo*[itemCount];

	pool->initialize();

	for (ui32 i = 0; i < itemCount; i++)
	{
		f[i] = new(pool->allocate()) Foo(i, i + 1);
	}

	std::cout << "After first allocation :" << std::endl;
	displayFooArray(f, 0, itemCount);

	for (ui32 i = 0; i < 5; i++)
	{
		pool->deallocate(f[i]);
	}

	std::cout << std::endl;
	std::cout << "After deallocation :" << std::endl;
	displayFooArray(f,5,itemCount);

	for (ui32 i = 0; i < 5; i++)
	{
		f[i] = new(pool->allocate()) Foo(i, i + 5);
	}

	std::cout << std::endl;
	std::cout << "After second allocation :" << std::endl;
	displayFooArray(f, 0, itemCount);

	for (ui32 i = 5; i < itemCount; i++)
	{
		pool->deallocate(f[i]);
	}

	std::cout << std::endl;
	std::cout << "After second deallocation" << std::endl;
	displayFooArray(f, 0, 5);

	for (ui32 i = 0; i < 5; i++)
	{
		pool->deallocate(f[i]);
	}

	for (ui32 i = 0; i < itemCount; i++)
	{
		f[i] = new(pool->allocate()) Foo(i, itemCount - i);
	}

	std::cout << std::endl;
	std::cout << "after complete deallocation - reallocation" << std::endl;
	displayFooArray(f, 0, itemCount);

	pool->shutDown();

	delete(pool);
	delete[] f;

	showMemoryStats();
}

void simplePoolAllocatorTest()
{
	std::cout << "Simple Pool Allocator Test" << std::endl;

	showMemoryStats();

	bs::PoolAllocator<Foo>* p = new bs::PoolAllocator<Foo>(32);

	Foo* f = p->allocate(4, 5);

	std::cout << "Foo* f = p->allocate(4, 5);" << std::endl;
	std::cout << "f->x = " << f->x << " f->y = " << f->y << std::endl;

	p->deallocate(f);

	std::cout << "p->deallocate(f);" << std::endl;
	std::cout << "f->x = " << f->x << " f->y = " << f->y << std::endl;

	p->shutDown();
	delete p;

	showMemoryStats();
}

void arrayPoolAllocatorTest(int itemCount, int poolSize)
{
	std::cout << "Array Pool Allocator Test" << std::endl;


	showMemoryStats();

	bs::PoolAllocator<Foo>* p = new bs::PoolAllocator<Foo>(poolSize);
	Foo** f = new Foo*[itemCount];

	for (ui32 i = 0; i < itemCount; i++)
	{
		f[i] = p->allocate(i, i + 1);
	}
	

	std::cout << "After first allocation :" << std::endl;
	showMemoryStats();
	displayFooArray(f, 0, itemCount);

	for (ui32 i = 0; i < itemCount - 5; i++)
	{
		p->deallocate(f[i]);
	}

	std::cout << std::endl;
	std::cout << "After deallocation :" << std::endl;
	showMemoryStats();
	displayFooArray(f, itemCount-5, itemCount);

	for (ui32 i = 0; i < itemCount-5; i++)
	{
		f[i] = p->allocate(i, i + 5);
	}

	std::cout << std::endl;
	std::cout << "After second allocation :" << std::endl;
	showMemoryStats();
	displayFooArray(f, 0, itemCount);

	for(ui32 i = itemCount - 5; i < itemCount; i++)
	{
		p->deallocate(f[i]);
	}

	std::cout << std::endl;
	std::cout << "After second deallocation" << std::endl;
	showMemoryStats();
	displayFooArray(f, 0, itemCount - 5);

	for (ui32 i = 0; i < itemCount - 5; i++)
	{
		p->deallocate(f[i]);
	}

	for (ui32 i = 0; i < itemCount; i++)
	{
		f[i] = p->allocate(i, itemCount - i);
	}

	std::cout << std::endl;
	std::cout << "after complete deallocation - reallocation" << std::endl;
	showMemoryStats();
	displayFooArray(f, 0, itemCount);

	for (ui32 i = 0; i < itemCount; i++)
	{
		p->deallocate(f[i]);
	}
	std::cout << std::endl;
	std::cout << "After complete deallocation" << std::endl;
	showMemoryStats();
	p->shutDown();

	std::cout << std::endl;
	std::cout << "After poolAllocator shuts down" << std::endl;
	delete[] f;
	delete p;

	showMemoryStats();

}

void stackAllocatorTest(ui64 stackSize)
{
	std::cout << "Stack Allocator Test" << std::endl;
	std::cout << "For each allocation bs::StackAllocator \nallocates an extra 4 bytes to store frame location\n" << std::endl;

	bs::StackAllocator s(stackSize);
	s.initialize();
	void* frame0 = s.getFrame();

	Foo* f = new(s.allocate(sizeof(Foo), __alignof(Foo))) Foo(10, 11);
	void* frame1 = s.getFrame();

	ui32 arrayCount = 5;
	int* i = (int*)s.allocate(sizeof(int) * arrayCount, __alignof(int));

	std::cout << "Allocated foo and int[5] array" << std::endl;
	showMemoryStats();

	const char* correctFrame0 = (frame1 == s.deallocate()) ? "True" : "False";
	std::cout << " Deallocate once" << std::endl;
	std::cout << "Are we at the correct frame ? " << correctFrame0 << std::endl;

	showMemoryStats();


	const char* correctFrame1 = (frame0 == s.deallocate()) ? "True" : "False";
	std::cout << " Deallocate twice" << std::endl;
	std::cout << "Are we at the correct frame ? " << correctFrame1 << std::endl;

	showMemoryStats();

	std::cout << "Shut down" << std::endl;

	s.shutDown();

	showMemoryStats();
}

void mallocFreeProfilingTest()
{
	std::cout << "Profile New:" << std::endl;

	std::cout << "\n Foo* f = new Foo(5,6);" << std::endl;
	Foo* f = new Foo(5, 6);

	showMemoryStats();

	std::cout << "delete f;" << std::endl;

	delete f;

	showMemoryStats();

	std::cout << "Foo* f = new Foo[10];" << std::endl;
	f = new Foo[10];

	showMemoryStats();

	std::cout << "delete[] f;" << std::endl;
	delete[] f;

	showMemoryStats();


	std::cout << "Profile Malloc:" << std::endl;

	int* ints = (int*)Malloc(sizeof(int) * 10);

	std::cout << "int* ints = (int*)Malloc(sizeof(int) * 10);" <<std::endl;

	showMemoryStats();

	std::cout << "Free(ints,sizeof(int) * 10);" << std::endl;

	Free(ints);

	showMemoryStats();
}

#endif