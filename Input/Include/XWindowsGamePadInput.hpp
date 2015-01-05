#pragma once

#ifndef _INPUT_XWINDOWSGAMEPADINPUT_HPP_
#define _INPUT_XWINDOWSGAMEPADINPUT_HPP_

#include "GamePadInputBase.hpp"

namespace Fnd
{
namespace Input
{

class XWindowsGamePadInput:
    public GamePadInputBase
{
    public:
        
        XWindowsGamePadInput();
        
        bool Initialise();
        
        ~XWindowsGamePadInput();
        
    protected:
        
        GamePadInputBase::GamePadState GetNextState();
};

}
}

#endif
