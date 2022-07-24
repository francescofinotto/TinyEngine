#include "../include/Game.h"
#include "WindowsOpenGLGUI.h"
#include "EngineOpenGL.h"
namespace Game
{
    Game::Game()
    {
        Platform::GUI::WindowsOpenGLGUI window{};
        window.MakeCurrent();
        Platform::Win::Initialize();
        window.Run();
    }
    Game::~Game()
    {
    }
}