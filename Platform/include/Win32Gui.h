#pragma once
#include <memory>
#include <string>
namespace Platform::GUI
{

    /**
     * @brief Extend this to implement Event handling for Win32Gui
     *
     */
    class WindowEventHandler
    {
    public:
        WindowEventHandler() = default;
        virtual ~WindowEventHandler(){};
        virtual void OnCreate() = 0;
        virtual void OnAfterCreation() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnDestroy() = 0;
        virtual void OnResize(uint16_t width, uint16_t height) = 0;
    };

    /**
     * @brief Win 32 Gui container to handle a Win 32 window.
     */
    class Win32Gui
    {
    public:
        Win32Gui(std::string title, std::unique_ptr<WindowEventHandler> eventHandler);
        ~Win32Gui();
        void Run();

    private:
        class WindowImplementation;
        std::unique_ptr<WindowImplementation> mImplementation;
        std::unique_ptr<WindowEventHandler> mEventHandler;
        std::string mTitle;
    };

}
