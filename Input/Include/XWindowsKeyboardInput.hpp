#pragma once

#ifndef _INPUT_XWINDOWSKEYBOARDINPUT_HPP_
#define _INPUT_XWINDOWSKEYBOARDINPUT_HPP_

#include "KeyboardInputBase.hpp"

namespace Fnd
{
namespace Input
{

class XWindowsKeyboardInput:
    public KeyboardInputBase
{
    public:
        
        XWindowsKeyboardInput();
    
        void SetDisplay( void* display );
        
        bool Initialise();
        
        ~XWindowsKeyboardInput();
        
    protected:
        
        KeyboardInputBase::KeyboardState GetNextState();
        
    private:
        
        void* _display;
};

}
}

#endif
