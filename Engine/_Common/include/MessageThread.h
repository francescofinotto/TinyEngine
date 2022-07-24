#pragma once
#include <functional>
#include <thread>
#include <stack>
namespace Common::Threading
{
    class MessageThread
    {
    public:
        MessageThread(std::function<void(void)> routine);
        ~MessageThread();
        void Execute(std::function<void(void)> action);
    private:
        std::stack<std::function<void(void)>> actions;
    };

}