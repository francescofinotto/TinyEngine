#pragma once
#include <memory>
namespace Platform
{
    class Window
    {

    public:

        Window();
        ~Window();
    
        void Run();

    private:
        /**
         * @brief Platform dependend window implementation
         */
        class WindowImplementation;
        std::unique_ptr<WindowImplementation> windowInstance;


    };
}
