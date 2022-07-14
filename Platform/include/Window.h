#pragma once
#include <memory>
#include <string>
namespace Platform
{

    class Window
    {

    public:
        Window(std::string title  = std::string("TinyEngine"));
        ~Window();

        void Run();
        /**
         * @brief Platform dependend window implementation
         */

    private:
        class WindowImplementation;
        std::unique_ptr<WindowImplementation> windowInstance;
    };

}
