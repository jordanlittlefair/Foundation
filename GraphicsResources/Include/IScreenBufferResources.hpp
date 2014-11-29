#pragma once

#ifndef _GRAPHICSRESOURCES_ISCREENBUFFERRESOURCES_HPP_
#define	_GRAPHICSRESOURCES_ISCREENBUFFERRESOURCES_HPP_

namespace Fnd
{
namespace GraphicsResources
{

class IScreenBufferResources
{
	public:
		
		virtual bool Initialise( unsigned int width, unsigned int height ) = 0;
		
		virtual bool Resize( unsigned int width, unsigned int height ) = 0;
		
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		virtual ~IScreenBufferResources(){};
};

}
}
#endif