#pragma once
#include "WindowsOpenGLGUI.h"
namespace Game
{
    class Game: public Platform::GUI::WindowsOpenGLGUI
    {
    public:
        Game();
        ~Game();
        virtual void OnAfterCreation() override;
    private:
    };
    
    
}