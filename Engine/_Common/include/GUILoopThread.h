#pragma once
#include <functional>
#include <thread>
#include <stack>
#include <mutex>

namespace Common::Threading
{

    class GUILoopThread
    {
    public:
        GUILoopThread(std::function<void(void)> updateAction);
        ~GUILoopThread();
        void InvokeOnGUIThread(std::function<void(void)> action);
    private:
        void CheckForActionsAndExecute();
        std::stack<std::function<void(void)>> mActions;
        std::mutex mMutexActions;
        std::thread loopThread;
        bool isRunning;
    };  

}