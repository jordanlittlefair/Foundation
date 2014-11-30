#include "../Include/DirectX11Model.hpp"

#include "../Include/DirectX11Graphics.hpp"

using namespace Fnd::DirectX11Graphics;

DirectX11Model::DirectX11Model( Fnd::DirectX11Graphics::DirectX11Graphics* graphics ):
	_graphics(graphics)
{
}

bool DirectX11Model::Create( const Fnd::AssetManager::ModelData& data )
{
	for ( unsigned int i = 0; i < data.meshes.size(); ++i )
	{
		_resource.meshes.push_back(Model::Mesh());
		Model::Mesh& mesh = _resource.meshes.back();

		auto& mesh_data = data.meshes[i];

		{
			D3D11_BUFFER_DESC vb_desc;
			vb_desc.ByteWidth = mesh_data.vertices.size() * sizeof(Model::Mesh::Vertex);
			vb_desc.Usage = D3D11_USAGE_IMMUTABLE;
			vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vb_desc.CPUAccessFlags = 0;
			vb_desc.MiscFlags = 0;
			vb_desc.StructureByteStride = sizeof(Model::Mesh::Vertex);

			D3D11_SUBRESOURCE_DATA vb_data;
			vb_data.pSysMem = &(mesh_data.vertices[0]);
			vb_data.SysMemPitch = 0;
			vb_data.SysMemSlicePitch = 0;

			auto res = _graphics->Device()->CreateBuffer(	&vb_desc,
												&vb_data,
												&mesh.vb );

			if ( res != S_OK )
			{
				return false;
			}
		}
		{
			D3D11_BUFFER_DESC ib_desc;
			ib_desc.ByteWidth = mesh_data.indices.size() * sizeof(unsigned int);
			ib_desc.Usage = D3D11_USAGE_IMMUTABLE;
			ib_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			ib_desc.CPUAccessFlags = 0;
			ib_desc.MiscFlags = 0;
			ib_desc.StructureByteStride = sizeof(unsigned int);

			D3D11_SUBRESOURCE_DATA ib_data;
			ib_data.pSysMem = &(mesh_data.indices[0]);
			ib_data.SysMemPitch = 0;
			ib_data.SysMemSlicePitch = 0;

			auto res = _graphics->Device()->CreateBuffer(	&ib_desc,
													&ib_data,
													&mesh.ib );

			mesh.num_indices = mesh_data.indices.size();

			if ( res != S_OK )
			{
				return false;
			}
		}
	}

	for ( unsigned int i = 0; i < data.materials.size(); ++i )
	{
		_resource.materials.push_back(DirectX11Material(&_graphics->GetResources()));
		DirectX11Material& material = _resource.materials.back();

		using namespace Fnd::CommonResources;

		if ( !data.materials[i].opacity_map.empty() )
		{
			Texture2DDesc desc = { "", false, Texture2DDesc::FormatUnknown };
			desc.filename = data.materials[i].opacity_map;
			desc.generate_mips = true;
			desc.format = Texture2DDesc::FormatR;
			_graphics->GetResources().LoadTexture( desc );
			material.SetOpacityMap( data.materials[i].opacity_map );
		}
		if ( !data.materials[i].normal_map.empty() )
		{
			Texture2DDesc desc = { "", false, Texture2DDesc::FormatUnknown };
			desc.filename = data.materials[i].normal_map;
			desc.generate_mips = true;
			desc.format = Texture2DDesc::FormatRGBA;
			_graphics->GetResources().LoadTexture( desc );
			material.SetNormalMap( data.materials[i].normal_map );
		}
		if ( !data.materials[i].diffuse_map.empty() )
		{
			Texture2DDesc desc = { "", false, Texture2DDesc::FormatUnknown };
			desc.filename = data.materials[i].diffuse_map;
			desc.generate_mips = true;
			desc.format = Texture2DDesc::FormatRGBA;
			_graphics->GetResources().LoadTexture( desc );
			material.SetDiffuseTexture( data.materials[i].diffuse_map );
		}
		if ( !data.materials[i].roughness_map.empty() )
		{
			Texture2DDesc desc = { "", false, Texture2DDesc::FormatUnknown };
			desc.filename = data.materials[i].roughness_map;
			desc.generate_mips = true;
			desc.format = Texture2DDesc::FormatR;
			_graphics->GetResources().LoadTexture( desc );
			material.SetRoughnessTexture( data.materials[i].roughness_map );
		}
		if ( !data.materials[i].specular_map.empty() )
		{
			Texture2DDesc desc = { "", false, Texture2DDesc::FormatUnknown };
			desc.filename = data.materials[i].specular_map;
			desc.generate_mips = true;
			desc.format = Texture2DDesc::FormatRGBA;
			_graphics->GetResources().LoadTexture( desc );
			material.SetSpecularTexture( data.materials[i].specular_map );
		}
		if ( !data.materials[i].fresnel_map.empty() )
		{
			Texture2DDesc desc = { "", false, Texture2DDesc::FormatUnknown };
			desc.filename = data.materials[i].fresnel_map;
			desc.generate_mips = true;
			desc.format = Texture2DDesc::FormatR;
			_graphics->GetResources().LoadTexture( desc );
			material.SetFresnelTexture( data.materials[i].fresnel_map );
		}
	}
	auto& res = _graphics->GetResources();
	_resource.root_node = data.root_node;

	return true;
}

DirectX11Model::~DirectX11Model()
{
	for ( unsigned int i = 0; i < _resource.meshes.size(); ++i )
	{
		if ( _resource.meshes[i].vb )
		{
			_resource.meshes[i].vb->Release();
		}
		if ( _resource.meshes[i].ib )
		{
			_resource.meshes[i].ib->Release();
		}
	}
}

void* DirectX11Model::GetResource()
{
	return (void*)&_resource;
}