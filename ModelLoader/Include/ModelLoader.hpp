#pragma once

#ifndef _MODELLOADER_HPP_
#define _MODELLOADER_HPP_

#include <string>

namespace Fnd
{
namespace AssetManager
{
struct ModelData;
}
}

namespace Fnd
{
namespace ModelLoader
{

class ModelLoader
{
	public:
		static bool LoadModel(	const std::string& filename,
								float scale,	// scale all axes- can't see any situation where an (x,y,z) scale would be needed 
								unsigned int flags,
								Fnd::AssetManager::ModelData& model_data );
};

}
}

#endif