#include "../Include/MessageBox.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace Fnd::Utility;

void Fnd::Utility::BlockingMessageBox( const std::string& title, const std::string& message )
{
#ifdef _WIN32
	MessageBox( nullptr, message.c_str(), title.c_str(), MB_OK );
#endif
}