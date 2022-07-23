#pragma once
#include <memory>
#include <string>
#include <functional>

namespace Platform::GUI
{

    class WindowsGUI
    {
    public:

        typedef std::function<void(void)> MESSAGE_HANDLER;

        WindowsGUI();
        ~WindowsGUI();

        virtual void OnAfterCreation();
        virtual void OnDestroy();
        void Run();
        void AddMessageHandler(uint16_t message,MESSAGE_HANDLER);
        void RemoveMessageHandler(uint16_t message);
    protected:
        void* GetWindowHandler();
    private:
        
        class Implementation;
        std::unique_ptr<Implementation> mImplementation;

    };
    

}