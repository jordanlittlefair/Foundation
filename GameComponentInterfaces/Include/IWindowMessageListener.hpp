#pragma once

#ifndef _GAMECOMPONENTINTERFACES_IWINDOWMESSAGELISTENER_HPP_
#define _GAMECOMPONENTINTERFACES_IWINDOWMESSAGELISTENER_HPP_

namespace Fnd
{
namespace GameComponentInterfaces
{

/**
	Interface class inherited by Game class.
	Methods are called when the Window's state has changed.
*/
class IWindowMessageListener
{
	public:

		/**
			Handle Game events when the Window is closed.
		*/
		virtual void OnWindowClose() = 0;

		/**
			Handle Game events when the Window is resized.
		*/
		virtual void OnWindowResize( unsigned int width, unsigned int height ) = 0;

		/**
			Called when the Window is activated.
		*/
		virtual void OnWindowActivate() = 0;

		/**
			Called when the Window is deactivated.
		*/
		virtual void OnWindowDeactivate() = 0;

		virtual bool VRIsEnabled() const = 0;
};

}
}

#endif