#include "controlTests.h"

#ifdef RESOURCE_TEST

#include <Resources\bs_Resource.h>
#include <Resources\bs_Path.h>
#include <Resources\bs_FileSystem.h>
#include <Globals\bs_globals.h>
#include <Profiler\bs_Profiler.h>
namespace bs
{
	class ResourceTester
	{
	public:
		void setFileName(Resource* resource, const char* fileName)
		{
			resource->_setFileName(fileName);
		}
	};
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

void textLoadTest();
void directoryScanTest();

int main()
{
	showMemoryStats();
	directoryScanTest();

	showMemoryStats();
	system("pause");
	
	return 0;
}

void textLoadTest()
{
	bs::Path path = bs::Path::data();

	path.toFileName("Text.txt");
	std::cout << "Path = " << path.utf8() << std::endl;

	bs::ResourceTester rt;

	bs::TextResource r;

	rt.setFileName(&r, path.utf8());

	std::cout << "Resource path = " << r.fileName().utf8() << std::endl;


	bool loadSuccessful = r.load();
	if (loadSuccessful)
	{
		std::cout << "Loading successful" << std::endl;
		bs::String text = r.getData();
		std::cout << "Text = \n" << text.utf8() << std::endl;
	}
	else std::cout << "Loading not successful" << std::endl;

	system("pause");
}

void	directoryScanTest()
{
	bs::initialize();

	showMemoryStats();

	std::cout << "Display root folder files" << std::endl;
	for (ui32 i = 0; i < bs::g_resourceManager.rootFolder().list.count(); i++) std::cout << bs::g_resourceManager.rootFolder().list[i].utf8() << std::endl;

	std::cout << "Display root folder folders" << std::endl;
	for (ui32 i = 0; i < bs::g_resourceManager.rootFolder().children.count(); i++) std::cout << bs::g_resourceManager.rootFolder().children[i]->name.utf8() << std::endl;

	std::cout << "Display root folder full paths" << std::endl;
	for (ui32 i = 0; i < bs::g_resourceManager.rootFolder().children.count(); i++) std::cout << bs::g_resourceManager.rootFolder().children[i]->fullPath.utf8()<< std::endl;

	showMemoryStats();

	std::cout << "sizeof(folder) = " << sizeof(bs::Folder) << std::endl;

	bs::shutDown();
	showMemoryStats();
	system("pause");
}

#endif