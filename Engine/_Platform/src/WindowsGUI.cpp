#include <iostream>
#include <map>
#include <stdexcept>
#include <windows.h>
#include "../include/WindowsGUI.h"
namespace Platform::GUI
{
#pragma region WindowsGUI::Implementation

    class WindowsGUI::Implementation
    {
    public:
        Implementation(WindowsGUI *container) : mContainer(container)
        {
            mInstance = GetModuleInstance();
            mWndClassEx = GenerateClassEx();
            if (!RegisterClassEx(&mWndClassEx))
            {
                auto error = GetLastError();
                throw std::runtime_error("Cannot register classex");
            }
            mWindowsHandler = GenerateWindow();
            if (!mWindowsHandler)
            {
                auto error = GetLastError();
                throw std::runtime_error("Cannot create window ");
            }
        };
        ~Implementation(){};
        void Run()
        {
            MSG msg;

            ShowWindow(static_cast<HWND>(mWindowsHandler), SW_NORMAL);
            UpdateWindow(static_cast<HWND>(mWindowsHandler));
            // mContainer->OnAfterCreation();
            while (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            std::cout<<"Program exit"<<std::endl;
        };

        void AddMessageHandler(uint16_t message, MESSAGE_HANDLER handler)
        {
            this->mMessageHandlers[message] = handler;
        };

        void RemoveMessageHandler(uint16_t message)
        {
            this->mMessageHandlers.erase(message);
        };

        static bool SetWindowInstanceToWindowLongPtr(Implementation *windowPtr, HWND &hwnd, LPARAM &lp)
        {

            auto temp = static_cast<Implementation *>(reinterpret_cast<CREATESTRUCT *>(lp)->lpCreateParams);
            windowPtr = dynamic_cast<Implementation *>(temp);
            if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowPtr)))
            {
                return true;
            }
            return false;
        };
        static LRESULT CALLBACK MessageHandling(HWND hwnd, UINT windowMessage, WPARAM wp, LPARAM lp)
        {
            WindowsGUI::Implementation *impl = nullptr;
            if (windowMessage == WM_NCCREATE)
            {
                // Set Implementation instance as GWLP_USERDATA
                SetLastError(0);
                if (!SetWindowInstanceToWindowLongPtr(impl, hwnd, lp))
                {
                    if (GetLastError() != 0)
                        return FALSE;
                }
            }
            else
            {
                // Get implementation from GWLP_USERDATA
                impl = reinterpret_cast<Implementation *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            }


            if (impl != nullptr)
            {
                // Handle Code after implementation is set
                auto& handler = impl->mMessageHandlers.find(windowMessage);
                if(handler!= impl->mMessageHandlers.end())
                {
                    handler->second(reinterpret_cast<void*>(wp),reinterpret_cast<void*>(lp));
                }
            }


            if(windowMessage == WM_CLOSE)
            {
                impl->mContainer->OnDestroy();
                PostQuitMessage(0);

            }
            if(windowMessage == WM_DESTROY)
            {
                return false;
            }
            return DefWindowProc(hwnd, windowMessage, wp, lp);
        }

#pragma region Win32 creation utility methods

        WNDCLASSEX GenerateClassEx()
        {
            WNDCLASSEX wc;
            wc.cbSize = sizeof(wc);
            wc.style = 0;
            wc.lpfnWndProc = Implementation::MessageHandling;
            wc.cbClsExtra = 0;
            wc.cbWndExtra = 0;
            wc.hInstance = mInstance;
            wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
            wc.lpszMenuName = NULL;
            wc.lpszClassName = mClassName.c_str();
            wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
            return wc;
        };
        HMODULE GetModuleInstance()
        {
            return GetModuleHandle(NULL);
        };

        HWND GenerateWindow()
        {
            return CreateWindowEx(
                WS_EX_LEFT,
                mClassName.c_str(),
                NULL,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                NULL,
                NULL,
                mInstance,
                this);
        };

#pragma endregion

#pragma region class variables

        std::map<unsigned int, MESSAGE_HANDLER> mMessageHandlers;
        HMODULE mInstance;
        WNDCLASSEX mWndClassEx;
        HWND mWindowsHandler;
        WindowsGUI *mContainer;
        std::string mClassName{"tiny tina turner"};
#pragma endregion
    };

#pragma endregion

#pragma region WindowsGUI

    WindowsGUI::WindowsGUI() : mImplementation(std::make_unique<Implementation>(this)){

                               };

    WindowsGUI::~WindowsGUI(){};

    void WindowsGUI::OnAfterCreation()
    {
    }

    void WindowsGUI::OnDestroy()
    {
    }

    void WindowsGUI::Run()
    {
        mImplementation->Run();
    }

    void WindowsGUI::AddMessageHandler(uint16_t message, MESSAGE_HANDLER handler)
    {
        mImplementation->AddMessageHandler(message, handler);
    }

    void WindowsGUI::RemoveMessageHandler(uint16_t message)
    {
        mImplementation->RemoveMessageHandler(message);
    };
    void* WindowsGUI::GetWindowHandler()
    {
        return static_cast<void*>(mImplementation->mWindowsHandler);
    }
#pragma endregion
}