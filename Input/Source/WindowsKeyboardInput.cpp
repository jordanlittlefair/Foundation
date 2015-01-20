#include "../Include/WindowsKeyboardInput.hpp"

using namespace Fnd::Input;

WindowsKeyboardInput::WindowsKeyboardInput():
	_window(nullptr),
	_direct_input(nullptr),
	_keyboard(nullptr)
{
}

void WindowsKeyboardInput::SetWindow( HWND window )
{
	_window = window;
}

void WindowsKeyboardInput::SetDirectInputDevice( IDirectInput8* direct_input )
{
	_direct_input = direct_input;
}

bool WindowsKeyboardInput::Initialise()
{
	if ( !_window ) 
	{
		return false;
	}

	if ( !_direct_input ) 
	{
		return false;
	}

	if ( FAILED( _direct_input->CreateDevice(	GUID_SysKeyboard, 
												&_keyboard,
												0 ) ) )
	{
		return false;
	}

	// set keyboard format and stuff
	if ( FAILED( _keyboard->SetDataFormat( &c_dfDIKeyboard ) ) ) 
	{
		return false;
	}
	if ( FAILED( _keyboard->SetCooperativeLevel( _window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		return false;
	}

	_keyboard->Acquire();

	return true;
}

WindowsKeyboardInput::~WindowsKeyboardInput()
{
	if ( _keyboard )
	{ 
		_keyboard->Unacquire();
		_keyboard->Release();
	}
}

KeyboardInputBase::KeyboardState WindowsKeyboardInput::GetNextState()
{
	KeyboardInputBase::KeyboardState state;
	memset( &state, 0, sizeof(state) );

	const int kb_state_size = 256;
	unsigned char kb_state[kb_state_size] = {0};
	
	_keyboard->Acquire();
	_keyboard->GetDeviceState( kb_state_size, kb_state );

	auto keyDown = [&,this]( const unsigned int key )
	{
		return ( kb_state[key] & 0x80 ) != 0;
	};

	state.keys[Back_Key] = keyDown(DIK_BACK);
    state.keys[Tab_Key] = keyDown(DIK_TAB);
    state.keys[Enter_Key] = keyDown(DIK_RETURN);
    state.keys[Shift_Key] = keyDown(DIK_LSHIFT) | keyDown(DIK_RSHIFT);
    state.keys[Ctrl_Key] = keyDown(DIK_LCONTROL) | keyDown(DIK_RCONTROL);
    state.keys[Alt_Key] = keyDown(DIK_LALT) | keyDown(DIK_RALT);
    state.keys[CapsLock_Key] = keyDown(DIK_CAPSLOCK);
    state.keys[Esc_Key] = keyDown(DIK_ESCAPE);
    state.keys[SpaceBar_Key] = keyDown(DIK_SPACE);
    state.keys[PageUp_Key] = keyDown(DIK_PGUP);
    state.keys[PageDown_Key] = keyDown(DIK_PGDN);
    state.keys[End_Key] = keyDown(DIK_END);
    state.keys[Home_Key] = keyDown(DIK_HOME);
    state.keys[Left_Key] = keyDown(DIK_LEFT);
    state.keys[Up_Key] = keyDown(DIK_UP);
    state.keys[Right_Key] = keyDown(DIK_RIGHT);
    state.keys[Down_Key] = keyDown(DIK_DOWN);
    state.keys[Insert_Key] = keyDown(DIK_INSERT);
    state.keys[Delete_Key] = keyDown(DIK_DELETE);
    state.keys[Zero_Key] = keyDown(DIK_0);
    state.keys[One_Key] = keyDown(DIK_1);
    state.keys[Two_Key] = keyDown(DIK_2);
    state.keys[Three_Key] = keyDown(DIK_3);
    state.keys[Four_Key] = keyDown(DIK_4);
    state.keys[Five_Key] = keyDown(DIK_5);
    state.keys[Six_Key] = keyDown(DIK_6);
    state.keys[Seven_Key] = keyDown(DIK_7);
    state.keys[Eight_Key] = keyDown(DIK_8);
    state.keys[Nine_Key] = keyDown(DIK_9);
    state.keys[A_Key] = keyDown(DIK_A);
    state.keys[B_Key] = keyDown(DIK_B);
    state.keys[C_Key] = keyDown(DIK_C);
    state.keys[D_Key] = keyDown(DIK_D);
    state.keys[E_Key] = keyDown(DIK_E);
    state.keys[F_Key] = keyDown(DIK_F);
    state.keys[G_Key] = keyDown(DIK_G);
    state.keys[H_Key] = keyDown(DIK_H);
    state.keys[I_Key] = keyDown(DIK_I);
    state.keys[J_Key] = keyDown(DIK_J);
    state.keys[K_Key] = keyDown(DIK_K);
    state.keys[L_Key] = keyDown(DIK_L);
    state.keys[M_Key] = keyDown(DIK_M);
    state.keys[N_Key] = keyDown(DIK_N);
    state.keys[O_Key] = keyDown(DIK_O);
    state.keys[P_Key] = keyDown(DIK_P);
    state.keys[Q_Key] = keyDown(DIK_Q);
    state.keys[R_Key] = keyDown(DIK_R);
    state.keys[S_Key] = keyDown(DIK_S);
    state.keys[T_Key] = keyDown(DIK_T);
    state.keys[U_Key] = keyDown(DIK_U);
    state.keys[V_Key] = keyDown(DIK_V);
    state.keys[W_Key] = keyDown(DIK_W);
    state.keys[X_Key] = keyDown(DIK_X);
    state.keys[Y_Key] = keyDown(DIK_Y);
    state.keys[Z_Key] = keyDown(DIK_Z);
    state.keys[LeftWin_Key] = keyDown(DIK_LWIN);
    state.keys[RightWin_Key] = keyDown(DIK_RWIN);
    state.keys[ZeroNumPad_Key] = keyDown(DIK_NUMPAD0);
    state.keys[OneNumpad_Key] = keyDown(DIK_NUMPAD1);
    state.keys[TwoNumPad_Key] = keyDown(DIK_NUMPAD2);
    state.keys[ThreeNumPad_Key] = keyDown(DIK_NUMPAD3);
    state.keys[FourNumPad_Key] = keyDown(DIK_NUMPAD4);
    state.keys[FiveNumPad_Key] = keyDown(DIK_NUMPAD5);
    state.keys[SixNumPad_Key] = keyDown(DIK_NUMPAD6);
    state.keys[SevenNumPad_Key] = keyDown(DIK_NUMPAD7);
    state.keys[EightNumPad_Key] = keyDown(DIK_NUMPAD8);
    state.keys[NineNumPad_Key] = keyDown(DIK_NUMPAD9);
    state.keys[Multiply_Key] = keyDown(DIK_MULTIPLY);
    state.keys[Add_Key] = keyDown(DIK_ADD);
    state.keys[Seperator_Key] = false;	// ?
    state.keys[Subtract_Key] = keyDown(DIK_SUBTRACT);
    state.keys[Decimal_Key] = keyDown(DIK_DECIMAL);
    state.keys[Divide_Key] = keyDown(DIK_DIVIDE);
    state.keys[F1_Key] = keyDown(DIK_F1);
    state.keys[F2_Key] = keyDown(DIK_F2);
    state.keys[F3_Key] = keyDown(DIK_F3);
    state.keys[F4_Key] = keyDown(DIK_F4);
    state.keys[F5_Key] = keyDown(DIK_F5);
    state.keys[F6_Key] = keyDown(DIK_F6);
    state.keys[F7_Key] = keyDown(DIK_F7);
    state.keys[F8_Key] = keyDown(DIK_F8);
    state.keys[F9_Key] = keyDown(DIK_F9);
    state.keys[F10_Key] = keyDown(DIK_F10);
    state.keys[F11_Key] = keyDown(DIK_F11);
    state.keys[F12_Key] = keyDown(DIK_F12);
    state.keys[LeftShift_Key] = keyDown(DIK_LSHIFT);
    state.keys[RightShift_Key] = keyDown(DIK_RSHIFT);
    state.keys[LeftControl_Key] = keyDown(DIK_LCONTROL);
    state.keys[RightControl_Key] = keyDown(DIK_RCONTROL);
    state.keys[LeftAlt_Key] = keyDown(DIK_LALT);
    state.keys[RightAlt_Key] = keyDown(DIK_RALT);
    state.keys[SemiColon_Key] = keyDown(DIK_SEMICOLON);
    state.keys[Plus_Key] = keyDown(DIK_EQUALS);
    state.keys[Comma_Key] = keyDown(DIK_COMMA);
    state.keys[Minus_Key] = keyDown(DIK_MINUS);
    state.keys[Dot_Key] = keyDown(DIK_PERIOD);
    state.keys[ForwardSlash_Key] = keyDown(DIK_SLASH);
    state.keys[Hash_Key] = false;	// ?
    state.keys[OpenSquareBracket_Key] = keyDown(DIK_LBRACKET);
    state.keys[BackSlash_Key] = keyDown(DIK_BACKSLASH);
    state.keys[CloseSquareBracket_Key] = keyDown(DIK_RBRACKET);
	state.keys[Quote_Key] = keyDown(DIK_APOSTROPHE);
	
	return state;
}