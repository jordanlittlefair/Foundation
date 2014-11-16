#pragma once

#ifndef _MESSAGEBOX_HPP_
#define _MESSAGEBOX_HPP_

#include <string>

namespace Fnd
{
namespace Utility
{
	/**
		Display a basic message box.
		The message box has no options, only a button to continue/close.
		@param title The title of the message box.
		@param message The message inside the message box.
	*/
	void BlockingMessageBox( const std::string& title, const std::string& message );
}
}

#endif