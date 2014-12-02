#pragma once

#ifndef _GRAPHICSRESOURCES_SCREENBUFFERRESOURCESBASE_HPP_
#define	_GRAPHICSRESOURCES_SCREENBUFFERRESOURCESBASE_HPP_

#include "../../Math/Include/Math.hpp"

namespace Fnd
{
namespace GraphicsResources
{

class ScreenBufferResourcesBase
{
	public:

		ScreenBufferResourcesBase();
		
		bool Initialise( unsigned int width, unsigned int height );
		
		bool Resize( unsigned int width, unsigned int height );
		
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		
		virtual ~ScreenBufferResourcesBase();

		struct PositionReconstruction_cbuffer
		{
			Fnd::Math::Vector2 screen_size;
			float aspect_ratio;
			float tan_half_fov_y;
		};
		PositionReconstruction_cbuffer GetPositionReconstructionData() const;
		bool UpdatePositionReconstructionData( const PositionReconstruction_cbuffer& data );

	protected:

		virtual void OnUpdatePositionReconstructionData( const PositionReconstruction_cbuffer& data ) = 0;

		virtual void ReleaseResources() = 0;
		virtual bool CreateResources() = 0;

	private:

		unsigned int _width;
		unsigned int _height;

		PositionReconstruction_cbuffer _position_reconstruction_data;
};

}
}
#endif