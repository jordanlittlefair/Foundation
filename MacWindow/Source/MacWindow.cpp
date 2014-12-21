#include "../Include/MacWindow.hpp"

using namespace Fnd::MacWindow;

MacWindow::MacWindow()
{
}

void MacWindow::SetWindowTitle( const std::string& title )
{
}

void MacWindow::SetWindowSize( unsigned int width, unsigned int height )
{
}

void MacWindow::SetWindowResizable( bool resizable )
{
}

void MacWindow::SetWindowFullscreen( bool fullscreen )
{
}

void MacWindow::SetWindowMessageListener( Fnd::GameComponentInterfaces::IWindowMessageListener* game )
{
}

bool MacWindow::Initialise()
{
    return true;
}

void* MacWindow::GetHWND() const
{
    return nullptr;
}

void* MacWindow::GetHDC() const
{
    return nullptr;
}

void* MacWindow::GetXWindowsDisplay() const
{
    return nullptr;
}

unsigned long MacWindow::GetXWindowsWindow() const
{
    return 0;
}

void MacWindow::Show()
{
}

bool MacWindow::IsOpen() const
{
    return true;
}

bool MacWindow::IsActive() const
{
    return true;
}

void MacWindow::HandleWindowMessages()
{
}

void MacWindow::ShowCursor( bool show )
{
}

void MacWindow::CloseWindow()
{
}

MacWindow::~MacWindow()
{
}