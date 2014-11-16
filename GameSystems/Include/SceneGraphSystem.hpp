#pragma once

#ifndef _SCENEGRAPHSYSTEM_HPP_
#define _SCENEGRAPHSYSTEM_HPP_

#include "../../EntitySystem/Include/System.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"

namespace Fnd
{
namespace GameSystems
{

class SceneGraphSystem:
	public Fnd::EntitySystem::System
{
	public:

		SceneGraphSystem();

		void AddNode( Fnd::EntitySystem::SystemNode* node );

		std::vector<std::string> GetRegisteredNodes();

		bool Initialise();

	protected:

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );

	private:

		struct GraphNode
		{
			GraphNode();

			unsigned int entity_id;

			Fnd::EntitySystem::SceneNodeNode* node;
			
			std::vector<GraphNode> children;

			void GenerateMatrices( SceneGraphSystem* system, Fnd::Math::Matrix4& xform );

			GraphNode* FindNode( unsigned int entity_id );
		};

		GraphNode* FindNode( unsigned int entity_id );

		std::vector<GraphNode> _parents;
};

}
}

#endif