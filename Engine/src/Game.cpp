#include "../include/Game.h"
#include "WindowsOpenGLGUI.h"
#include "EngineOpenGL.h"
namespace Game
{
    Game::Game()
    {

    }
    Game::~Game()
    {
    }
    void Game::OnAfterCreation()
    {
        WindowsOpenGLGUI::OnAfterCreation();
        MakeCurrent();
        Platform::Win::Initialize();
    }
}