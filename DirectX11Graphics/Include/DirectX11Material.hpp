#pragma once

#ifndef _DIRECTX11GRAPHICS_DIRECTX11MATERIAL_HPP_
#define _DIRECTX11GRAPHICS_DIRECTX11MATERIAL_HPP_

#include "DirectX11Resources.hpp"

#include <string>

namespace Fnd
{
namespace DirectX11Graphics
{

class DirectX11Material
{
	public:

		DirectX11Material( DirectX11Resources* resources );

		void SetOpacityMap( const std::string& opacity_map );
		void SetNormalMap( const std::string& normal_map );
		void SetDiffuseTexture( const std::string& diffuse_texture );
		void SetRoughnessTexture( const std::string& roughness_texture );
		void SetSpecularTexture( const std::string& specular_texture );
		void SetFresnelTexture( const std::string& fresnel_texture );

		const Texture2D& GetOpacityMap() const;
		const Texture2D& GetNormalMap() const;
		const Texture2D& GetDiffuseTexture() const;
		const Texture2D& GetRoughnessTexture() const;
		const Texture2D& GetSpecularTexture() const;
		const Texture2D& GetFresnelTexture() const;
	
	private:

		DirectX11Resources* _resources;
	
		std::string _opacity_map;
		std::string _normal_map;
		std::string _diffuse_texture;
		std::string _roughness_texture;
		std::string _specular_texture;
		std::string _fresnel_texture;
};

}
}

#endif