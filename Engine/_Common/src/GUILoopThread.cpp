#include "../include/GUILoopThread.h"

namespace Common::Threading
{
    GUILoopThread::GUILoopThread(std::function<void(void)> updateAction):isRunning(true)
    {
        loopThread = std::thread([&](){
            while(isRunning) 
            {
                CheckForActionsAndExecute();
                updateAction();
            }
        });
    }

    GUILoopThread::~GUILoopThread()
    {
        isRunning = false;
        loopThread.join();
    }
        
    void GUILoopThread::InvokeOnGUIThread(std::function<void(void)> action)
    {
        std::lock_guard<std::mutex> lock(this->mMutexActions);
        mActions.push(action);
    }
    void GUILoopThread::CheckForActionsAndExecute()
    {
        std::lock_guard<std::mutex> lock(this->mMutexActions);
        while (!mActions.empty())
        {
            auto& action = mActions.top();
            action();
            mActions.pop();
        }
        
    }
}