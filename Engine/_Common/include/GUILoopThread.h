#pragma once
#include <functional>
#include <thread>
#include <stack>
#include <mutex>
#include <optional>
namespace Common::Threading
{

    class GUILoopThread
    {
    public:
        GUILoopThread(std::optional<std::function<void(void)>> updateAction);
        ~GUILoopThread();
        GUILoopThread(GUILoopThread &&other);
        GUILoopThread& operator=(GUILoopThread &&other); 
        void InvokeOnGUIThread(std::function<void(void)> action);
    private:
        void CheckForActionsAndExecute();
        std::stack<std::function<void(void)>> mActions;
        std::mutex mMutexActions;
        std::unique_ptr<std::thread> mLoopThread;
        bool isRunning;
    }; 

}