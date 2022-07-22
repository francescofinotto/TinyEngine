#include "../include/Win32Gui.h"
#include <windows.h>
#include <stdexcept>
namespace Platform::GUI
{

    class Win32Gui::WindowImplementation
    {
    public:
        WindowImplementation() = default;
        ~WindowImplementation(){};
        HWND windowHandler;
        static bool SetWindowInstanceToWindowLongPtr(Win32Gui *windowPtr, HWND &hwnd, LPARAM &lp)
        {
            auto temp = static_cast<Win32Gui *>(reinterpret_cast<CREATESTRUCT *>(lp)->lpCreateParams);
            windowPtr = dynamic_cast<Win32Gui *>(temp);
            if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowPtr)))
            {
                return true;
            }
            return false;
        };
        /**
         * @brief Handle Messaging system
         *
         */
        static LRESULT CALLBACK MessageRoutine(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
        {
            Win32Gui *windowPtr = nullptr;
            if (wm == WM_NCCREATE) // on creation set pointer to this window
            {
                SetLastError(0);
                if (!SetWindowInstanceToWindowLongPtr(windowPtr, hwnd, lp))
                {
                    if (GetLastError() != 0)
                        return FALSE;
                }
            }
            else
            { // Set window Ptr if present
                windowPtr = reinterpret_cast<Win32Gui *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            }

            switch (wm)
            {
            case WM_CREATE:

                windowPtr->mEventHandler->OnCreate();

                break;

            case WM_LBUTTONDOWN:
            {
                int xPos = LOWORD(lp);
                int yPos = HIWORD(lp);
                SetCursor(LoadCursor(NULL,IDC_HAND));
                // windowPtr->events.push_back(std::make_shared<MouseClickedEvent>(xPos, yPos, MouseEvent::LEFT));
                break;
            }
            case WM_LBUTTONUP:
            {
                SetCursor(LoadCursor(NULL,IDC_NO));
            }
            case WM_MOUSEMOVE:{
                SetCursor(LoadCursor(NULL,IDC_IBEAM));
                return true;
            }
            case WM_SETCURSOR:
            {
                SetWindowLongPtr(hwnd, DWLP_MSGRESULT, TRUE);
            }
            case WM_COMMAND:
                break;
            case WM_TIMER:
                InvalidateRect(hwnd, NULL, FALSE);
                break;
            case WM_PAINT:
                windowPtr->mEventHandler->OnUpdate();
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
                windowPtr->mEventHandler->OnDestroy();
                PostQuitMessage(0);
                break;
            }
            return DefWindowProc(hwnd, wm, wp, lp);
        }
    };

    Win32Gui::Win32Gui(std::unique_ptr<WindowEventHandler> eventHandler, std::string title)
        : mTitle(title), mEventHandler(std::move(eventHandler)), mImplementation(std::make_unique<WindowImplementation>())
    {
        auto hInst = GetModuleHandle(NULL);
        WNDCLASSEX wc;
        wc.cbSize = sizeof(wc);
        wc.style = 0;
        wc.lpfnWndProc = WindowImplementation::MessageRoutine;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInst;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = mTitle.c_str();
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        if (!RegisterClassEx(&wc))
        {
            throw std::runtime_error("Cannot Register Window Class");
        }
        mImplementation->windowHandler = CreateWindowEx(WS_EX_LEFT,
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
        if (!mImplementation->windowHandler)
        {
            throw std::runtime_error("Cannot create Window");
        }

        SetWindowText(static_cast<HWND>(mImplementation->windowHandler), mTitle.c_str());
    }


    Win32Gui::~Win32Gui()
    {
 
    }


    void Win32Gui::Run()
    {
        MSG msg;

        ShowWindow(static_cast<HWND>(mImplementation->windowHandler), SW_NORMAL);
        UpdateWindow(static_cast<HWND>(mImplementation->windowHandler));

        mEventHandler->OnAfterCreation();

        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

}