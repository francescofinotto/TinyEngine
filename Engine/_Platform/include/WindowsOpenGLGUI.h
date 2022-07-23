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
        typedef void* GL_CONTEXT;
    protected:
        virtual void OnRender();
    private:
        void Swap();
        GL_CONTEXT mGlContext;

    };       

} 