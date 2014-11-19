#pragma once

#ifndef _GAMECOMPONENTINTERFACES_IGRAPHICSMESSAGELISTENER_HPP_
#define _GAMECOMPONENTINTERFACES_IGRAPHICSMESSAGELISTENER_HPP_

namespace Fnd
{
namespace GameComponentInterfaces
{

/*
	Interface class inherited by Game class.
	Allows the Graphics to access data in the Game.
*/
class IGraphicsMessageListener
{
	public:

		/**
			Get a pointer to the HWND window handle.
			@note Only implemented for Win32.\n
			All other implementations return null.
			@return Returns the window handle.
		*/
		virtual void* GetHWND() const = 0;

		/**
			Get a pointer to the HCD device context handle.
			@note Only implemented for Win32.\n
			All other implementations return null.
			@return Returns the device context handle.
		*/
		virtual void* GetHDC() const = 0;

		virtual bool GetVRTextureDimensions( unsigned int& width, unsigned int& height ) = 0;
};

}
}

#endif