#include "../include/Window.h"
#include <iostream>
namespace Platform
{
#ifdef WIN32
    class Window::WindowImplementation
    {
    public:

        WindowImplementation()
        {
            std::cout << "Window Implementation created" << std::endl;
        };

        ~WindowImplementation()
        {
            std::cout << "Window Implementation Destroied" << std::endl;
        };

    private:
    };
#endif
    Window::Window():windowInstance(std::make_unique<WindowImplementation>()){

    };

    Window::~Window(){

    };
}