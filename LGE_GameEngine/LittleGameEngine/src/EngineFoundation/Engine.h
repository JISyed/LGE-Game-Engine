#ifndef THE_GAME_ENGINE_CORE_H
#define THE_GAME_ENGINE_CORE_H

#include "GL/gl3w.h"
#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1
#include "GL/glfw.h"
#include "sb6ext.h"
#define ENGINE_TITLE_SIZE 128

// Defines for OpenGL versions
#define LGE_WIN_GL_VER_MAJOR 3
#define LGE_WIN_GL_VER_MINOR 3
#define LGE_OSX_GL_VER_MAJOR 3
#define LGE_OSX_GL_VER_MINOR 3


#include "..\EngineUtilities\Time.h"
#include "..\EngineUtilities\Screen.h"
#include "..\AbstractDataTypes\Color.h"


namespace lge
{

	// Abstract class that is the basis of any game made with this engine
	class Engine
	{
	public:

		//
		// Ctor / Dtor
		//

		// Constructor
		Engine(const char* const newWindowName, const int newWidth, const int newHeight);

		// Destructor
		virtual ~Engine();


		//
		// Program Lifetime Methods
		//

		// Run the lifetime of the engine's application (called only once!) (Not virtual!)
		void Run();

		// Construct nessesary system objects for the engine
		virtual void Initialize() = 0;

		// Create objects for external resources used in the engine
		virtual void LoadContent() = 0;

		// The logic loop of the engine that is called multiple times per second
		virtual void Update() = 0;

		// The draw loop of the engine that is called multiple times per second
		virtual void Draw() = 0;

		// Called before Draw() to clear OpenGL's render buffer
		void OnClearRenderBuffer();

		// Unload objects and resources used by the engine
		virtual void Shutdown() = 0;


		//
		// Event Methods
		//

		// Called when the window is resized
		virtual void onResize(const int w, const int h);

		// Called when the keyboard is used
		virtual void onKey(int key, int action);

		// Called when the mouse buttons are used
		virtual void onMouseButton(int button, int action);

		// Called when the mouse moves
		virtual void onMouseMove(int x, int y);

		// Called when the mouse wheel is used
		virtual void onMouseWheel(int pos);

		// Called when GLEW gets debug messages?
		virtual void onDebugMessage(GLenum source,
									GLenum type,
									GLuint id,
									GLenum severity,
									GLsizei length,
									const GLchar* message);

		//
		// Getters
		//

		// Get the current mouse coordinate position
		static void getMousePosition(int& x, int& y);

		// Get read-only values of the screen clear color
		static const Color& GetClearColor();
		


		//
		// Setters
		//

		// Set the clear color for OpenGL
		static void SetClearColor(const Color& newClearColor);



	public:

		//
		// Nested Struct
		//

		// Contains metadata about the program
		struct APPINFO
		{
			char title[ENGINE_TITLE_SIZE];	// The title on the window title bar
			int majorVersion;				// OpenGL major version number
			int minorVersion;				// OpenGL minor version number
			int samples;					// What is this?
#pragma warning( disable : 4201)
			union
			{
				struct
				{
					unsigned int    fullscreen : 1;		// Enable fullscreen
					unsigned int    vsync : 1;			// Enable Vsync
					unsigned int    cursor : 1;			// Enable rendering of mouse cursor
					unsigned int    stereo : 1;			// Don't know what stereo is?
					unsigned int    debug : 1;			// Enable debug mode?
				};
				unsigned int        all;				// Used to clear all the flags at once
			} flags;			// Application flags
		};

	protected:

		//
		// GLFW API Wrapping
		//

		static void GLFWCALL glfw_onResize(int w, int h);
		static void GLFWCALL glfw_onKey(int key, int action);
		static void GLFWCALL glfw_onMouseButton(int button, int action);
		static void GLFWCALL glfw_onMouseMove(int x, int y);
		static void GLFWCALL glfw_onMouseWheel(int pos);
		static void APIENTRY debug_callback(GLenum source,
											GLenum type,
											GLuint id,
											GLenum severity,
											GLsizei length,
											const GLchar* message,
											GLvoid* userParam);
		void setVsync(bool enable);




	protected:

		//
		// Protected Data
		//

		APPINFO     info;						// Program metadata
		static      Engine* onlyInstance;		// Singeton instance (needed for GLFW callbacks)


	private:

		//
		// Data
		//

		Screen screen;	// Information about the program screen size
		Time time;	// The timing system
		Color clearColor;	// Color of screen after glClear()






		//
		// Private Helper Routines
		//

		// Secretly called before Engine::Initialize()
		bool PreInitialize();

		// Secretly called before Engine::LoadContent() and after Engine::Initialize()
		bool PreLoadContent();

		// Secretly called after Engine::Shutdown()
		void PostShutdown();



		//
		// Deleted Methods
		//

		// No default constructor
		Engine() = delete;

		// No Copy ctor allowed
		Engine(const Engine& other) = delete;

		// No copy assignment overload allowed (pointers don't count)
		Engine& operator=(const Engine& other) = delete;

		// No move ctor
		Engine(Engine&& other) = delete;
		
		// No move assignment
		Engine& operator=(Engine&& other) = delete;
	};

}


#endif /* THE_GAME_ENGINE_CORE_H */

