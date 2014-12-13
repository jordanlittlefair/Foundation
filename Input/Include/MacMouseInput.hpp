#pragma once

#ifndef _INPUT_MACMOUSEINPUT_HPP_
#define _INPUT_MACMOUSEINPUT_HPP_

#include "MouseInputBase.hpp"

namespace Fnd
{
namespace Input
{

class MacMouseInput:
    public MouseInputBase
{
    public:
        
        MacMouseInput();
        
        bool Initialise();
        
        ~MacMouseInput();
        
    protected:
        
        MouseInputBase::MouseState GetNextState();
        
    private:
    
        // TODO
};

}
}

#endif