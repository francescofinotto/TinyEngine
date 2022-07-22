#include <map>
#include <windows.h>
#include "../include/WindowsGUI.h"

namespace Platform::GUI
{
#pragma region WindowsGUI::Implementation

    class WindowsGUI::Implementation
    {
    public:
        Implementation(){};
        ~Implementation(){};

    private:
#pragma region

        static LRESULT CALLBACK MessageHandling(HWND hwnd, UINT windowMessage, WPARAM wp, LPARAM lp)
        {
        }

#pragma endregion

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
            // wc.lpszClassName = mTitle.c_str();
            wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
            return wc;
        };
        HMODULE GetModuleInstance(){
            return GetModuleHandle(NULL);
        };

        HWND GenerateWindow()
        {
            return CreateWindowEx(
                WS_EX_LEFT,
                "mTitle.c_str()",
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

#pragma endregion
    };

#pragma endregion

#pragma region WindowsGUI

    WindowsGUI::WindowsGUI() : mImplementation(std::make_unique<Implementation>()){

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
    }

    void WindowsGUI::AddMessageHandler(uint16_t message, MESSAGE_HANDLER)
    {
    }

    void WindowsGUI::RemoveMessageHandler(uint16_t message){

    };

#pragma endregion
}