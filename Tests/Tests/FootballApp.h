#ifndef FOOTBALLAPP_H
#define	FOOTBALLAPP_H

#include <Rendering\bs_OpenGLWindow.h>
#include <Functions\bs_BaseMemberFunction.h>

class FootballApp
{
public:
	FootballApp();
	~FootballApp();
public:
	//Manual init.
	bool	initialize();
	//Manual shut down.
	bool	shutDown();

	bool	initializeGameWindow();

public:
	//Callbacks.
	bs::MemberFunction<FootballApp, void, void>OnResizeGameDelegate;
	void OnResizeGame();

	bs::MemberFunction<FootballApp, void, void> GameThreadDelegate;
	void GameThread();

private:
	bs::OpenGLWindow*	m_gameWindow;
};


#endif // !FOOTBALLAPP_H
