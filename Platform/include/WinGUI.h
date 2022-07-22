#pragma once
#include <memory>
#include <map>
#include <vector>
#include <functional>
namespace Platform::GUI
{
    typedef std::function<void()> MESSAGE_HANDLER;
    class WinGUI
    {
    public:
        WinGUI();
        virtual ~WinGUI();

        virtual void Run();

        virtual void OnCreation();
        virtual void OnAfterCreation();
        virtual void OnUpdate();
        virtual void OnDestroy();

        void AddMessageHandler(uint16_t message,MESSAGE_HANDLER);
        void RemoveMessageHandler(uint16_t message);

    protected:

    private:

        class Win32Implementation;
        bool mReady = false;
        std::unique_ptr<Win32Implementation> mImplementation;
        uint32_t counter = 0;
    };
}