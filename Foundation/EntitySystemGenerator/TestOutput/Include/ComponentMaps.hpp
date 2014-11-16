/*
	This file is automatically generated.
	Do not edit this file manually.
*/

#ifndef _COMPONENTMAPS_HPP_
#define _COMPONENTMAPS_HPP_

#include "Components.hpp"
#include "../../Utility/Include/IdGenerator.hpp"

#include <map>

namespace Fnd
{
namespace EntitySystem
{

class ComponentMaps
{
private:
	std::map<unsigned int, SceneNodeComponent> scenenodecomponent;
	std::map<unsigned int, CameraPropertiesComponent> camerapropertiescomponent;
	std::map<unsigned int, RumbleComponent> rumblecomponent;
	std::map<unsigned int, RigidBodyComponent> rigidbodycomponent;
	std::map<unsigned int, AmbientLightComponent> ambientlightcomponent;
	std::map<unsigned int, DirectionalLightComponent> directionallightcomponent;
	std::map<unsigned int, SpotLightComponent> spotlightcomponent;
	std::map<unsigned int, PointLightComponent> pointlightcomponent;
	std::map<unsigned int, ModelComponent> modelcomponent;
	std::map<unsigned int, SkyBoxComponent> skyboxcomponent;
	std::map<unsigned int, MotionBlurComponent> motionblurcomponent;
	std::map<unsigned int, BloomComponent> bloomcomponent;
	std::map<unsigned int, ToneMapComponent> tonemapcomponent;
	std::map<unsigned int, AmbientOcclusionComponent> ambientocclusioncomponent;
	Fnd::Utility::IdGenerator _id_generator;

public:

	/**
		Default constructor.
	*/
	ComponentMaps();

	/**
		Get an existing component from its type and index.
		@note Returns null if the component doesn't exist.
		@tparam ComponentType The type of component.
		@param index The index of the component.
		@return Returns a pointer to the requested component.
	*/
	template <typename ComponentType>
	inline ComponentType* GetComponent( unsigned int index );

	/**
		Get an existing component from its type and index.
		@note Returns null if the component doesn't exist.
		@param component_id The id of the component type.
		@param index The index of the component.
		@return Returns a pointer to the requested component.
	*/
	 Component* GetComponent( unsigned int component_id, unsigned int index );

	/**
		Get the map of 'ComponentType' components.
		@tparam ComponentType The type of component to get the map for.
		@return Returns a map of 'ComponentType' components.
	*/
	template <typename ComponentType>
	inline std::map<unsigned int, ComponentType>& GetComponentMap();

	/**
		Get the map of 'ComponentType' components.
		@tparam ComponentType The type of component to get the map for.
		@return Returns a map of 'ComponentType' components.
	*/
	template <typename ComponentType>
	inline const std::map<unsigned int, ComponentType>& GetComponentMap() const;

	/**
		Add a component to a map.
		@tparam ComponentType The type of component to add.
		@param component The new component with initial data.
		@return Returns the id of the added component.
	*/
	template <typename ComponentType>
	inline unsigned int AddComponent( const ComponentType& component );

};

}
}

namespace Fnd
{
namespace EntitySystem
{

/*
	GetComponent<> implementations.
*/

template <>
inline SceneNodeComponent* ComponentMaps::GetComponent<SceneNodeComponent>( unsigned int index )
{
	auto iter = scenenodecomponent.find(index);
	return ( iter == scenenodecomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline CameraPropertiesComponent* ComponentMaps::GetComponent<CameraPropertiesComponent>( unsigned int index )
{
	auto iter = camerapropertiescomponent.find(index);
	return ( iter == camerapropertiescomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline RumbleComponent* ComponentMaps::GetComponent<RumbleComponent>( unsigned int index )
{
	auto iter = rumblecomponent.find(index);
	return ( iter == rumblecomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline RigidBodyComponent* ComponentMaps::GetComponent<RigidBodyComponent>( unsigned int index )
{
	auto iter = rigidbodycomponent.find(index);
	return ( iter == rigidbodycomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline AmbientLightComponent* ComponentMaps::GetComponent<AmbientLightComponent>( unsigned int index )
{
	auto iter = ambientlightcomponent.find(index);
	return ( iter == ambientlightcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline DirectionalLightComponent* ComponentMaps::GetComponent<DirectionalLightComponent>( unsigned int index )
{
	auto iter = directionallightcomponent.find(index);
	return ( iter == directionallightcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline SpotLightComponent* ComponentMaps::GetComponent<SpotLightComponent>( unsigned int index )
{
	auto iter = spotlightcomponent.find(index);
	return ( iter == spotlightcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline PointLightComponent* ComponentMaps::GetComponent<PointLightComponent>( unsigned int index )
{
	auto iter = pointlightcomponent.find(index);
	return ( iter == pointlightcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline ModelComponent* ComponentMaps::GetComponent<ModelComponent>( unsigned int index )
{
	auto iter = modelcomponent.find(index);
	return ( iter == modelcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline SkyBoxComponent* ComponentMaps::GetComponent<SkyBoxComponent>( unsigned int index )
{
	auto iter = skyboxcomponent.find(index);
	return ( iter == skyboxcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline MotionBlurComponent* ComponentMaps::GetComponent<MotionBlurComponent>( unsigned int index )
{
	auto iter = motionblurcomponent.find(index);
	return ( iter == motionblurcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline BloomComponent* ComponentMaps::GetComponent<BloomComponent>( unsigned int index )
{
	auto iter = bloomcomponent.find(index);
	return ( iter == bloomcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline ToneMapComponent* ComponentMaps::GetComponent<ToneMapComponent>( unsigned int index )
{
	auto iter = tonemapcomponent.find(index);
	return ( iter == tonemapcomponent.end() ) ? nullptr : &((*iter).second);
}
template <>
inline AmbientOcclusionComponent* ComponentMaps::GetComponent<AmbientOcclusionComponent>( unsigned int index )
{
	auto iter = ambientocclusioncomponent.find(index);
	return ( iter == ambientocclusioncomponent.end() ) ? nullptr : &((*iter).second);
}

/*
	GetComponentMap<> implementations.
*/

template <>
inline std::map<unsigned int,SceneNodeComponent>& ComponentMaps::GetComponentMap<SceneNodeComponent>()
{
	return scenenodecomponent;
}
template <>
inline std::map<unsigned int,CameraPropertiesComponent>& ComponentMaps::GetComponentMap<CameraPropertiesComponent>()
{
	return camerapropertiescomponent;
}
template <>
inline std::map<unsigned int,RumbleComponent>& ComponentMaps::GetComponentMap<RumbleComponent>()
{
	return rumblecomponent;
}
template <>
inline std::map<unsigned int,RigidBodyComponent>& ComponentMaps::GetComponentMap<RigidBodyComponent>()
{
	return rigidbodycomponent;
}
template <>
inline std::map<unsigned int,AmbientLightComponent>& ComponentMaps::GetComponentMap<AmbientLightComponent>()
{
	return ambientlightcomponent;
}
template <>
inline std::map<unsigned int,DirectionalLightComponent>& ComponentMaps::GetComponentMap<DirectionalLightComponent>()
{
	return directionallightcomponent;
}
template <>
inline std::map<unsigned int,SpotLightComponent>& ComponentMaps::GetComponentMap<SpotLightComponent>()
{
	return spotlightcomponent;
}
template <>
inline std::map<unsigned int,PointLightComponent>& ComponentMaps::GetComponentMap<PointLightComponent>()
{
	return pointlightcomponent;
}
template <>
inline std::map<unsigned int,ModelComponent>& ComponentMaps::GetComponentMap<ModelComponent>()
{
	return modelcomponent;
}
template <>
inline std::map<unsigned int,SkyBoxComponent>& ComponentMaps::GetComponentMap<SkyBoxComponent>()
{
	return skyboxcomponent;
}
template <>
inline std::map<unsigned int,MotionBlurComponent>& ComponentMaps::GetComponentMap<MotionBlurComponent>()
{
	return motionblurcomponent;
}
template <>
inline std::map<unsigned int,BloomComponent>& ComponentMaps::GetComponentMap<BloomComponent>()
{
	return bloomcomponent;
}
template <>
inline std::map<unsigned int,ToneMapComponent>& ComponentMaps::GetComponentMap<ToneMapComponent>()
{
	return tonemapcomponent;
}
template <>
inline std::map<unsigned int,AmbientOcclusionComponent>& ComponentMaps::GetComponentMap<AmbientOcclusionComponent>()
{
	return ambientocclusioncomponent;
}

/*
	AddComponent<> implementations.
*/

template <>
inline unsigned int ComponentMaps::AddComponent<SceneNodeComponent>( const SceneNodeComponent& component)
{
	unsigned int index = _id_generator.GetId();
	scenenodecomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<CameraPropertiesComponent>( const CameraPropertiesComponent& component)
{
	unsigned int index = _id_generator.GetId();
	camerapropertiescomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<RumbleComponent>( const RumbleComponent& component)
{
	unsigned int index = _id_generator.GetId();
	rumblecomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<RigidBodyComponent>( const RigidBodyComponent& component)
{
	unsigned int index = _id_generator.GetId();
	rigidbodycomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<AmbientLightComponent>( const AmbientLightComponent& component)
{
	unsigned int index = _id_generator.GetId();
	ambientlightcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<DirectionalLightComponent>( const DirectionalLightComponent& component)
{
	unsigned int index = _id_generator.GetId();
	directionallightcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<SpotLightComponent>( const SpotLightComponent& component)
{
	unsigned int index = _id_generator.GetId();
	spotlightcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<PointLightComponent>( const PointLightComponent& component)
{
	unsigned int index = _id_generator.GetId();
	pointlightcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<ModelComponent>( const ModelComponent& component)
{
	unsigned int index = _id_generator.GetId();
	modelcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<SkyBoxComponent>( const SkyBoxComponent& component)
{
	unsigned int index = _id_generator.GetId();
	skyboxcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<MotionBlurComponent>( const MotionBlurComponent& component)
{
	unsigned int index = _id_generator.GetId();
	motionblurcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<BloomComponent>( const BloomComponent& component)
{
	unsigned int index = _id_generator.GetId();
	bloomcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<ToneMapComponent>( const ToneMapComponent& component)
{
	unsigned int index = _id_generator.GetId();
	tonemapcomponent[index] = component;
	return index;
}
template <>
inline unsigned int ComponentMaps::AddComponent<AmbientOcclusionComponent>( const AmbientOcclusionComponent& component)
{
	unsigned int index = _id_generator.GetId();
	ambientocclusioncomponent[index] = component;
	return index;
}

}
}

#endif
