/*
 * Copyright � 2012-2013 Graham Sellers
 *
 * This code is part of the OpenGL SuperBible, 6th Edition.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __SB6_H__
#define __SB6_H__

#ifdef WIN32
    #pragma once
    #define _CRT_SECURE_NO_WARNINGS 1

    #define WIN32_LEAN_AND_MEAN 1
    #include <Windows.h>

    #ifdef _DEBUG
        #ifdef _WIN64
            #pragma comment (lib, "GLFW_d64.lib")
            #ifndef IN_SB6_LIB
                #pragma comment (lib, "sb6_d64.lib")
            #endif
        #else
			#pragma comment (lib, "GLFW_Debug.lib")
            #ifndef IN_SB6_LIB
                #pragma comment (lib, "sb6_Debug.lib")
            #endif
        #endif
    #else
        #ifdef _WIN64
            #pragma comment (lib, "GLFW_r64.lib")
            #ifndef IN_SB6_LIB
                #pragma comment (lib, "sb6_r64.lib")
            #endif
        #else
            #pragma comment (lib, "GLFW_Release.lib")
            #ifndef IN_SB6_LIB
                #pragma comment (lib, "sb6_Release.lib")
            #endif
        #endif
    #endif

    #pragma comment (lib, "OpenGL32.lib")
#endif

#include "GL/gl3w.h"

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1
#include "GL/glfw.h"

#include "sb6ext.h"

#include <stdio.h>
#include <string.h>


// Defines for OpenGL versions
#define SB6_WIN_GL_VER_MAJOR 3
#define SB6_WIN_GL_VER_MINOR 3
#define SB6_OSX_GL_VER_MAJOR 3
#define SB6_OSX_GL_VER_MINOR 3

namespace sb6
{

class application
{
public:
    application() {}
    virtual ~application() {}
    virtual void run(sb6::application* the_app)
    {
        bool running = true;
        app = the_app;

        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            return;
        }

        init();

        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, info.majorVersion);
        glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, info.minorVersion);

#ifdef _DEBUG
        glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif /* _DEBUG */
        glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwOpenWindowHint(GLFW_FSAA_SAMPLES, info.samples);
        glfwOpenWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);
        if (info.flags.fullscreen)
        {
            if (info.windowWidth == 0 || info.windowHeight == 0)
            {
                GLFWvidmode mode;
                glfwGetDesktopMode(&mode);
                info.windowWidth = mode.Width;
                info.windowHeight = mode.Height;
            }
            glfwOpenWindow(info.windowWidth, info.windowHeight, 8, 8, 8, 0, 32, 0, GLFW_FULLSCREEN);
            glfwSwapInterval((int)info.flags.vsync);
        }
        else
        {
            if (!glfwOpenWindow(info.windowWidth, info.windowHeight, 8, 8, 8, 0, 32, 0, GLFW_WINDOW))
            {
                fprintf(stderr, "Failed to open window\n");
                return;
            }
        }

        glfwSetWindowTitle(info.title);
        glfwSetWindowSizeCallback(glfw_onResize);
        glfwSetKeyCallback(glfw_onKey);
        glfwSetMouseButtonCallback(glfw_onMouseButton);
        glfwSetMousePosCallback(glfw_onMouseMove);
        glfwSetMouseWheelCallback(glfw_onMouseWheel);
        (info.flags.cursor ? glfwEnable : glfwDisable)(GLFW_MOUSE_CURSOR);

        info.flags.stereo = (glfwGetWindowParam(GLFW_STEREO) ? 1 : 0);

        gl3wInit();

#ifdef _DEBUG
        fprintf(stderr, "VENDOR: %s\n", (char *)glGetString(GL_VENDOR));
        fprintf(stderr, "VERSION: %s\n", (char *)glGetString(GL_VERSION));
        fprintf(stderr, "RENDERER: %s\n", (char *)glGetString(GL_RENDERER));
#endif

        if (info.flags.debug)
        {
			// ARB Debug output was written against OpenGL 4.0
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

        startup();

        do
        {
            render(glfwGetTime());

            glfwSwapBuffers();

            running &= (glfwGetKey( GLFW_KEY_ESC ) == GLFW_RELEASE);
            running &= (glfwGetWindowParam( GLFW_OPENED ) != GL_FALSE);
        } while(running);

        shutdown();

        glfwTerminate();
    }

    virtual void init()
    {
#if defined _WIN32
		strcpy_s(info.title, 128, "SuperBible6 Example");
#else
		strcpy(info.title, "SuperBible6 Example");
#endif
        info.windowWidth = 800;
        info.windowHeight = 600;
#ifdef __APPLE__
		info.majorVersion = SB6_OSX_GL_VER_MAJOR;
		info.minorVersion = SB6_OSX_GL_VER_MINOR;
#else
		info.majorVersion = SB6_WIN_GL_VER_MAJOR;
		info.minorVersion = SB6_WIN_GL_VER_MINOR;
#endif
        info.samples = 0;
        info.flags.all = 0;
        info.flags.cursor = 1;
#ifdef _DEBUG
        info.flags.debug = 1;
#endif
    }

    virtual void startup()
    {

    }

    virtual void render(double currentTime)
    {
		currentTime;//not used

    }

    virtual void shutdown()
    {

    }

    virtual void onResize(int w, int h)
    {
        info.windowWidth = w;
        info.windowHeight = h;
    }

    virtual void onKey(int key, int action)
    {
		key;//not used
		action;//not used
    }

    virtual void onMouseButton(int button, int action)
    {
		button;//not used
		action;//not used
    }

    virtual void onMouseMove(int x, int y)
    {
		x; /*not used*/
		y;/* not used*/
    }

    virtual void onMouseWheel(int pos)
    {
		pos; /*not used*/
    }

    virtual void onDebugMessage(GLenum source,
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

    static void getMousePosition(int& x, int& y)
    {
        glfwGetMousePos(&x, &y);
    }

public:
    struct APPINFO
    {
        char title[128];
        int windowWidth;
        int windowHeight;
        int majorVersion;
        int minorVersion;
        int samples;
		#pragma warning( disable : 4201)
        union
        {
            struct
            {
                unsigned int    fullscreen  : 1;
                unsigned int    vsync       : 1;
                unsigned int    cursor      : 1;
                unsigned int    stereo      : 1;
                unsigned int    debug       : 1;
            };
            unsigned int        all;
        } flags;
    };

protected:
    APPINFO     info;
    static      sb6::application * app;

    static void GLFWCALL glfw_onResize(int w, int h)
    {
        app->onResize(w, h);
    }

    static void GLFWCALL glfw_onKey(int key, int action)
    {
        app->onKey(key, action);
    }

    static void GLFWCALL glfw_onMouseButton(int button, int action)
    {
        app->onMouseButton(button, action);
    }

    static void GLFWCALL glfw_onMouseMove(int x, int y)
    {
        app->onMouseMove(x, y);
    }

    static void GLFWCALL glfw_onMouseWheel(int pos)
    {
        app->onMouseWheel(pos);
    }

    void setVsync(bool enable)
    {
        info.flags.vsync = enable ? 1 : 0;
        glfwSwapInterval((int)info.flags.vsync);
    }

    static void APIENTRY debug_callback(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar* message,
                                        GLvoid* userParam)
    {
        reinterpret_cast<application *>(userParam)->onDebugMessage(source, type, id, severity, length, message);
    }
};

};

#if defined _WIN32
#define DECLARE_MAIN(a)                             \
sb6::application *app = 0;                          \
int CALLBACK WinMain(HINSTANCE hInstance,           \
                     HINSTANCE hPrevInstance,       \
                     LPSTR lpCmdLine,               \
                     int nCmdShow)                  \
{                                                   \
	hPrevInstance; /*not used*/                     \
    hInstance; /*not used*/                         \
	lpCmdLine; /*not used*/                         \
	nCmdShow; /*not used*/                          \
    a *app = new a;                                 \
    app->run(app);                                  \
    delete app;                                     \
    return 0;                                       \
}
#elif defined _LINUX || defined __APPLE__
#define DECLARE_MAIN(a)                             \
int main(int argc, const char ** argv)              \
{                                                   \
    a *app = new a;                                 \
    app->run(app);                                  \
    delete app;                                     \
    return 0;                                       \
}
#else
#error Undefined platform!
#endif

#endif /* __SB6_H__ */

