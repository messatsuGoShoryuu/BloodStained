#include "controlTests.h"

#ifdef TEST_STRING

#include <iostream>
#include <Utilities/bs_String.h>

typedef unsigned int ui32;

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

void stringTest();


int main()
{
	bool quit = false;

	while (!quit)
	{
		std::cout << std::endl;
		std::cout << "Choose Test :" << std::endl;
		std::cout << "1: String Test" << std::endl;
		std::cout << "4: Quit" << std::endl;

		ui32 index = 0;
		std::cin >> index;

		switch (index)
		{
			case 1: stringTest();
				break;
			case 4:
				quit = true;
				break;
			default: stringTest();
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

void stringTest()
{
	std::cout << "String test : " << std::endl;
	bs::String s("DENEME 1");
	std::cout << s.utf8() << std::endl;
	showMemoryStats();

	std::cout << "Clear From Memory" << std::endl;

	s.clearFromMemory();
	showMemoryStats();

	bs::String s2(L"ÞAÞA");

	 s = L"ÞAÞA";

	std::cout << "s = " << s.utf8() << " s2 = " << s2.utf8() << " s == s2 : " << (s == s2) << std::endl;

	std::cout << s2.utf8() << std::endl;
	showMemoryStats();

	std::cout << "s1 + s2 = " << (s + s2).utf8() << std::endl;

	showMemoryStats();

	s += 3.0f;

	std::cout << s.utf8()<<std::endl;

	showMemoryStats();

	bs::String s1 = bs::String("S1 = ") + s + s2;
	std::cout << s1.utf8() << std::endl;

	showMemoryStats();

	

	std::cout << "Clear all strings" << std::endl;
	s.clearFromMemory();
	s1.clearFromMemory();
	s2.clearFromMemory();

	s = BS_UNDECORATED_FUNCTION;
	std::cout << s.utf8() << std::endl;

	showMemoryStats();
}

#endif // TEST_LINKED_ARRAY

