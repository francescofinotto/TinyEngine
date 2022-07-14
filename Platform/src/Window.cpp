#include "../include/Window.h"
#include "windows.h"
#include <iostream>

namespace Platform
{
    class Window::WindowImplementation
    {
    public:
        WindowImplementation(std::string title): mTitle(title)
        {
            std::cout << "Window Implementation created" << std::endl;
        };

        ~WindowImplementation()
        {
            std::cout << "Window Implementation Destroied" << std::endl;
        };
        void Run()
        {
            MSG msg;
            auto hInst = GetModuleHandle(NULL);
            WNDCLASSEX wc;
            wc.cbSize = sizeof(wc);
            wc.style = 0;
            wc.lpfnWndProc = WndProc;
            wc.cbClsExtra = 0;
            wc.cbWndExtra = 0;
            wc.hInstance = hInst;
            wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
            wc.lpszMenuName = NULL;
            wc.lpszClassName = mTitle.c_str();
            wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
            if (!RegisterClassEx(&wc))
            {
                throw std::runtime_error("Cannot Register Window Class");
            }
            windowHandle = CreateWindowEx(WS_EX_LEFT,
                                           mTitle.c_str(),
                                           NULL,
                                           WS_OVERLAPPEDWINDOW,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           NULL,
                                           NULL,
                                           hInst,
                                           this);
            if (!windowHandle)
            {
                throw std::runtime_error("Cannot create Window");
            }

            SetWindowText(static_cast<HWND>(windowHandle), mTitle.c_str());

            ShowWindow(static_cast<HWND>(windowHandle), SW_NORMAL);
            UpdateWindow(static_cast<HWND>(windowHandle));
            // AfterCreation();
            while (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

    private:
        HWND windowHandle;
        std::string mTitle;
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
        {
            WindowImplementation *windowPtr = nullptr;

            if (wm == WM_NCCREATE) // on creation set pointer to this window
            {
                auto temp = static_cast<WindowImplementation *>(reinterpret_cast<CREATESTRUCT *>(lp)->lpCreateParams);
                windowPtr = dynamic_cast<WindowImplementation *>(temp);
                SetLastError(0);
                if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowPtr)))
                {
                    if (GetLastError() != 0)
                        return FALSE;
                }
            }
            else
            { // Set window Ptr if present
                windowPtr = reinterpret_cast<WindowImplementation *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            }

            switch (wm)
            {
            case WM_CREATE:
                // windowPtr->OnCreate();
                break;
            case WM_LBUTTONDOWN:
            {
                int xPos = LOWORD(lp);
                int yPos = HIWORD(lp);
                // windowPtr->events.push_back(std::make_shared<MouseClickedEvent>(xPos, yPos, MouseEvent::LEFT));
                break;
            }
            case WM_COMMAND:
                break;
            case WM_TIMER:
                InvalidateRect(hwnd, NULL, FALSE);
                break;
            case WM_PAINT:
                // windowPtr->OnUpdate();
                break;
            case WM_SIZE:
            {
                UINT width = LOWORD(lp);
                UINT height = HIWORD(lp);
                // windowPtr->width = width;
                // windowPtr->height = height;
                // windowPtr->OnResize(width, height);
                break;
            }
            case WM_DESTROY:
                // windowPtr->OnDestroy();
                PostQuitMessage(0);
                break;
            }
            return DefWindowProc(hwnd, wm, wp, lp);
        }
    };

    Window::Window(std::string title) : windowInstance(std::make_unique<WindowImplementation>(title)){};

    Window::~Window(){

    };
    void Window::Run()
    {
        windowInstance->Run();
    }
}