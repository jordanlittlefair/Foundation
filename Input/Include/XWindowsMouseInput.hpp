#pragma once

#ifndef _INPUT_XWINDOWSMOUSEINPUT_HPP_
#define _INPUT_XWINDOWSMOUSEINPUT_HPP_

#include "MouseInputBase.hpp"

namespace Fnd
{
namespace Input
{

class XWindowsMouseInput:
    public MouseInputBase
{
    public:
        
        XWindowsMouseInput();
        
        bool Initialise();
        
        ~XWindowsMouseInput();
        
    protected:
        
        MouseInputBase::MouseState GetNextState();
};

}
}

#endif
