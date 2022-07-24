#include <iostream>
#include <Windows.h>
#include <GL/gl.h>
#include "../include/WindowsOpenGLGUI.h"
namespace Platform::GUI
{

	WindowsOpenGLGUI::WindowsOpenGLGUI()
	{
	}

	WindowsOpenGLGUI::~WindowsOpenGLGUI()
	{
	}

	void WindowsOpenGLGUI::OnAfterCreation()
	{
		PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
				PFD_TYPE_RGBA,												// The kind of framebuffer. RGBA or palette.
				32,															// Colordepth of the framebuffer.
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24, // Number of bits for the depthbuffer
				8,	// Number of bits for the stencilbuffer
				0,	// Number of Aux buffers in the framebuffer.
				PFD_MAIN_PLANE,
				0,
				0, 0, 0};

		HDC deviceContext = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));

		int letWindowsChooseThisPixelFormat;
		letWindowsChooseThisPixelFormat = ChoosePixelFormat(deviceContext, &pfd);
		SetPixelFormat(deviceContext, letWindowsChooseThisPixelFormat, &pfd);
		mGlContext = static_cast<void *>(wglCreateContext(deviceContext));
		SetTimer(static_cast<HWND>(this->GetWindowHandler()), 1001, (UINT)(1.0f / 60), (TIMERPROC)NULL);
		this->AddMessageHandler(WM_TIMER, [&](void* wp,void* lp)
								{ OnRender(); });
		this->AddMessageHandler(WM_SIZE, [&](void* wp, void* lp)
								{ OnResize(wp,lp); });
	}
	float rotation = 0;
	void WindowsOpenGLGUI::OnRender()
	{
		MakeCurrent();
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glMatrixMode(GL_VIEWPORT);
		glLoadIdentity();
		glPushMatrix();
		glRotatef(rotation, 0, 1, 0);
		rotation += 1;
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, .5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		Swap();
	}
	void WindowsOpenGLGUI::OnDestroy()
	{
	}

	void WindowsOpenGLGUI::Swap()
	{
		HDC deviceContext = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));
		SwapBuffers(deviceContext);
	}
	void WindowsOpenGLGUI::MakeCurrent()
	{
		HDC deviceContext = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));
		wglMakeCurrent(deviceContext, reinterpret_cast<HGLRC>(mGlContext));
	}
	void WindowsOpenGLGUI::OnResize(void* wp,void* lp)
	{
		UINT width = LOWORD(lp);
		UINT height = HIWORD(lp);
		MakeCurrent();
		glViewport(0, 0, width,height);
	}
} // namespace Platform::GUI
