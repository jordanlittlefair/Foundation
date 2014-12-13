#pragma once

#ifndef _INPUT_MACKEYBOARDINPUT_HPP_
#define _INPUT_MACKEYBOARDINPUT_HPP_

#include "KeyboardInputBase.hpp"

namespace Fnd
{
namespace Input
{

class MacKeyboardInput:
    public KeyboardInputBase
{
    public:
        
        MacKeyboardInput();
        
        bool Initialise();
        
        ~MacKeyboardInput();
        
    protected:
        
        KeyboardInputBase::KeyboardState GetNextState();
        
    private:
        
        // TODO
};

}
}

#endif