#include "../include/GUILoopThread.h"
#include <iostream>
namespace Common::Threading
{
    GUILoopThread::GUILoopThread(std::function<void(void)>updateAction)
        :updateAction{updateAction},isRunning{true}, mLoopThread{std::thread(std::bind(&GUILoopThread::UpdateLoop,this))}
    {}

    GUILoopThread::~GUILoopThread()
    {
        isRunning = false;
        mLoopThread.join();
    }
        
    void GUILoopThread::InvokeOnGUIThread(std::function<void(void)> action)
    {
        std::lock_guard<std::mutex> lock(mMutexActions);
        mActions.push(action);
    }
    void GUILoopThread::CheckForActionsAndExecute()
    {
        std::lock_guard<std::mutex> lock(mMutexActions);
        while (!mActions.empty())
        {
            auto& action = mActions.top();
            action();
            mActions.pop();
        }
        
    }
    void GUILoopThread::UpdateLoop()
    {
        while(isRunning) 
        {
            CheckForActionsAndExecute();
            updateAction();
        }
        std::cout<<"Exit thread"<<std::this_thread::get_id<<std::endl;
    }
     
}