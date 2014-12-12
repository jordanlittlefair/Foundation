#pragma once

#ifndef _INPUT_MOUSEINPUTBASE_HPP_
#define _INPUT_MOUSEINPUTBASE_HPP_

#include "IMouseInput.hpp"

namespace Fnd
{
namespace Input
{

class MouseInputBase:
    public IMouseInput
{
    public:
    
        MouseInputState();
    
        bool IsDownLeft() const;

        bool IsDownRight() const;

        bool IsDownMiddle() const;

        bool IsUpLeft() const;

        bool IsUpRight() const;

        bool IsUpMiddle() const;

        bool IsPressedLeft() const;

        bool IsPressedRight() const;

        bool IsPressedMiddle() const;

        bool IsReleasedLeft() const;

        bool IsReleasedRight() const;

        bool IsReleasedMiddle() const;

        int GetMouseDeltaX() const;

        int GetMouseDeltaY() const;

        int GetMouseDeltaWheel() const;
    
        void Update();
    
    protected:
    
        struct MouseState
        {
            bool left_button;
            bool right_button;
            bool middle_button;
            
            int delta_x;
            int delta_y;
            int delta_wheel;
        };
    
        virtual MouseState GetNextState() = 0;
    
    private:
    
        MouseState _mouse_state[2];
    
        unsigned int _current_state;
        unsigned int _previous_state;
};

}
}

#endif
