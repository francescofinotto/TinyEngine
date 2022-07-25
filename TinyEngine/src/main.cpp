#include <iostream>
#include <memory>
#include "Game.h"
using namespace Common::Threading;
const unsigned int MOUSE_LEFT_BUTTON_DOWN = 513;

int main(int, char **)
{
    try
    {
        {

            GUILoopThread t1 = GUILoopThread(
                []()
                {std::cout<<"Thread"<<std::endl; std::this_thread::sleep_for(std::chrono::duration<double,std::milli>(100)); });
            t1.InvokeOnGUIThread([&]()
                                 { std::cout << "Endless run" << std::endl; });
            
            GUILoopThread t2 = GUILoopThread(
                []()
                {std::cout<<"Thread2"<<std::endl; std::this_thread::sleep_for(std::chrono::duration<double,std::milli>(100)); });
            t1.InvokeOnGUIThread([&]()
                                 { std::cout << "Endless run" << std::endl; });
            
            std::this_thread::sleep_for(std::chrono::duration<double,std::milli>(1500));

        }
            Game::Game window;
            window.Run();
    }
    catch (std::exception exc)
    {
        std::cout << exc.what() << std::endl;
    }
    // mainWindow.Run();
}
