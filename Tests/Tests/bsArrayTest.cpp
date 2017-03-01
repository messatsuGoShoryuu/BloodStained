
#include "controlTests.h"


#ifdef TEST_ARRAY

#include <iostream>
#include <Containers/bs_Array.h>
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

void intArrayTest();
void fooArrayTest();
void fooArrayOfArrayTest();

int main()
{
	bool quit = false;

	while (!quit)
	{
		std::cout << std::endl;
		std::cout << "Choose Test :" << std::endl;
		std::cout << "1: Int Array Test" << std::endl;
		std::cout << "2: Foo Array Test" << std::endl;
		std::cout << "3: Foo Array Of Array Test" << std::endl;
		std::cout << "4: Quit" << std::endl;

		ui32 index = 0;
		std::cin >> index;

		switch (index)
		{
			case 1: intArrayTest();
				break;
			case 2: fooArrayTest();
				break;
			case 3: fooArrayOfArrayTest();
				break;
			case 4:
				quit = true;
				break;
			default: intArrayTest();
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

template<class T>
void showArray(const bs::Array<T>& a)
{
	std::cout << std::endl;
	for (ui32 i = 0; i < a.count(); i++)
	{
		std::cout << "Array[" << i << "] = " << a[i] << std::endl;
	}
	std::cout << std::endl;
}

void showFooArray(const bs::Array<Foo>& a)
{
	std::cout << std::endl;
	for (ui32 i = 0; i < a.count(); i++)
	{
		std::cout << "Array[" << i << "].x = " << a[i].x <<", y = " << a[i].y << std::endl;
	}
	std::cout << std::endl;
}

void showArrayOfArrayFoo(const bs::Array<bs::Array<Foo>>& a)
{
	std::cout << std::endl;
	
	for (ui32 i = 0; i < a.count(); i++)
	{
		for (ui32 j = 0; j < a[i].count();j++)
			std::cout << "Array[" << i << "]["<<j<<"].x = " << a[i][j].x << ", y = " << a[i][j].y << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void intArrayTest()
{
	std::cout << "Int Array Test" << std::endl;
	bs::Array<int> a;

	showMemoryStats();

	for (int i = 0; i < 120; i++)
	{
		a.add(i);
	}

	showArray(a);

	showMemoryStats();


	for (int i = 0; i < 120; i++)
	{
		a.pop();
	}

	showArray(a);
	showMemoryStats();

	for (int i = 0; i < 120000; i++)
	{
		a.add(i);
	}
	
	showArray(a);
	showMemoryStats();

	std::cout << "Reset array" << std::endl;
	a.reset();
	showMemoryStats();
	system("Pause");
}

void fooArrayTest()
{
	std::cout << "Foo Array Test" << std::endl;
	bs::Array<Foo> a;

	showMemoryStats();

	std::cout << "Add " << std::endl;
	for (int i = 0; i < 5; i++)
	{
		a.add(Foo(i,i+1));
	}

	showFooArray(a);

	std::cout << "Construct " << std::endl;
	for (int i = 0; i < 5; i++)
	{
		a.construct(4-i,i);
	}

	showFooArray(a);
	showMemoryStats();


	for (int i = 0; i < 10; i++)
	{
		a.pop();
	}

	showFooArray(a);
	showMemoryStats();

	std::cout << "Reset array, count = " << a.count() << std::endl;
	a.reset();
	showMemoryStats();


	std::cout << "reConstruct " << std::endl;
	for (int i = 0; i < 10; i++)
	{
		a.construct(4 - i, i);
	}

	showFooArray(a);
	showMemoryStats();

	std::cout << "Reset full array, count = " << a.count() << std::endl;

	a.reset();

	showFooArray(a);
	showMemoryStats();

	system("Pause");
}

void fooArrayOfArrayTest()
{
	std::cout << "Foo Array Of Array Test" << std::endl;

	bs::Array<bs::Array<Foo>> a;

	std::cout << "Construct" << std::endl;

	
	for (ui32 i = 0; i < 10; i++)
	{
		a.construct();
		for (ui32 j = 0; j < 10; j++)
		{
			a[i].construct(i, j);
		}
	}

	showArrayOfArrayFoo(a);
	showMemoryStats();

	std::cout << "Reset, count = " << a.count() << ", buffer size = "<<a.bufferSize() << std::endl;
	a.reset();

	showArrayOfArrayFoo(a);
	showMemoryStats();

	std::cout << "Construct j, i" << std::endl;
	for (ui32 i = 0; i < 10; i++)
	{
		a.construct();
		for (ui32 j = 0; j < 10; j++)
		{
			a[i].construct(j, i);
		}
	}

	showMemoryStats();

	std::cout << "Swap and remove 3" << std::endl;

	a.swapAndRemove(3);
	
	showArrayOfArrayFoo(a);
	showMemoryStats();

	std::cout << "Clear" << std::endl;
	a.clear();

	showArrayOfArrayFoo(a);
	showMemoryStats();
}



#endif