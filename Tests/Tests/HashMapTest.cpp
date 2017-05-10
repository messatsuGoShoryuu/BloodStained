#include "controlTests.h"

#ifdef HASHMAP_TEST

#include <Containers\bs_HashMap.h>
#include <iostream>
#include <Profiler\bs_Profiler.h>
#include <Utilities\bs_String.h>

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


void testString();
void showMemoryStats();
void testInt();
void testStringFoo();
int main()
{
	testStringFoo();
	system("pause");
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

void testInt()
{
	bs::HashMap<int, int> map;
	showMemoryStats();

	map[3] = 123;

	std::cout << "Map[" << 3 << "] = " << map[3] << std::endl;

	showMemoryStats();

	map.reset();
	std::cout << "reset map" << std::endl;
	showMemoryStats();

	for (ui32 j = 5; j < 50; j++)
	{
		for (ui32 i = 0; i < j; i++) map[i] = j - i;
		for (ui32 i = 0; i < j; i++) std::cout << "Map[" << i << "] = " << map[i] << std::endl;
		map.reset();
		std::cout << std::endl;
	}

	for (ui32 i = 0; i < 50; i++) map[i] = 50 - i;

	map.remove(40);

	for (ui32 i = 0; i < 50; i++)
	{
		if (!map.isEmptyAt(i)) std::cout << "Map[" << i << "] = " << map[i] << std::endl;
		else std::cout << "Is empty at " << i << std::endl;
	}

	map[40] = 100;

	for (ui32 i = 0; i < 50; i++)
	{
		if (!map.isEmptyAt(i)) std::cout << "Map[" << i << "] = " << map[i] << std::endl;
		else std::cout << "Is empty at " << i << std::endl;
	}

}

void testString()
{

	bs::HashMap<bs::String, int> map;
	map[L"AHAH"] = 2;
	map[L"ahah"] = 5;
	map[L"ahmetabieee"] = 10;
	map[L"cimipeyc"] = 50;
	map[L"mayk�lceks�n"] = 60;
	map[L"h�sn��enlendirici"] = 70;
	map[L"h�sn�bey"] = 80;
	map[L"hamdibey"] = 90;

	showMemoryStats();

	std::cout << "map[AHAH] = " << map[L"AHAH"] << std::endl;
	std::cout << "map[ahah] = " << map[L"ahah"] << std::endl;
	std::cout << "map[ahmetabieee] = " << map[L"ahmetabieee"] << std::endl;
	std::cout << "map[cimipeyc] = " << map[L"cimipeyc"] << std::endl;
	std::cout << "map[mayk�lceks�n] = " << map[L"mayk�lceks�n"] << std::endl;
	std::cout << "map[h�sn��enlendirici] = " << map[L"h�sn��enlendirici"] << std::endl;
	std::cout << "map[h�sn�bey] = " << map[L"h�sn�bey"] << std::endl;
	std::cout << "map[hamdibey] = " << map[L"hamdibey"] << std::endl;

	showMemoryStats();
	map.reset();

	showMemoryStats();
}

void testStringFoo()
{
	bs::HashMap<bs::String, Foo> map;
	map[L"AHAH"] = Foo(5,10);
	map[L"ahah"] = Foo(10,20);
	map[L"ahmetabieee"] = Foo(129412, 1249124);
	map[L"cimipeyc"] = Foo(1234, 5421);
	map[L"mayk�lceks�n"] = Foo(150050, 1);
	map[L"h�sn��enlendirici"] = Foo(0, 1);
	map[L"h�sn�bey"] = Foo(6, 7);
	map[L"hamdibey"] = Foo(7, 8);

	showMemoryStats();

	std::cout << "map[AHAH] x = " << map[L"AHAH"].x << std::endl;
	std::cout << "map[ahah] x = " << map[L"ahah"].x << std::endl;
	std::cout << "map[ahmetabieee] x = " << map[L"ahmetabieee"].x << std::endl;
	std::cout << "map[cimipeyc] x = " << map[L"cimipeyc"].x << std::endl;
	std::cout << "map[mayk�lceks�n] x = " << map[L"mayk�lceks�n"].x << std::endl;
	std::cout << "map[h�sn��enlendirici] = " << map[L"h�sn��enlendirici"].x << std::endl;
	std::cout << "map[h�sn�bey] x = " << map[L"h�sn�bey"].x << std::endl;
	std::cout << "map[hamdibey] x = " << map[L"hamdibey"].x << std::endl;

	showMemoryStats();
	map.reset();

	showMemoryStats();
}

#endif