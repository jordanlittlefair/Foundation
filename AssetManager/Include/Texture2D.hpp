#pragma once

#ifndef _ASSETMANAGER_TEXTURE2DCONTENT_HPP_
#define _ASSETMANAGER_TEXTURE2DCONTENT_HPP_

#include "Asset.hpp"
#include "../../Utility/Include/Image.hpp"

namespace Fnd
{
namespace AssetManager
{

struct Texture2DData
{
	Fnd::Utility::Image image;

	enum Format
	{
		Format_R,
		Format_RG,
		Format_RGB,
		Format_RGBA
	};
	Format texture_format;

	enum Usage
	{
		Usage_Diffuse,
		Usage_NormalMap
	};
	Usage texture_usage;

	enum Flags
	{
		Flag_UseMipMaps = 1 << 0
	};
	unsigned int flags;
};

class Texture2D:
	public Fnd::AssetManager::Asset
{
	public:

		virtual bool Create( const Texture2DData& data ) = 0;

		virtual ~Texture2D();
};

}
}

#endif