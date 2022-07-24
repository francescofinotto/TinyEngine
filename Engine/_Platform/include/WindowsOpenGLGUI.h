#pragma once
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
        void Swap();
        void MakeCurrent();
        typedef void* GL_CONTEXT;
    protected:
        virtual void OnRender();
        virtual void OnResize(void* wp,void* lp);
    private:
        GL_CONTEXT mGlContext;

    };       

} 