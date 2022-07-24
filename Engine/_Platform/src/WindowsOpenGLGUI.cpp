#include <iostream>
#include <thread>
#include <Windows.h>
#include <GL/gl.h>
#include "../include/WindowsOpenGLGUI.h"
#include "EngineOpenGL.h"
namespace Platform::GUI
{

	WindowsOpenGLGUI::WindowsOpenGLGUI()
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

		HDC hdc = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));

		int letWindowsChooseThisPixelFormat;
		letWindowsChooseThisPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, letWindowsChooseThisPixelFormat, &pfd);
		mGlContext = static_cast<void *>(wglCreateContext(hdc));
		ReleaseDC(reinterpret_cast<HWND>(this->GetWindowHandler()),hdc);
		//SetTimer(static_cast<HWND>(this->GetWindowHandler()), 1001, (UINT)(1.0f / 60), (TIMERPROC)NULL);
		SetupMessageHandlers();
	}

	WindowsOpenGLGUI::~WindowsOpenGLGUI()
	{
		isRunning = false;
		renderThread.join();
	}

	void WindowsOpenGLGUI::OnAfterCreation()
	{
		// PIXELFORMATDESCRIPTOR pfd =
		// 	{
		// 		sizeof(PIXELFORMATDESCRIPTOR),
		// 		1,
		// 		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
		// 		PFD_TYPE_RGBA,												// The kind of framebuffer. RGBA or palette.
		// 		32,															// Colordepth of the framebuffer.
		// 		0, 0, 0, 0, 0, 0,
		// 		0,
		// 		0,
		// 		0,
		// 		0, 0, 0, 0,
		// 		24, // Number of bits for the depthbuffer
		// 		8,	// Number of bits for the stencilbuffer
		// 		0,	// Number of Aux buffers in the framebuffer.
		// 		PFD_MAIN_PLANE,
		// 		0,
		// 		0, 0, 0};

		// HDC hdc = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));

		// int letWindowsChooseThisPixelFormat;
		// letWindowsChooseThisPixelFormat = ChoosePixelFormat(hdc, &pfd);
		// SetPixelFormat(hdc, letWindowsChooseThisPixelFormat, &pfd);
		// mGlContext = static_cast<void *>(wglCreateContext(hdc));
		// ReleaseDC(reinterpret_cast<HWND>(this->GetWindowHandler()),hdc);
		// //SetTimer(static_cast<HWND>(this->GetWindowHandler()), 1001, (UINT)(1.0f / 60), (TIMERPROC)NULL);
		// SetupMessageHandlers();
	}
	void WindowsOpenGLGUI::Run()
    {

		renderThread = std::thread(
			[&]()
			{
				std::cout<<"Thread start"<<std::endl;
				while(isRunning)
				{
					MakeCurrent();
					OnRender();
					Swap();
					std::this_thread::sleep_for(std::chrono::duration<float,std::milli>(10));
				}
				std::cout << "Thread end" << std::endl;
			});
		WindowsGUI::Run();
	}
	void WindowsOpenGLGUI::OnRender()
	{
		static float rotation = 0;

		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(rotation, 0, 1, 0);
		rotation += 1;
		
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex2f(0.0f, .5f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex2f(0.5f, -0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glEnd();

	}
	void WindowsOpenGLGUI::SetupMessageHandlers()
	{

		// this->AddMessageHandler(WM_TIMER, [&](void *wp, void *lp)
		// 						{
		// 							RedrawWindow(reinterpret_cast<HWND>(this->GetWindowHandler()),nullptr,nullptr,RDW_INVALIDATE);
		// 							// Swap();
		// 						});
		this->AddMessageHandler(WM_SIZE, [&](void *wp, void *lp)
								{
									OnResize(wp, lp);
								});

		// this->AddMessageHandler(WM_PAINT, [&](void *wp, void *lp)
		// 						{
		// 							// HDC hdc = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));
		// 							// PAINTSTRUCT ps;
		// 							// hdc = BeginPaint(reinterpret_cast<HWND>(this->GetWindowHandler()), &ps);

		// 							// EndPaint(reinterpret_cast<HWND>(this->GetWindowHandler()), &ps);
		// 							// ReleaseDC(reinterpret_cast<HWND>(this->GetWindowHandler()),hdc);
		// 						});
	}
	void WindowsOpenGLGUI::OnDestroy()
	{
	}

	void WindowsOpenGLGUI::Swap()
	{
		HDC hdc = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));
		SwapBuffers(hdc);
		ReleaseDC(reinterpret_cast<HWND>(this->GetWindowHandler()),hdc);
	}
	void WindowsOpenGLGUI::MakeCurrent()
	{
		HDC hdc = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));
		wglMakeCurrent(hdc, reinterpret_cast<HGLRC>(mGlContext));
		ReleaseDC(reinterpret_cast<HWND>(this->GetWindowHandler()),hdc);
	}
	void WindowsOpenGLGUI::OnResize(void *wp, void *lp)
	{
		UINT width = LOWORD(lp);
		UINT height = HIWORD(lp);
		MakeCurrent();
		glViewport(0, 0, width, height);
	}
} // namespace Platform::GUI
