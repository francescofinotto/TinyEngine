#include <iostream>
#include "WindowsGUI.h"
#include <memory>
// class WinEvents : public Platform::GUI::WindowEventHandler
// {
// public:
//     WinEvents(){};
//     virtual ~WinEvents() override = default;
//     virtual void OnCreate(){};
//     virtual void OnAfterCreation(){};
//     virtual void OnUpdate(){};
//     virtual void OnDestroy(){};
//     virtual void OnResize(uint16_t width, uint16_t height){};
// };

const unsigned int MOUSE_LEFT_BUTTON_DOWN = 513;

int main(int, char **)
{
    try
    {
        Platform::GUI::WindowsGUI window;
        window.AddMessageHandler(MOUSE_LEFT_BUTTON_DOWN,[&](){
            
        });
        window.Run();
    }
    catch (std::exception exc)
    {
        std::cout << exc.what() << std::endl;
    }
    // mainWindow.Run();
}
