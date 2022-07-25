#include <iostream>
#include <thread>
#include <mutex>
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
		ReleaseDC(reinterpret_cast<HWND>(this->GetWindowHandler()), hdc);
		SetupMessageHandlers();
	}

	WindowsOpenGLGUI::~WindowsOpenGLGUI()
	{
		isRunning = false;
		renderThread.join();
	}

	void WindowsOpenGLGUI::OnAfterCreation()
	{
	}
	void WindowsOpenGLGUI::Run()
	{
		// mRenderThread = std::move(Common::Threading::GUILoopThread(std::function<void()>(
		// 	[&]()
		// 	{
		// 		std::cout << "Thread start" << std::endl;
		// 		while (isRunning)
		// 		{
		// 			ExecuteWithCurrentContext([&]()
		// 									{
		// 					OnRender();
		// 					Swap(); });
		// 			std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(10));
		// 		}
		// 		std::cout << "Thread end" << std::endl;
		// 	}
		// )));
		renderThread = std::thread(
			[&]()
			{
				std::cout<<"Thread start"<<std::endl;
				while(isRunning)
				{
					ExecuteWithCurrentContext([&](){
						OnRender();
						Swap();
					});
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
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(0.0f, .5f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(0.5f, -0.5f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glEnd();

	}
	void WindowsOpenGLGUI::SetupMessageHandlers()
	{
			this->AddMessageHandler(WM_SIZE, [&](void *wp, void *lp)
									{ OnResize(wp, lp); });

	}
	void WindowsOpenGLGUI::OnDestroy()
	{
	}

	void WindowsOpenGLGUI::Swap()
	{
			HDC hdc = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));
			SwapBuffers(hdc);
			ReleaseDC(reinterpret_cast<HWND>(this->GetWindowHandler()), hdc);
	}
	void WindowsOpenGLGUI::MakeCurrent()
	{
			HDC hdc = GetDC(reinterpret_cast<HWND>(this->GetWindowHandler()));
			wglMakeCurrent(hdc, reinterpret_cast<HGLRC>(mGlContext));
			ReleaseDC(reinterpret_cast<HWND>(this->GetWindowHandler()), hdc);
	}
	void WindowsOpenGLGUI::ExecuteWithCurrentContext(std::function<void(void)> callback)
    {
			std::lock_guard<std::mutex> lock{mutexContext};
			MakeCurrent();
			callback();
			wglMakeCurrent(nullptr, nullptr);
    }
	void WindowsOpenGLGUI::OnResize(void *wp, void *lp)
	{
			UINT width = LOWORD(lp);
			UINT height = HIWORD(lp);
			ExecuteWithCurrentContext([&]()
									  { glViewport(0, 0, width, height); });
	}
	} // namespace Platform::GUI
