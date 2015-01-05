#include "../Include/XWindowsKeyboardInput.hpp"

#include <cstring>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <iostream>

using namespace Fnd::Input;

XWindowsKeyboardInput::XWindowsKeyboardInput():
    _display(nullptr)
{
}

void XWindowsKeyboardInput::SetDisplay( void* display )
{
    _display = display;
}

bool XWindowsKeyboardInput::Initialise()
{
    return _display != nullptr;
}

KeyboardInputBase::KeyboardState XWindowsKeyboardInput::GetNextState()
{
    KeyboardState state;
    memset( &state, 0, sizeof(KeyboardState) );

    const auto KeyIsDown = [this]( const char keys[32], const int xk_key ) -> bool
    {
        const int keycode = XKeysymToKeycode((Display*)_display, xk_key);
        
        return keys[ keycode / 8 ] & ( 0x1 << ( keycode % 8 ) );
    };
    
    char keys[32];
    
    XQueryKeymap((Display*)_display, keys);
    
    state.keys[Back_Key] = KeyIsDown(keys,0);
    state.keys[Tab_Key] = KeyIsDown(keys,XK_Tab);
    state.keys[Enter_Key] = KeyIsDown(keys,XK_Return);
    state.keys[Shift_Key] = KeyIsDown(keys,XK_Shift_L) || KeyIsDown(keys,XK_Shift_R);
    state.keys[Ctrl_Key] = KeyIsDown(keys,XK_Control_L ) || KeyIsDown(keys,XK_Control_R);
    state.keys[Alt_Key] = KeyIsDown(keys,XK_Alt_L) || KeyIsDown(keys,XK_Alt_R);
    state.keys[CapsLock_Key] = KeyIsDown(keys,XK_Caps_Lock);
    state.keys[Esc_Key] = KeyIsDown(keys,XK_Escape);
    state.keys[SpaceBar_Key] = KeyIsDown(keys,XK_space);
    state.keys[PageUp_Key] = KeyIsDown(keys,XK_Page_Up);
    state.keys[PageDown_Key] = KeyIsDown(keys,XK_Page_Down);
    state.keys[End_Key] = KeyIsDown(keys,XK_End);
    state.keys[Home_Key] = KeyIsDown(keys,XK_Home);
    state.keys[Left_Key] = KeyIsDown(keys,XK_Left);
    state.keys[Up_Key] = KeyIsDown(keys,XK_Up);
    state.keys[Right_Key] = KeyIsDown(keys,XK_Right);
    state.keys[Down_Key] = KeyIsDown(keys,XK_Down);
    state.keys[Insert_Key] = KeyIsDown(keys,XK_Insert);
    state.keys[Delete_Key] = KeyIsDown(keys,XK_Delete);
    for ( unsigned int i = 0; i < 10; ++i )
        state.keys[Zero_Key+i] = KeyIsDown(keys,XK_0+i);
    for ( unsigned int i = 0; i < 26; ++i )
        state.keys[A_Key+i] = KeyIsDown(keys,XK_A+i);
    state.keys[LeftWin_Key] = KeyIsDown(keys,0);
    state.keys[RightWin_Key] = KeyIsDown(keys,0);
    /*
        TODO: Numpad numbers and +*-/
    */
    state.keys[F1_Key] = KeyIsDown(keys,XK_F1);
    state.keys[F2_Key] = KeyIsDown(keys,XK_F2);
    state.keys[F3_Key] = KeyIsDown(keys,XK_F3);
    state.keys[F4_Key] = KeyIsDown(keys,XK_F4);
    state.keys[F5_Key] = KeyIsDown(keys,XK_F5);
    state.keys[F6_Key] = KeyIsDown(keys,XK_F6);
    state.keys[F7_Key] = KeyIsDown(keys,XK_F7);
    state.keys[F8_Key] = KeyIsDown(keys,XK_F8);
    state.keys[F9_Key] = KeyIsDown(keys,XK_F9);
    state.keys[F10_Key] = KeyIsDown(keys,XK_F10);
    state.keys[F11_Key] = KeyIsDown(keys,XK_F11);
    state.keys[F12_Key] = KeyIsDown(keys,XK_F12);
    state.keys[LeftShift_Key] = KeyIsDown(keys,XK_Shift_L);
    state.keys[RightShift_Key] = KeyIsDown(keys,XK_Shift_R);
    state.keys[LeftControl_Key] = KeyIsDown(keys,XK_Control_L);
    state.keys[RightControl_Key] = KeyIsDown(keys,XK_Control_R);
    state.keys[LeftAlt_Key] = KeyIsDown(keys,XK_Alt_L);
    state.keys[RightAlt_Key] = KeyIsDown(keys,XK_Alt_R);
    state.keys[SemiColon_Key] = KeyIsDown(keys,XK_semicolon);
    state.keys[Plus_Key] = KeyIsDown(keys,XK_plus);
    state.keys[Comma_Key] = KeyIsDown(keys,XK_comma);
    state.keys[Minus_Key] = KeyIsDown(keys,XK_minus);
    state.keys[Dot_Key] = KeyIsDown(keys,XK_period);
    state.keys[ForwardSlash_Key] = KeyIsDown(keys,XK_slash);
    state.keys[Hash_Key] = KeyIsDown(keys,0);
    state.keys[OpenSquareBracket_Key] = KeyIsDown(keys,0);
    state.keys[BackSlash_Key] = KeyIsDown(keys,XK_backslash);
    state.keys[Quote_Key] = KeyIsDown(keys,XK_quoteleft) || KeyIsDown(keys,XK_quoteright);
    
    return state;
}

XWindowsKeyboardInput::~XWindowsKeyboardInput()
{
}
