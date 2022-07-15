#include <iostream>
#include "Win32Gui.h"
#include <memory>
class WinEvents : public Platform::GUI::WindowEventHandler
{
public:
    WinEvents(){};
    virtual ~WinEvents() override = default;
    virtual void OnCreate(){};
    virtual void OnAfterCreation(){};
    virtual void OnUpdate(){};
    virtual void OnDestroy(){};
    virtual void OnResize(uint16_t width, uint16_t height){};
};

int main(int, char **)
{
    Platform::GUI::Win32Gui window("Titolone", std::make_unique<WinEvents>());
    window.Run();
    // mainWindow.Run();
}
