#pragma once

#ifndef _DIRECTX11MODEL_HPP_
#define _DIRECTX11MODEL_HPP_

#include "../../AssetManager/Include/Model.hpp"

#include "../../glew/Include/glew.hpp"

#include <memory>

namespace Fnd
{
namespace OpenGLGraphics
{
class OpenGLGraphicsBase;

class OpenGLModel:
	public Fnd::AssetManager::Model
{
	public:

		OpenGLModel( Fnd::OpenGLGraphics::OpenGLGraphicsBase* graphics );

		bool Create( const Fnd::AssetManager::ModelData& data );

		~OpenGLModel();

		struct Model
		{
			struct Mesh
			{
				typedef Fnd::AssetManager::ModelData::Mesh::Vertex Vertex;

				GLuint vertex_vbo;
				GLuint index_vbo;
				GLuint vao;

				unsigned int num_indices;
			};

			typedef Fnd::AssetManager::ModelData::MeshNode MeshNode;

			std::vector<Mesh> meshes;

			MeshNode root_node;
		};

		void* GetResource();

	private:

		Fnd::OpenGLGraphics::OpenGLGraphicsBase* _graphics;

		Model _resource;
};

}
}

#endif