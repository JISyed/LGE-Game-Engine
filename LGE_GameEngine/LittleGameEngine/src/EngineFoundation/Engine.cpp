#include "Engine.h"

#include "GL/glext.h"
#include <string.h>
#include <stdio.h>
#include <cassert>
#include "..\GraphicsSystem\GpuBufferVao.h"

namespace lge
{


	//
	// Static Data
	//

	// Singleton instance
	Engine* Engine::onlyInstance = nullptr;



	//
	// Constructor/Destructor
	//

	// Constructor
	Engine::Engine(const char* const newWindowName, const int newWidth, const int newHeight) :
		screen(newWidth, newHeight),
		time(),
		clearColor(0.1f, 0.1f, 0.1f)
	{
		#if defined _WIN32
			strcpy_s(info.title, ENGINE_TITLE_SIZE, newWindowName);
		#else
			strcpy(info.title, newWindowName);
		#endif

		#ifdef __APPLE__
				info.majorVersion = LGE_OSX_GL_VER_MAJOR;
				info.minorVersion = LGE_OSX_GL_VER_MINOR;
		#else
				info.majorVersion = LGE_WIN_GL_VER_MAJOR;
				info.minorVersion = LGE_WIN_GL_VER_MINOR;
		#endif

		info.samples = 0;
		info.flags.all = 0;
		info.flags.cursor = 1;

		#ifdef _DEBUG
			info.flags.debug = 1;
		#endif

		// Set the singleton pointer for the Engine
		assert(Engine::onlyInstance == nullptr);
		Engine::onlyInstance = this;
	}


	// VIRTUAL
	// Destructor
	Engine::~Engine()
	{
		Engine::onlyInstance = nullptr;
	}




	//
	// Application Lifetime Methods
	//

	// Run the lifetime of the engine's application (called only once!) (Not virtual!)
	void Engine::Run()
	{
		if (!this->PreInitialize())
		{
			return;
		}

		this->Initialize();

		if (!this->PreLoadContent())
		{
			return;
		}

		this->LoadContent();

		// The Game Loop
		while ((glfwGetKey(GLFW_KEY_ESC) == GLFW_RELEASE) && (glfwGetWindowParam(GLFW_OPENED) != GL_FALSE))
		{
			this->time.Update();
			this->Update();

			this->OnClearRenderBuffer();
			this->Draw();

			glfwSwapBuffers();
		}
		// End the Game Loop

		this->Shutdown();

		this->PostShutdown();

		// Must be called to shutdown GLFW
		glfwTerminate();
	}

	// Secretly called before Engine::Initialize()
	bool Engine::PreInitialize()
	{
		// Initialize GLFW
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			return false;
		}

		return true;
	}

	// Secretly called before Engine::LoadContent() and after Engine::Initialize()
	bool Engine::PreLoadContent()
	{
		// Tell GLFW about the OpenGL version
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, info.majorVersion);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, info.minorVersion);

		// Setup OpenGL window data
#ifdef _DEBUG
		glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, info.samples);
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
		glfwOpenWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);

		// Open the window native to the OS...
		// ... if in Full-Screen
		if (info.flags.fullscreen)
		{
			if (Screen::GetWidth() == 0 || Screen::GetHeight() == 0)
			{
				GLFWvidmode mode;
				glfwGetDesktopMode(&mode);
				this->screen.SetWidthAndHeight(mode.Width, mode.Height);
			}
			glfwOpenWindow(Screen::GetWidth(), Screen::GetHeight(), 8, 8, 8, 0, 32, 0, GLFW_FULLSCREEN);
			glfwSwapInterval((int)info.flags.vsync);
		}
		// ... or in Windowed-Mode
		else
		{
			if (!glfwOpenWindow(Screen::GetWidth(), Screen::GetHeight(), 8, 8, 8, 0, 32, 0, GLFW_WINDOW))
			{
				fprintf(stderr, "Failed to open window\n");
				return false;
			}
		}

		// Set the title of the opened window
		glfwSetWindowTitle(info.title);

		// Setup GLFW Input Event callbacks
		glfwSetWindowSizeCallback(glfw_onResize);
		glfwSetKeyCallback(glfw_onKey);
		glfwSetMouseButtonCallback(glfw_onMouseButton);
		glfwSetMousePosCallback(glfw_onMouseMove);
		glfwSetMouseWheelCallback(glfw_onMouseWheel);

		// Didn't know the tertiary operator can be used to pick which function :O
		(info.flags.cursor ? glfwEnable : glfwDisable)(GLFW_MOUSE_CURSOR);
		info.flags.stereo = (glfwGetWindowParam(GLFW_STEREO) ? 1 : 0);

		// Setup OpenGL...?
		gl3wInit();

		// Print OpenGL stats to console
#ifdef _DEBUG
		fprintf(stderr, "VENDOR: %s\n", (char *)glGetString(GL_VENDOR));
		fprintf(stderr, "VERSION: %s\n", (char *)glGetString(GL_VERSION));
		fprintf(stderr, "RENDERER: %s\n", (char *)glGetString(GL_RENDERER));
#endif

		// Setup GLFW debug callbacks
		if (info.flags.debug)
		{
			// ARB Debug Output was written against OpenGL 4.0
			// https://www.opengl.org/registry/specs/ARB/debug_output.txt
			if (gl3wIsSupported(4, 0))
			{
				glDebugMessageCallback(debug_callback, this);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			}
			else if (sb6IsExtensionSupported("GL_ARB_debug_output"))
			{
				glDebugMessageCallbackARB(debug_callback, this);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
			}
		}


		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);


		// Setup GpuBuffer VAO
		GpuBufferVao::Init();
		GpuBufferVao::Unactivate();

		return true;
	}

	
	// Called before Draw() to clear OpenGL's render buffer. NOT virtual
	void Engine::OnClearRenderBuffer()
	{
		static const GLfloat one = 1.0f;

		glViewport(0, 0, Screen::GetWidth(), Screen::GetHeight());
		glClearBufferfv(GL_COLOR, 0, this->clearColor.GetRawData());
		glClearBufferfv(GL_DEPTH, 0, &one);
	}


	// VIRTUAL
	// Secretly called after Engine::Shutdown()
	void Engine::PostShutdown()
	{
		GpuBufferVao::Destroy(this);
	}



	//
	// Event Methods
	//

	// VIRTUAL
	// Called when the window is resized
	void Engine::onResize(const int w, const int h)
	{
		this->screen.SetWidthAndHeight(w, h);
	}


	// VIRTUAL
	// Called when the keyboard is used
	void Engine::onKey(int key, int action)
	{
		key;//not used
		action;//not used
	}


	// VIRTUAL
	// Called when the mouse buttons are used
	void Engine::onMouseButton(int button, int action)
	{
		button;//not used
		action;//not used
	}

	// VIRTUAL
	// Called when the mouse moves
	void Engine::onMouseMove(int x, int y)
	{
		x; /*not used*/
		y;/* not used*/
	}

	// VIRTUAL
	// Called when the mouse wheel is used
	void Engine::onMouseWheel(int pos)
	{
		pos; /*not used*/
	}


	// VIRTUAL
	// Called when GLEW gets debug messages?
	void Engine::onDebugMessage(GLenum source,
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar* message)
	{
#ifdef _WIN32
		OutputDebugStringA(message);
		OutputDebugStringA("\n");

		type; //not used
		id; //not used
		severity; //not used
		length;//not used

		source; /*not used*/
#endif /* _WIN32 */
	}



	//
	// Getters
	//


	// STATIC
	// Get the current mouse coordinate position
	void Engine::getMousePosition(int& x, int& y)
	{
		glfwGetMousePos(&x, &y);
	}

	// STATIC
	// Get read-only values of the screen clear color
	const Color& Engine::GetClearColor()
	{
		assert(Engine::onlyInstance != nullptr);
		return Engine::onlyInstance->clearColor;
	}



	//
	// Setters
	//

	// STATIC
	// Set the clear color for OpenGL
	void Engine::SetClearColor(const Color& newClearColor)
	{
		assert(Engine::onlyInstance != nullptr);
		Engine::onlyInstance->clearColor = newClearColor;
	}





	//
	// GLFW API Wrapping
	//

	// STATIC
	void GLFWCALL Engine::glfw_onResize(int w, int h)
	{
		Engine::onlyInstance->onResize(w, h);
	}

	// STATIC
	void GLFWCALL Engine::glfw_onKey(int key, int action)
	{
		Engine::onlyInstance->onKey(key, action);
	}

	// STATIC
	void GLFWCALL Engine::glfw_onMouseButton(int button, int action)
	{
		Engine::onlyInstance->onMouseButton(button, action);
	}

	// STATIC
	void GLFWCALL Engine::glfw_onMouseMove(int x, int y)
	{
		Engine::onlyInstance->onMouseMove(x, y);
	}

	// STATIC
	void GLFWCALL Engine::glfw_onMouseWheel(int pos)
	{
		Engine::onlyInstance->onMouseWheel(pos);
	}

	// STATIC
	void APIENTRY Engine::debug_callback(GLenum source,
										 GLenum type,
										 GLuint id,
										 GLenum severity,
										 GLsizei length,
										 const GLchar* message,
										 GLvoid* userParam)
	{
		reinterpret_cast<Engine *>(userParam)->onDebugMessage(source, type, id, severity, length, message);
	}

	void Engine::setVsync(bool enable)
	{
		info.flags.vsync = enable ? 1 : 0;
		glfwSwapInterval((int)info.flags.vsync);
	}


}
