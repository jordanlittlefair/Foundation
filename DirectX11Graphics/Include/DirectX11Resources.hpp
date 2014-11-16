#pragma once

#ifndef _DIRECTX11RESOURCES_HPP_
#define _DIRECTX11RESOURCES_HPP_

#include "../../Configuration/Include/Configuration.hpp"
#include "../../Math/Include/Math.hpp"

#include <vector>
#include <d3d11.h>

namespace Fnd
{
namespace DirectX11Graphics
{
class DirectX11GraphicsBase;

struct Pipeline
{
	Pipeline();

	ID3D11VertexShader* vs;
	ID3D11HullShader* hs;
	ID3D11DomainShader* ds;
	ID3D11GeometryShader* gs;
	ID3D11PixelShader* ps;
	ID3D11ComputeShader* cs;
};

struct Texture2D	// TODO: Could probably do with a better name...
{
	Texture2D();

	ID3D11ShaderResourceView* sr;

	unsigned int width;
	unsigned int height;
	unsigned int mip_levels;
};

struct EngineMesh	// Currently only positions, no normals, uvs etc
{
	struct Vertex
	{
		Fnd::Math::Vector3 position;
	};

	EngineMesh();

	ID3D11Buffer* vertex_buffer;
	ID3D11Buffer* index_buffer;

	unsigned int num_indices;
};

class DirectX11Resources
{
	public:

		DirectX11Resources( DirectX11GraphicsBase* graphics );

		void SetConfig( const Fnd::Configuration::GraphicsConfig& config );

		bool GetBytecodeFromFile( const std::string& filename, std::vector<char>& buffer ) const;
		const Fnd::CommonResources::PipelineDesc GetPipelineData( const std::string& pipeline ) const;

		bool Initialise();

		bool LoadTexture( const Fnd::CommonResources::Texture2DDesc& texture_desc );

		const Pipeline& GetShaders( const std::string& pipeline ) const;

		const Texture2D& GetTexture( const std::string& texture ) const;

		const EngineMesh& GetMesh( const std::string& mesh ) const;

		ID3D11SamplerState* GetDefaultSampler() const;

		ID3D11RasterizerState* GetLightQuadRasteriser() const;

		ID3D11RasterizerState* GetNoCullRasteriser() const;

		ID3D11RasterizerState* GetWireframeRasteriser() const;

		ID3D11DepthStencilState* GetGeometryDepthState() const;

		ID3D11DepthStencilState* GetLightQuadRenderDepthState() const;

		ID3D11DepthStencilState* GetLightVolumePrePassDepthState() const;

		ID3D11DepthStencilState* GetLightVolumeLightPassDepthState() const;
		
		ID3D11BlendState* GetAdditiveLightBlendState() const;

		~DirectX11Resources();

	private:

		bool LoadShaders();

		bool LoadEngineTextures();

		bool LoadEngineModels();
		
		Fnd::DirectX11Graphics::DirectX11GraphicsBase* _graphics;

		Fnd::Configuration::GraphicsConfig::GraphicsImplementation _config;
		Fnd::Configuration::GraphicsConfig::GraphicsCommon _common;

		std::map<std::string,Pipeline> _pipelines;
		std::map<std::string,Texture2D> _textures;
		std::map<std::string,EngineMesh> _meshes;

		ID3D11SamplerState* _default_sampler;
		
		ID3D11RasterizerState* _light_quad_rasteriser;
		ID3D11RasterizerState* _nocull_rasteriser;
		ID3D11RasterizerState* _wireframe_rasteriser;

		ID3D11DepthStencilState* _geometry_depth_state;
		ID3D11DepthStencilState* _lightquad_render_depth_state;
		ID3D11DepthStencilState* _lightvolume_prepass_depthstate;
		ID3D11DepthStencilState* _lightvolume_lightpass_depthstate;

		ID3D11BlendState* _additive_light_blendstate;
};

}
}

#endif