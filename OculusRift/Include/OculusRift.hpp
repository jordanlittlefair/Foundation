#pragma once

#ifndef _OCULUSRIFT_OCULUSRIFT_HPP_
#define _OCULUSRIFT_OCULUSRIFT_HPP_

#include "../../GameComponentInterfaces/Include/IWindow.hpp"
#include "../../GameComponentInterfaces/Include/IGraphics.hpp"

#include <Windows.h>
#include <memory>

namespace Fnd
{
namespace OculusRift
{

struct OculusData;

class OculusRift
{
	public:

		OculusRift();

		void SetWindow( Fnd::GameComponentInterfaces::IWindow* window );

		void SetGraphics( Fnd::GameComponentInterfaces::IGraphics* graphics );

		bool InitialiseStart();

		bool Initialise();

		void BeginRender( unsigned int frame_index );

		void FinishRender();

		unsigned int GetTextureWidth();
		unsigned int GetTextureHeight();
		unsigned int GetRightEyeTextureWidth();
		unsigned int GetRightEyeTextureHeight();
		unsigned int GetLeftEyeTextureWidth();
		unsigned int GetLeftEyeTextureHeight();

		~OculusRift();

	private:

		Fnd::GameComponentInterfaces::IWindow* _window;
		Fnd::GameComponentInterfaces::IGraphics* _graphics;
		
		std::unique_ptr<OculusData> _oculus_data;
};

}
}

#endif