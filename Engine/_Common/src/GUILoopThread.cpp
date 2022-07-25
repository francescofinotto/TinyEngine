#include "../include/GUILoopThread.h"

namespace Common::Threading
{
    GUILoopThread::GUILoopThread(std::optional<std::function<void(void)>> updateAction):isRunning(true)
    {
        if(updateAction.has_value())
        mLoopThread = std::make_unique<std::thread>([&](){
            while(isRunning) 
            {
                CheckForActionsAndExecute();
                updateAction.value();
            }
        });
    }
    GUILoopThread::GUILoopThread(GUILoopThread&& other)
    {
        mLoopThread = std::move(other.mLoopThread);
        mActions = std::move(other.mActions);

    }
    GUILoopThread& GUILoopThread::operator=(GUILoopThread &&other)
    {
        mLoopThread = std::move(other.mLoopThread);
        mActions = std::move(other.mActions);
        return *this;
    }
      
    GUILoopThread::~GUILoopThread()
    {
        isRunning = false;
        mLoopThread->join();
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