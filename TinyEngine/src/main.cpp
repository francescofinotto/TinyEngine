#include <iostream>
#include <memory>
#include "Game.h"

const unsigned int MOUSE_LEFT_BUTTON_DOWN = 513;

int main(int, char **)
{
    try
    {
        Game::Game window;
        window.Run();
    }
    catch (std::exception exc)
    {
        std::cout << exc.what() << std::endl;
    }
    // mainWindow.Run();
}
