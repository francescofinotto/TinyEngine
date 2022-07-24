#pragma once
#include <thread>
#include <memory>
#include "WindowsGUI.h"
namespace Platform::GUI
{
    class WindowsOpenGLGUI : public WindowsGUI
    {
    public:
        WindowsOpenGLGUI();
        ~WindowsOpenGLGUI();
        virtual void OnAfterCreation() override;
        virtual void OnDestroy() override;
        virtual void Run() override;
        void Swap();
        void MakeCurrent();
        typedef void* GL_CONTEXT;
    protected:
        virtual void OnRender();
        virtual void OnResize(void* wp,void* lp);
        void SetupMessageHandlers();
    private:
        GL_CONTEXT mGlContext;
        std::thread renderThread;
        bool isRunning = true;
    };
           

} 