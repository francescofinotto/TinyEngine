#pragma once
#include <functional>
#include <thread>
#include <stack>
#include <mutex>
#include <optional>
namespace Common::Threading
{

    class GUILoopThread final
    {
    public:
        GUILoopThread(std::function<void(void)> updateAction);
        ~GUILoopThread();

        void InvokeOnGUIThread(std::function<void(void)> action);
    private:
        void UpdateLoop();
        void CheckForActionsAndExecute();
        std::stack<std::function<void(void)>> mActions;
        std::function<void(void)> updateAction;
        std::mutex mMutexActions;
        std::thread mLoopThread;
        bool isRunning;
    };  

}