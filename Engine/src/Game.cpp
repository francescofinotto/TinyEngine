#include "../include/Game.h"
#include "WindowsOpenGLGUI.h"
namespace Game
{
    Game::Game()
    {
        Platform::GUI::WindowsOpenGLGUI window{};
        window.Run();
    }
    Game::~Game()
    {
    }
}