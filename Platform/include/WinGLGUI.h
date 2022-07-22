#pragma once
#include <iostream>
#include "WinGUI.h"
namespace Platform::GUI
{

    class WinGLGUI : public WinGUI
    {
    public:
        WinGLGUI() = default;
        ~WinGLGUI() = default;
        virtual void OnUpdate() override {
            std::cout<<"GL Update"<<std::endl;
        }
    private:
    };

}