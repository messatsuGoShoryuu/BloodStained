#include "FileExplorer.h"
#include <Globals\bs_globals.h>
#include <Platform\Windows\WindowsWindow\bs_WindowsWindow.h>
#include <Editor\bs_Editor.h>
#include <Math/bs_Quaternion.h>
#include <Math/bs_Vector3.h>
#include <Math/bs_Matrix4x4.h>
#include <Rendering/RenderedObjects/Debug/bs_DebugShader.h>

#include <thread>
#include "TestLevel.h"
#include "TestShader.h"
#include "TexShader3D.h"
#include "SpriteShader.h"
#include "Camera3DTest.h"
#include <Rendering\bs_Camera3D.h>
#include "FootballApp.h"
#include "SpriteTest.h"

void testFileExplorer();
void testWindowsEditorWindow();
void testFolderExplorer();
void testEditorApp();
void testMainWithEditor();
void testLevelScript();
void testQuaternion();
void testMatrix();
void FootballDemo();
void spriteDemo();

#ifdef BS_DEBUG_BUILD
int main()
#else
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#endif
{
//	testQuaternion();
//	testLevelScript();

//	FootballDemo();

	spriteDemo();
	
	return 0; 
}

void spriteDemo()
{
	SpriteShader* spriteShader = new SpriteShader();
	bs::DebugDrawShader* debugShader = new bs::DebugDrawShader();

	bs::initialize();

	FootballApp app;
	if (!app.initialize()) std::cout << "initialization failed" << std::endl;

	SpriteTest* t = new SpriteTest();
	bs::Level* level0 = bs::g_game.addLevel();
	level0->setScript(t);

	bs::g_windowsMain.main();

	app.shutDown();

	bs::Profiler::printMemoryStats(BS_UNDECORATED_FUNCTION);

	bs::shutDown();

	bs::Profiler::printMemoryStats(BS_UNDECORATED_FUNCTION);

	system("pause");
}

void FootballDemo()
{
	TestShader* testShader = new TestShader();
	TexShader3D* tex = new TexShader3D();
	bs::initialize();

	FootballApp app;
	if (!app.initialize()) std::cout << "initialization failed" << std::endl;

	//	TestLevel* t = new TestLevel();
	Camera3DTest* t = new Camera3DTest();
	bs::Level* level0 = bs::g_game.addLevel();
	level0->setScript(t);

	bs::g_windowsMain.main();

	app.shutDown();

	bs::Profiler::printMemoryStats(BS_UNDECORATED_FUNCTION);

	bs::shutDown();

	bs::Profiler::printMemoryStats(BS_UNDECORATED_FUNCTION);

}

void testMatrix()
{
	bs::Quaternion q(bs::Vector3(1, 0, 0), 30 * BS_DEG_TO_RAD);

	std::cout << q.toString().utf8() << std::endl;


	bs::Matrix4x4 m;
	bs::Matrix4x4 n;

	

	m.loadIdentity();
	

	bs::Camera3D c;
	c.setFov(60);
	c.setAspectRatio(800.0 / 600.0);
	bs::Matrix4x4 p = c.projection();
	std::cout << p.toString().utf8() << std::endl;

	q.toRotationMatrix(m);
	std::cout << std::endl;

	std::cout << m.toString().utf8() << std::endl;
	
	m.inverse(n);

	std::cout << std::endl;

	std::cout << n.toString().utf8() << std::endl;

	bs::Matrix4x4 mvp = m * p;
	std::cout << mvp.toString().utf8() << std::endl;

	bs::Vector3 vec(10, 100, -10);

	vec = mvp * vec;

	std::cout << vec.toString().utf8() << std::endl;

	system("pause");
}

void testQuaternion()
{
	bs::Quaternion q(bs::Vector3(1, 0, 0), -390 * BS_DEG_TO_RAD);

	std::cout << "q.x = " << q.x << ", q.y = " << q.y << ", q.z = " << q.z << ", q.w = " << q.w << std::endl;
	bs::Vector3 v(0.0f, 1.0f, 0.0f);
	bs::Vector3 r = q * v;
	std::cout << "v.x = " << v.x << ", v.y = " << v.y << ", v.z = " << v.z << std::endl;
	std::cout << "r.x = " << r.x << ", r.y = " << r.y << ", r.z = " << r.z << std::endl;

	q = q*q;

	bs::Vector3 eu = q.toEuler();
	eu *= BS_RAD_TO_DEG;
	std::cout << "eu.x = " << eu.x << ", eu.y = " << eu.y << ", eu.z = " << eu.z << std::endl;

	bs::Quaternion id = bs::Quaternion::identity;
	bs::Vector3 vec(0.5, 123, 2552.4);

	vec = id * vec;

	std::cout << id.toString().utf8() << std::endl;
	std::cout << vec.toString().utf8() << std::endl;

	system("pause");
}

void testLevelScript()
{
	TexShader3D* tex = new TexShader3D();
	bs::initialize();

	bs::editor::EditorApp editor;
	if (!editor.initialize()) std::cout << "initialization failed" << std::endl;

//	TestLevel* t = new TestLevel();
	Camera3DTest* t = new Camera3DTest();
	bs::Level* level0 = bs::g_game.addLevel(); 
	level0->setScript(t);

	bs::g_windowsMain.main();

	editor.shutDown();

	bs::Profiler::printMemoryStats(BS_UNDECORATED_FUNCTION);

	bs::shutDown();

	bs::Profiler::printMemoryStats(BS_UNDECORATED_FUNCTION);

	system("pause");
}

void testMainWithEditor()
{
	bs::initialize();

	bs::editor::EditorApp editor;
	if (!editor.initialize()) std::cout << "initialization failed" << std::endl;

	bs::g_windowsMain.main();

	bs::shutDown();
}

void testEditorApp()
{
	bs::initialize();
	bs::editor::EditorApp editor;

	if (!editor.initialize()) std::cout << "initialization failed" << std::endl;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (!editor.shutDown()) std::cout << "shut down failed" << std::endl;

	bs::shutDown();
}

void testFolderExplorer()
{
	bs::initialize();

	bs::editor::FolderExplorer f;

	if(!f.initialize()) std::cout<< "initialization failed"<<std::endl;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	bs::shutDown();
}

void testWindowsEditorWindow()
{
	bs::initialize();

	bs::editor::WindowsEditorWindow* w = new bs::editor::WindowsEditorWindow();

	w->setMetrics(0, 0, 1000, 600);

	

	if(!w->initialize()) std::cout<<"failed to initialize window"<<std::endl;

	w->setTextMargin("ASDFASDFF ÞÞ Þ LÝ Þ LÝ TEXT BU HACI", 0, 0, 0, 0);
	w->refreshDisplay();
	w->setTextColor(255, 0, 0);
	w->setTextProperties(BS_ALIGN_TOP | BS_ALIGN_LEFT, BS_ITALIC,30, "Times new roman");
	w->setTextMargin("\n2.SATIR GELÝYO ABÝEE", 0, 0, 0, 0);

	ui32 menuHandle = w->addMenu();
	ui32 subMenuHandle = w->addPopupMenu("File", menuHandle);
	w->appendPopupMenu("Exit", subMenuHandle);
	w->registerMenu(menuHandle);

	bs::editor::ListviewWindow* lv = new bs::editor::ListviewWindow();

	lv->setMetrics(0, 0, 500, 500);

	if (!lv->initialize()) std::cout << "Failed to initialize listview" << std::endl;
	lv->setBackgroundColor(bs::ColorRGB24::black);

	lv->addItem("Ahmet", bs::editor::LISTVIEW_ICON::FOLDER);
	lv->addItem("Mehmet", bs::editor::LISTVIEW_ICON::JPG);

	lv->refreshDisplay();


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	bs::shutDown();
}

void testFileExplorer()
{
	bs::initialize();

	FileExplorer f;
	f.initialize();

	f.updateFolderContent();

	HMENU mainMenu = CreateMenu();
	HMENU subMenu = CreatePopupMenu();
	AppendMenu(mainMenu, MF_STRING | MF_POPUP, (UINT)subMenu, "&File");
	AppendMenu(subMenu, MF_STRING, 0, "&New Game");
	AppendMenu(subMenu, MF_STRING, 0, "&Load Game");
	AppendMenu(subMenu, MF_STRING, 0, "E&xit");

	AppendMenu(mainMenu, MF_STRING | MF_POPUP, (UINT)subMenu, "&Bitmap shit");
	
	SetMenu(f.mainWindow()->hwnd(), mainMenu);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	f.shutDown();

	bs::shutDown();
}