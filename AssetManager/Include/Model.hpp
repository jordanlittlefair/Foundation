#pragma once

#ifndef _ASSETMANAGER_MODEL_HPP_
#define _ASSETMANAGER_MODEL_HPP_

#include "Asset.hpp"
#include "../../Math/Include/Math.hpp"
#include <vector>

namespace Fnd
{
namespace AssetManager
{

struct ModelData
{
	struct Mesh
	{
		struct Vertex
		{
			Fnd::Math::Vector3 position;
			Fnd::Math::Vector3 normal;
			Fnd::Math::Vector3 tangent;
			Fnd::Math::Vector3 bitangent;
			Fnd::Math::Vector2 texcoord;
		};
		std::vector<Vertex> vertices;

		std::vector<unsigned int> indices;
	};

	struct MeshNode
	{
		Fnd::Math::Matrix4 transform;
		std::vector<unsigned int> mesh_indices;
		unsigned int material_index;
		std::vector<MeshNode> children;
	};

	struct Material
	{
		std::string opacity_map;
		std::string normal_map;
		std::string diffuse_map;
		std::string roughness_map;
		std::string specular_map;
		std::string fresnel_map;
	};

	std::vector<Mesh> meshes;

	std::vector<Material> materials;

	MeshNode root_node;
};

class Model:
	public Fnd::AssetManager::Asset
{
	public:

		// Image will contain the r/rg/rgb/rgba data.
		// r/g/b/aTexture flag should match this.
		// isNormal, useMipMaps should be handled internally.
		virtual bool Create( const ModelData& data ) = 0;

		virtual ~Model();
};

}
}

#endif