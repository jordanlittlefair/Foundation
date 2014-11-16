#include "../Include/DirectX11Material.hpp"

using namespace Fnd::DirectX11Graphics;

DirectX11Material::DirectX11Material( DirectX11Resources* resources ):
	_resources(resources),
	_opacity_map("DefaultOpacity"),
	_normal_map("DefaultNormal"),
	_diffuse_texture("DefaultDiffuse"),
	_roughness_texture("DefaultRoughness"),
	_specular_texture("DefaultSpecular"),
	_fresnel_texture("DefaultFresnel")
{
}

void DirectX11Material::SetOpacityMap( const std::string& opacity_map )
{
	_opacity_map = opacity_map;
}

void DirectX11Material::SetNormalMap( const std::string& normal_map )
{
	_normal_map = normal_map;
}

void DirectX11Material::SetRoughnessTexture( const std::string& roughness_texture )
{
	_roughness_texture = roughness_texture;
}

void DirectX11Material::SetDiffuseTexture( const std::string& diffuse_texture )
{
	_diffuse_texture = diffuse_texture;
}

void DirectX11Material::SetFresnelTexture( const std::string& fresnel_texture )
{
	_fresnel_texture = fresnel_texture;
}

void DirectX11Material::SetSpecularTexture( const std::string& specular_texture )
{
	_specular_texture = specular_texture;
}

const Texture2D& DirectX11Material::GetOpacityMap() const
{
	return _resources->GetTexture(_opacity_map);
}

const Texture2D& DirectX11Material::GetNormalMap() const
{
	return _resources->GetTexture(_normal_map);
}

const Texture2D& DirectX11Material::GetDiffuseTexture() const
{
	return _resources->GetTexture(_diffuse_texture);
}

const Texture2D& DirectX11Material::GetRoughnessTexture() const
{
	return _resources->GetTexture(_roughness_texture);
}

const Texture2D& DirectX11Material::GetSpecularTexture() const
{
	return _resources->GetTexture(_specular_texture);
}

const Texture2D& DirectX11Material::GetFresnelTexture() const
{
	return _resources->GetTexture(_fresnel_texture);
}