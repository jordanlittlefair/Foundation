#pragma once

#ifndef _UTILITY_MIPMAPGENERATOR_HPP_
#define _UTILITY_MIPMAPGENERATOR_HPP_

#include "Image.hpp"

#include <vector>

namespace Fnd
{
namespace Utility
{

class MipMapGenerator
{
	public:

		static unsigned int GetNumMipLevels( const Image& image );

		static unsigned int GetNumMipLevels( unsigned int width, unsigned int height );

		static std::vector<Image> GenerateMipMaps( const Image& image, unsigned int max_mip_level = ~0 );

		static char Sample( const Image& image, float x, float y, char channel );
};

}
}

#endif