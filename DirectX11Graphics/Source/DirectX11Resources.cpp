#include "../Include/DirectX11Resources.hpp"

#include "../Include/DirectX11Graphics.hpp"

#include "../../Utility/Include/Image.hpp"
#include "../../ModelLoader/Include/ModelLoader.hpp"
#include "../../AssetManager/Include/Model.hpp"
#include "../../Utility/Include/Utility.hpp"
#include "../../Utility/Include/MipMapGenerator.hpp"

#include <fstream>
#include <vector>

using namespace Fnd::DirectX11Graphics;
using namespace Fnd::Utility;

Pipeline::Pipeline():
	vs(nullptr),
	hs(nullptr),
	ds(nullptr),
	gs(nullptr),
	ps(nullptr),
	cs(nullptr)
{
}

Texture2D::Texture2D():
	sr(nullptr),
	width(0),
	height(0),
	mip_levels(0)
{
}

EngineMesh::EngineMesh():
	vertex_buffer(nullptr),
	index_buffer(nullptr),
	num_indices(0)
{
}

DirectX11Resources::DirectX11Resources( DirectX11Graphics* graphics ):
	_graphics(graphics),
	_default_sampler(nullptr),
	_light_quad_rasteriser(nullptr),
	_nocull_rasteriser(nullptr),
	_wireframe_rasteriser(nullptr),
	_geometry_depth_state(nullptr),
	_lightquad_render_depth_state(nullptr),
	_lightvolume_prepass_depthstate(nullptr),
	_lightvolume_lightpass_depthstate(nullptr),
	_additive_light_blendstate(nullptr)
{
}

void DirectX11Resources::SetConfig( const Fnd::Settings::EngineSettings::GraphicsSettings& config )
{
	_config = config;
}

bool DirectX11Resources::GetBytecodeFromFile( const std::string& filename, std::vector<char>& buffer ) const
{
	std::ifstream filestream( filename, std::ios::in | std::ios::binary | std::ios::ate );

	if ( filestream.is_open() )
	{
		auto end = filestream.tellg();
		filestream.seekg(std::ios::beg);
		auto start = filestream.tellg();

		auto length = end-start;

		buffer.resize((unsigned int)length);

		if ( length != 0 )
		{
			filestream.read(&buffer[0],length);
		}

		filestream.close();

		return true;
	}

	return false;
}

bool DirectX11Resources::Initialise()
{
	if ( !LoadShaders() )
	{
		return false;
	}

	if ( !LoadEngineTextures() )
	{
		return false;
	}

	if ( !LoadEngineModels() )
	{
		return false;
	}

	{
		D3D11_SAMPLER_DESC sampler_desc;
		sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.MipLODBias = 0.0f;
		sampler_desc.MaxAnisotropy = 16;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampler_desc.BorderColor[0] = 0.0f;
		sampler_desc.BorderColor[1] = 0.0f;
		sampler_desc.BorderColor[2] = 0.0f;
		sampler_desc.BorderColor[3] = 0.0f;
		sampler_desc.MinLOD = -D3D11_FLOAT32_MAX;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

		if ( FAILED( _graphics->Device()->CreateSamplerState( &sampler_desc, &_default_sampler ) ) )
		{
			return false;
		}
	}

	{
		D3D11_RASTERIZER_DESC rs_desc;

		rs_desc.FillMode = D3D11_FILL_SOLID;
		rs_desc.CullMode = D3D11_CULL_FRONT;
		rs_desc.FrontCounterClockwise = false;
		rs_desc.DepthBias = 0;
		rs_desc.DepthBiasClamp = 0.0f;
		rs_desc.SlopeScaledDepthBias = 0.0f;
		rs_desc.DepthClipEnable = false;
		rs_desc.ScissorEnable = false;
		rs_desc.MultisampleEnable = false;
		rs_desc.AntialiasedLineEnable = false;

		if ( FAILED( _graphics->Device()->CreateRasterizerState( &rs_desc, &_light_quad_rasteriser ) ) )
		{
			return false;
		}
	}

	{
		D3D11_RASTERIZER_DESC rs_desc;

		rs_desc.FillMode = D3D11_FILL_SOLID;
		rs_desc.CullMode = D3D11_CULL_NONE;
		rs_desc.FrontCounterClockwise = false;
		rs_desc.DepthBias = 0;
		rs_desc.DepthBiasClamp = 0.0f;
		rs_desc.SlopeScaledDepthBias = 0.0f;
		rs_desc.DepthClipEnable = false;
		rs_desc.ScissorEnable = false;
		rs_desc.MultisampleEnable = false;
		rs_desc.AntialiasedLineEnable = false;

		if ( FAILED( _graphics->Device()->CreateRasterizerState( &rs_desc, &_nocull_rasteriser ) ) )
		{
			return false;
		}
	}

	{
		D3D11_RASTERIZER_DESC rs_desc;

		rs_desc.FillMode = D3D11_FILL_WIREFRAME;
		rs_desc.CullMode = D3D11_CULL_NONE;
		rs_desc.FrontCounterClockwise = false;
		rs_desc.DepthBias = 0;
		rs_desc.DepthBiasClamp = 0.0f;
		rs_desc.SlopeScaledDepthBias = 0.0f;
		rs_desc.DepthClipEnable = false;
		rs_desc.ScissorEnable = false;
		rs_desc.MultisampleEnable = false;
		rs_desc.AntialiasedLineEnable = false;

		if ( FAILED( _graphics->Device()->CreateRasterizerState( &rs_desc, &_wireframe_rasteriser ) ) )
		{
			return false;
		}
	}

	{
		D3D11_DEPTH_STENCIL_DESC ds_desc;
		ds_desc.DepthEnable = true;
		ds_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		ds_desc.DepthFunc = D3D11_COMPARISON_LESS;
		ds_desc.StencilEnable = true;
		ds_desc.StencilReadMask = ~0;
		ds_desc.StencilWriteMask = ~0;
		ds_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		ds_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		ds_desc.BackFace = ds_desc.FrontFace;

		if ( FAILED( _graphics->Device()->CreateDepthStencilState( &ds_desc, &_geometry_depth_state ) ) )
		{
			return false;
		}
	}

	{
		D3D11_DEPTH_STENCIL_DESC ds_desc;
		ds_desc.DepthEnable = false;
		ds_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		ds_desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
		ds_desc.StencilEnable = true;
		ds_desc.StencilReadMask = ~0;
		ds_desc.StencilWriteMask = 0;
		ds_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
		ds_desc.BackFace = ds_desc.FrontFace;

		if ( FAILED( _graphics->Device()->CreateDepthStencilState( &ds_desc, &_lightquad_render_depth_state ) ) )
		{
			return false;
		}
	}

	{
		D3D11_DEPTH_STENCIL_DESC ds_desc;
		ds_desc.DepthEnable = true;
		ds_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		ds_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		ds_desc.StencilEnable = true;
		ds_desc.StencilReadMask = ~0;
		ds_desc.StencilWriteMask = ~0;
		ds_desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
		ds_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_DECR;
		
		ds_desc.BackFace = ds_desc.FrontFace;
		ds_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;

		if ( FAILED( _graphics->Device()->CreateDepthStencilState( &ds_desc, &_lightvolume_prepass_depthstate ) ) )
		{
			return false;
		}
	}

	{
		D3D11_DEPTH_STENCIL_DESC ds_desc;
		ds_desc.DepthEnable = false;
		ds_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		ds_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		ds_desc.StencilEnable = true;
		ds_desc.StencilReadMask = ~0;
		ds_desc.StencilWriteMask = ~0;
		ds_desc.FrontFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;
		ds_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		
		ds_desc.BackFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;
		ds_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		ds_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;

		if ( FAILED( _graphics->Device()->CreateDepthStencilState( &ds_desc, &_lightvolume_lightpass_depthstate ) ) )
		{
			return false;
		}
	}

	{
		D3D11_BLEND_DESC blend_desc;
		blend_desc.AlphaToCoverageEnable = false;
		blend_desc.IndependentBlendEnable = false;
		blend_desc.RenderTarget[0].BlendEnable = true;
		blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		if ( FAILED( _graphics->Device()->CreateBlendState( &blend_desc, &_additive_light_blendstate ) ) )
		{
			return false;
		}
	}

	return true;
}

bool DirectX11Resources::LoadShaders()
{
	// Create a default empty pipeline
	_pipelines[""] = Pipeline();

	for ( auto pipeline_iter = _config.shader_pipelines.begin(); pipeline_iter != _config.shader_pipelines.end(); ++pipeline_iter )
	{
		std::string name = pipeline_iter->first;

		if ( !pipeline_iter->second.vertex_shader.empty() )
		{
			std::vector<char> buffer;

			if ( GetBytecodeFromFile( pipeline_iter->second.vertex_shader, buffer ) )
			{
				_graphics->Device()->CreateVertexShader( &buffer[0], buffer.size(), nullptr, &_pipelines[name].vs );
			}
			else
			{
				return false;
			}
		}

		if ( !pipeline_iter->second.hull_shader.empty() )
		{
			std::vector<char> buffer;

			if ( GetBytecodeFromFile( pipeline_iter->second.hull_shader, buffer ) )
			{
				_graphics->Device()->CreateHullShader( &buffer[0], buffer.size(), nullptr, &_pipelines[name].hs );
			}
			else
			{
				return false;
			}
		}

		if ( !pipeline_iter->second.domain_shader.empty() )
		{
			std::vector<char> buffer;

			if ( GetBytecodeFromFile( pipeline_iter->second.domain_shader, buffer ) )
			{
				_graphics->Device()->CreateDomainShader( &buffer[0], buffer.size(), nullptr, &_pipelines[name].ds );
			}
			else
			{
				return false;
			}
		}

		if ( !pipeline_iter->second.hull_shader.empty() )
		{
			std::vector<char> buffer;

			if ( GetBytecodeFromFile( pipeline_iter->second.hull_shader, buffer ) )
			{
				_graphics->Device()->CreateHullShader( &buffer[0], buffer.size(), nullptr, &_pipelines[name].hs );
			}
			else
			{
				return false;
			}
		}

		if ( !pipeline_iter->second.geometry_shader.empty() )
		{
			std::vector<char> buffer;

			if ( GetBytecodeFromFile( pipeline_iter->second.geometry_shader, buffer ) )
			{
				_graphics->Device()->CreateGeometryShader( &buffer[0], buffer.size(), nullptr, &_pipelines[name].gs );
			}
			else
			{
				return false;
			}
		}

		if ( !pipeline_iter->second.pixel_shader.empty() )
		{
			std::vector<char> buffer;

			if ( GetBytecodeFromFile( pipeline_iter->second.pixel_shader, buffer ) )
			{
				_graphics->Device()->CreatePixelShader( &buffer[0], buffer.size(), nullptr, &_pipelines[name].ps );
			}
			else
			{
				return false;
			}
		}

		if ( !pipeline_iter->second.compute_shader.empty() )
		{
			std::vector<char> buffer;

			if ( GetBytecodeFromFile( pipeline_iter->second.compute_shader, buffer ) )
			{
				_graphics->Device()->CreateComputeShader( &buffer[0], buffer.size(), nullptr, &_pipelines[name].cs );
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

bool DirectX11Resources::LoadTexture( const Fnd::CommonResources::Texture2DDesc& texture_desc, const std::string& explicit_name )
{
	if ( _textures.find( texture_desc.filename ) != _textures.end() )
		return true;

	if ( texture_desc.filename.empty() )
		return false;

	Texture2D engine_texture;
			
	Fnd::Utility::Image image;

	unsigned int format = texture_desc.format;
		
	if ( image.CreateImageFromFile( texture_desc.filename, (Fnd::Utility::Image::Format)format, 0, 0, 0, 0 ) != Fnd::Utility::Image::Result::OK_Return )
	{
		return false;
	}

	engine_texture.mip_levels = Min( MipMapGenerator::GetNumMipLevels( image ), texture_desc.generate_mips ? ~0u : 1u );

	auto mipmaps = Fnd::Utility::MipMapGenerator::GenerateMipMaps( image, engine_texture.mip_levels );

	engine_texture.width = image.GetWidth();
	engine_texture.height = image.GetHeight();

	D3D11_TEXTURE2D_DESC tex_desc;
	tex_desc.Width = image.GetWidth();
	tex_desc.Height = image.GetHeight();
	tex_desc.MipLevels = engine_texture.mip_levels;
	tex_desc.ArraySize = 1;
	
	tex_desc.Format = DXGI_FORMAT_UNKNOWN;

	switch (format)
	{
	case 1:
		tex_desc.Format = DXGI_FORMAT_R8_UNORM;
		break;
	case 2:
		tex_desc.Format = DXGI_FORMAT_R8G8_UNORM;
		break;
	case 3:
		break;
	case 4:
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	default:
		break;
	}
	
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.Usage = D3D11_USAGE_IMMUTABLE;
	tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tex_desc.CPUAccessFlags = 0;
	tex_desc.MiscFlags = 0;

	std::vector<D3D11_SUBRESOURCE_DATA> tex_data;
	for ( unsigned int i = 0; i < mipmaps.size(); ++i )
	{
		D3D11_SUBRESOURCE_DATA this_subresource;
		this_subresource.pSysMem = mipmaps[i].GetData();
		this_subresource.SysMemPitch = format * mipmaps[i].GetWidth();
		this_subresource.SysMemSlicePitch = format * mipmaps[i].GetWidth() * mipmaps[i].GetHeight();

		tex_data.push_back(this_subresource);
	}

	ID3D11Texture2D* tex = nullptr;

	if ( FAILED( _graphics->Device()->CreateTexture2D( &tex_desc, &tex_data[0], &tex ) ) )
	{
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC sr_desc;
	sr_desc.Format = tex_desc.Format;
	sr_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	sr_desc.Texture2D.MostDetailedMip = 0;
	sr_desc.Texture2D.MipLevels = engine_texture.mip_levels;

	if ( FAILED( _graphics->Device()->CreateShaderResourceView( tex, &sr_desc, &engine_texture.sr ) ) )
	{
		if ( tex )
		{
			tex->Release();
		}
		return false;
	}

	if ( tex )
	{
		tex->Release();
	}

	_textures[ explicit_name.empty() ? texture_desc.filename : explicit_name ] = engine_texture;

	return true;
}

bool DirectX11Resources::LoadEngineTextures()
{
	_textures[""] = Texture2D();
	
	for ( auto texture_iter = _config.common.textures.begin(); texture_iter != _config.common.textures.end(); ++texture_iter )
	{
		if ( !LoadTexture( texture_iter->second, texture_iter->first ) )
			return false;
	}

	return true;
}

bool DirectX11Resources::LoadEngineModels()
{
	_meshes[""] = EngineMesh();

	for ( auto model_iter = _config.common.models.begin(); model_iter != _config.common.models.end(); ++model_iter )
	{
		Fnd::AssetManager::ModelData model_data;

		if ( !ModelLoader::ModelLoader::LoadModel( model_iter->second.filename, 1.0f, 0, model_data ) )
		{
			return false;
		}

		if ( model_data.meshes.size() != 1 )
		{
			return false;
		}

		auto& mesh_data = model_data.meshes[0];

		EngineMesh mesh;
		{
			D3D11_BUFFER_DESC vb_desc;
			vb_desc.ByteWidth = mesh_data.vertices.size() * sizeof(EngineMesh::Vertex);
			vb_desc.Usage = D3D11_USAGE_IMMUTABLE;
			vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vb_desc.CPUAccessFlags = 0;
			vb_desc.MiscFlags = 0;
			vb_desc.StructureByteStride = sizeof(EngineMesh::Vertex);

			std::vector<EngineMesh::Vertex> vertices;
			for ( unsigned int i = 0; i < mesh_data.vertices.size(); ++i )
			{
				EngineMesh::Vertex vertex = { mesh_data.vertices[i].position };

				vertices.push_back(vertex);
			}

			D3D11_SUBRESOURCE_DATA vb_data;
			vb_data.pSysMem = &(vertices[0]);
			vb_data.SysMemPitch = 0;
			vb_data.SysMemSlicePitch = 0;

			auto res = _graphics->Device()->CreateBuffer(	&vb_desc,
															&vb_data,
															&mesh.vertex_buffer );

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
													&mesh.index_buffer );

			mesh.num_indices = mesh_data.indices.size();

			if ( res != S_OK )
			{
				return false;
			}
		}

		_meshes[model_iter->first] = mesh;

	}

	return true;
}

const Pipeline& DirectX11Resources::GetShaders( const std::string& pipeline ) const
{
	auto found_iter = _pipelines.find(pipeline);
	if ( found_iter == _pipelines.end() )
	{
		auto default_iter = _pipelines.find("");
		
		return default_iter->second;
	}
	else
	{
		return found_iter->second;
	}
}

const Texture2D& DirectX11Resources::GetTexture( const std::string& texture ) const
{
	auto found_iter = _textures.find(texture);
	if ( found_iter == _textures.end() )
	{
		auto default_iter = _textures.find("");
		
		return default_iter->second;
	}
	else
	{
		return found_iter->second;
	}
}

const EngineMesh& DirectX11Resources::GetMesh( const std::string& mesh ) const
{
	auto found_iter = _meshes.find(mesh);
	if ( found_iter == _meshes.end() )
	{
		auto default_iter = _meshes.find("");
		
		return default_iter->second;
	}
	else
	{
		return found_iter->second;
	}
}

ID3D11SamplerState* DirectX11Resources::GetDefaultSampler() const
{
	return _default_sampler;
}

ID3D11RasterizerState* DirectX11Resources::GetLightQuadRasteriser() const
{
	return _light_quad_rasteriser;
}

ID3D11RasterizerState* DirectX11Resources::GetNoCullRasteriser() const
{
	return _nocull_rasteriser;
}

ID3D11RasterizerState* DirectX11Resources::GetWireframeRasteriser() const
{
	return _wireframe_rasteriser;
}

ID3D11DepthStencilState* DirectX11Resources::GetGeometryDepthState() const
{
	return _geometry_depth_state;
}

ID3D11DepthStencilState* DirectX11Resources::GetLightQuadRenderDepthState() const
{
	return _lightquad_render_depth_state;
}

ID3D11DepthStencilState* DirectX11Resources::GetLightVolumePrePassDepthState() const
{
	return _lightvolume_prepass_depthstate;
}

ID3D11DepthStencilState* DirectX11Resources::GetLightVolumeLightPassDepthState() const
{
	return _lightvolume_lightpass_depthstate;
}

ID3D11BlendState* DirectX11Resources::GetAdditiveLightBlendState() const
{
	return _additive_light_blendstate;
}

const Fnd::CommonResources::PipelineDesc DirectX11Resources::GetPipelineData( const std::string& pipeline ) const
{
	auto found_iter = _config.shader_pipelines.find(pipeline);
	if ( found_iter == _config.shader_pipelines.end() )
	{		
		return Fnd::CommonResources::PipelineDesc();
	}
	else
	{
		return found_iter->second;
	}
}

DirectX11Resources::~DirectX11Resources()
{
	for ( auto iter = _pipelines.begin(); iter != _pipelines.end(); ++iter )
	{
		if ( iter->second.vs )
		{
			iter->second.vs->Release();
		}
		if ( iter->second.hs )
		{
			iter->second.hs->Release();
		}
		if ( iter->second.ds )
		{
			iter->second.ds->Release();
		}
		if ( iter->second.gs )
		{
			iter->second.gs->Release();
		}
		if ( iter->second.ps )
		{
			iter->second.ps->Release();
		}
		if ( iter->second.cs )
		{
			iter->second.cs->Release();
		}
	}
	
	for ( auto iter = _textures.begin(); iter != _textures.end(); ++iter )
	{
		if ( iter->second.sr )
		{
			iter->second.sr->Release();
		}
	}

	for ( auto iter = _meshes.begin(); iter != _meshes.end(); ++iter )
	{
		if ( iter->second.vertex_buffer )
		{
			iter->second.vertex_buffer->Release();
		}
		if ( iter->second.index_buffer )
		{
			iter->second.index_buffer->Release();
		}
	}

	if ( _default_sampler )
	{
		_default_sampler->Release();
	}

	if ( _light_quad_rasteriser )
	{
		_light_quad_rasteriser->Release();
	}

	if ( _nocull_rasteriser )
	{
		_nocull_rasteriser->Release();
	}

	if ( _wireframe_rasteriser )
	{
		_wireframe_rasteriser->Release();
	}

	if ( _geometry_depth_state )
	{
		_geometry_depth_state->Release();
	}

	if ( _lightquad_render_depth_state )
	{
		_lightquad_render_depth_state->Release();
	}

	if ( _lightvolume_prepass_depthstate )
	{
		_lightvolume_prepass_depthstate->Release();
	}

	if ( _lightvolume_lightpass_depthstate )
	{
		_lightvolume_lightpass_depthstate->Release();
	}

	if ( _additive_light_blendstate )
	{
		_additive_light_blendstate->Release();
	}
}