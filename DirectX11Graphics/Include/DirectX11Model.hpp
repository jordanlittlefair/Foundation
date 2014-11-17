#pragma once

#ifndef _DIRECTX11MODEL_HPP_
#define _DIRECTX11MODEL_HPP_

#include <d3d11.h>

#include "../../AssetManager/Include/Model.hpp"
#include "DirectX11Material.hpp"
#include <memory>

namespace Fnd
{
namespace DirectX11Graphics
{
class DirectX11GraphicsBase;

class DirectX11Model:
	public Fnd::AssetManager::Model
{
	public:

		DirectX11Model( Fnd::DirectX11Graphics::DirectX11GraphicsBase* graphics );

		bool Create( const Fnd::AssetManager::ModelData& data );

		~DirectX11Model();

		struct Model
		{
			struct Mesh
			{
				typedef Fnd::AssetManager::ModelData::Mesh::Vertex Vertex;

				ID3D11Buffer* vb;
				ID3D11Buffer* ib;

				unsigned int num_indices;
			};

			typedef Fnd::AssetManager::ModelData::MeshNode MeshNode;

			std::vector<Mesh> meshes;

			std::vector<DirectX11Material> materials;

			MeshNode root_node;
		};

		void* GetResource();

	private:

		Fnd::DirectX11Graphics::DirectX11GraphicsBase* _graphics;

		Model _resource;
};

}
}

#endif