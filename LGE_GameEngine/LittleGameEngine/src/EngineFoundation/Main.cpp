#include "Game.h"

void executeGame()
{
	lge::Game *theGame = new lge::Game("Little Game Engine - Oribtal Cubes", 800, 600);
	theGame->Run();
	delete theGame;
}

#if defined _WIN32
	#include <Windows.h>
	
	// WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
	{
		executeGame();
		return 0;
	}
//#elif defined _LINUX || defined __APPLE__
//	int main(int argc, const char ** argv)
//	{
//		executeGame();
//		return 0;
//	}
#else
	#error Game cannot run on this platform! Only Windows is supported.
#endif