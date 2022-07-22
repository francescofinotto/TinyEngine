#include "../include/WinGUI.h"
#include <windows.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <utility>
namespace Platform::GUI
{
    class WinGUI::Win32Implementation
    {

    public:
        /**
         * @brief Construct a new Win32 Implementation object
         * @param container, winGUI pointer
         * @param title Text on top of the window
         */
        Win32Implementation(WinGUI* container,std::string title = "TinyEngine")
            : mTitle(title), mInstance(GetModuleHandle(NULL)), mWndClassEx(GenWNDCLASSEX()), 
                mMessgeHandlers(std::make_shared<std::unordered_map<unsigned int,MESSAGE_HANDLER>>()),
                mParent(container)
        {


            if (!RegisterClassEx(&mWndClassEx))
            {
                throw std::runtime_error("Cannot Register Window Class");
            }


            if ((mWindowHandle = CreateWindowGetHandler()) == nullptr)
            {
                throw std::runtime_error("Cannot create Window");
            }


            SetTimer(mWindowHandle,NULL,1000/60,NULL);
            SetWindowText(mWindowHandle, mTitle.c_str());


        };

        void MessageHandlingRoutine(const unsigned int message){


            auto value = mMessgeHandlers->find(static_cast<unsigned int>(message));
            if (value != mMessgeHandlers->end())
            {
                value->second();
            }


        }

        ~Win32Implementation()
        {


            mParent = nullptr;
            DestroyWindow(mWindowHandle);
            std::cout<<"Implementation destroied"<<std::endl;


        };

        void Run()
        {


            MSG msg;

            ShowWindow(static_cast<HWND>(mWindowHandle), SW_NORMAL);
            UpdateWindow(static_cast<HWND>(mWindowHandle));
            mParent->OnAfterCreation();

            while (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }


        }


        static bool SetWindowInstanceToWindowLongPtr(Win32Implementation *windowPtr, HWND &hwnd, LPARAM &lp)
        {


            auto temp = static_cast<Win32Implementation *>(reinterpret_cast<CREATESTRUCT *>(lp)->lpCreateParams);
            windowPtr = dynamic_cast<Win32Implementation *>(temp);
            if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowPtr)))
            {
                return true;
            }
            return false;


        };


        static LRESULT CALLBACK MessageRoutine(HWND hwnd, UINT windowMessage, WPARAM wp, LPARAM lp)
        {


            Win32Implementation *windowPtr = nullptr;
            if (windowMessage == WM_NCCREATE)
            {


                SetLastError(0);
                if (!SetWindowInstanceToWindowLongPtr(windowPtr, hwnd, lp))
                {
                    if (GetLastError() != 0)
                        return FALSE;
                }

                
            }
            else
            {
                windowPtr = reinterpret_cast<Win32Implementation *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            }


            if (windowPtr != nullptr)
            {
                windowPtr->MessageHandlingRoutine(windowMessage);
                // windowPtr->mParent->OnUpdate();
            }


            return DefWindowProc(hwnd, windowMessage, wp, lp);


        };


        HWND CreateWindowGetHandler()
        {
            return CreateWindowEx(
                WS_EX_LEFT,
                mTitle.c_str(),
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
        }


        WNDCLASSEX GenWNDCLASSEX()
        {
            WNDCLASSEX wc;
            wc.cbSize = sizeof(wc);
            wc.style = 0;
            wc.lpfnWndProc = Win32Implementation::MessageRoutine;
            wc.cbClsExtra = 0;
            wc.cbWndExtra = 0;
            wc.hInstance = mInstance;
            wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
            wc.lpszMenuName = NULL;
            wc.lpszClassName = mTitle.c_str();
            wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
            return wc;
        };

        std::shared_ptr<std::unordered_map<unsigned int, MESSAGE_HANDLER>> mMessgeHandlers;
        std::string mTitle;
        HMODULE mInstance;
        WNDCLASSEX mWndClassEx;
        HWND mWindowHandle;
        WinGUI* mParent;
    };








    WinGUI::WinGUI()
    {
        OnCreation();
        mImplementation = std::make_unique<Win32Implementation>(this,"titolone");
        mImplementation->mMessgeHandlers->insert(std::make_pair<unsigned int,MESSAGE_HANDLER>(
            WM_TIMER,[&](){this->OnUpdate();}
        ));
        mReady = true;
    }

    WinGUI::~WinGUI()
    {
    }




    void WinGUI::Run()
    {
        mImplementation->Run();
    }

    void WinGUI::OnCreation()
    {
    }

    void WinGUI::OnAfterCreation()
    {
        std::cout<<"After Creation"<<std::endl;
    }

    void WinGUI::OnUpdate()
    {
        std::cout<<"On Update: "<<counter++<<std::endl;
    }

    void WinGUI::OnDestroy()
    {
        std::cout<<"On Destroy"<<std::endl;
    }
}