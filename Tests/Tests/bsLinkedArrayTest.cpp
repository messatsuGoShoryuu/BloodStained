#include "controlTests.h"

#ifdef TEST_LINKED_ARRAY

#include <iostream>
#include <Containers\bs_LinkedArray.h>

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

void intPoolTest();
void fooPoolTest();
void fooArrayTest();

int main()
{
	bool quit = false;

	while (!quit)
	{
		std::cout << std::endl;
		std::cout << "Choose Test :" << std::endl;
		std::cout << "1: Int Pool Test" << std::endl;
		std::cout << "2: Foo Pool Test" << std::endl;
		std::cout << "3: Foo Array Test" << std::endl;
		std::cout << "4: Quit" << std::endl;

		ui32 index = 0;
		std::cin >> index;

		switch (index)
		{
			case 1: intPoolTest();
				break;
			case 2: fooPoolTest();
				break;
			case 3: fooArrayTest();
				break;
			case 4:
				quit = true;
				break;
			default: intPoolTest();
		}
	}
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

void intPoolTest()
{
	std::cout << "Integer Pool Test:" << std::endl;
	bs::LinkedArrayPool<int> p;
	p.initialize();

	int* i1 = p.add(5);
	std::cout << "Added new int" << *i1 << std::endl;

	showMemoryStats();

	std::cout << "Remove int" << std::endl;

	p.remove(i1);
	showMemoryStats();

	for (ui32 i = 0; i < 10; i++)
	{
		p.add(i);
	}

	int* ints[10];
	for (ui32 i = 0; i < 10; i++)
	{
		std::cout << "p["<<i<<"] = " << p[i]->item << std::endl;
		ints[i] = &p[i]->item;
	}

	showMemoryStats();

	p.remove(ints[5]);

	for (ui32 i = 0; i < 10; i++)
	{
		std::cout << "p[" << i << "] = " << p[i]->item << std::endl;
	}

	showMemoryStats();

	p.add(521);

	for (ui32 i = 0; i < 10; i++)
	{
		std::cout << "p[" << i << "] = " << p[i]->item << std::endl;
	}

	showMemoryStats();

	p.destroy();
	showMemoryStats();

	system("pause");
}

void printFoo(Foo* f)
{
	std::cout << "x = " << f->x << ", y = " << f->y;
}

void fooPoolTest()
{
	std::cout << "Foo Pool Test:" << std::endl;

	bs::LinkedArrayPool<Foo> p;
	p.initialize();

	Foo* f1 = p.construct(10, 15);

	std::cout << "Added new int: ";
	printFoo(f1);

	std::cout << "Max index = " << p.maxIndex() << " Min index = " << p.minIndex() << std::endl;

	std::cout<<std::endl;

	showMemoryStats();

	for (ui32 i = 0; i < 10; i++)
	{
		p.construct(i, i + 1);
	}

	p.remove(f1);

	for (ui32 i = 0; i < 20; i++)
	{
		if (p[i]->isEmpty) continue;
		std::cout << "Foo[" << i << "] = ";
		printFoo(&p[i]->item);
		std::cout << std::endl;
	}
	std::cout << "Max index = " << p.maxIndex() << " Min index = " << p.minIndex() << std::endl;

	showMemoryStats();

	p.remove(&p[3]->item);

	p.construct(50, 40);

	for (ui32 i = 0; i < 20; i++)
	{
		if (p[i]->isEmpty) continue;
		std::cout << "Foo[" << i << "] = ";
		printFoo(&p[i]->item);
		std::cout << std::endl;
	}
	std::cout << "Max index = " << p.maxIndex() << " Min index = " << p.minIndex() << std::endl;

	showMemoryStats();

	p.destroy();

	showMemoryStats();
	system("pause");
}

void fooArrayTest()
{
	std::cout << "Foo Array Test:" << std::endl;

	showMemoryStats();

	std::cout << "Create linked array" << std::endl;
	bs::LinkedArray<Foo> l(20);

	showMemoryStats();

	for (ui32 i = 0; i < 16; i++)
		l.construct(i, i + 1);

	std::cout << "Sizeof pool = " << sizeof(bs::LinkedArrayPool<Foo>) << std::endl;

	for (ui32 i = 0; i < 16; i++)
	{
		Foo* f = l[i];
		if (f)
			std::cout << "l[" << i << "].x = " << f->x << ", y = " << f->y << std::endl;
	}

	std::cout << "Remove 3" << std::endl;

	l.remove(l[3]);

	for (ui32 i = 0; i < 16; i++)
	{
		Foo* f = l[i];
		if (f)
			std::cout << "l[" << i << "].x = " << f->x << ", y = " << f->y << std::endl;
	}

	showMemoryStats();

	std::cout << "destroy linked array" << std::endl;
	l.destroy();
	showMemoryStats();

	system("pause");
}

#endif // TEST_LINKED_ARRAY
