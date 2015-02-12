#include "../Include/MeshSystem.hpp"

#include "../../EntitySystem/Include/Components.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"

using namespace Fnd::OpenGLGraphics;
using namespace Fnd::EntitySystem;
using namespace Fnd::Math;

MeshSystem::MeshSystem( OpenGLGraphics* graphics ):
	OpenGLGraphicsSystem( "MeshSystem", graphics )
{
}

bool MeshSystem::Initialise()
{
	return true;
}

void MeshSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	ForEachCamera( [this]( const CameraData& camera_data )
	{
	}
	);
}

void MeshSystem::RenderMeshNode(
						OpenGLModel::Model* model, 
						const Fnd::Math::Matrix4& parent_matrix,
						const Fnd::Math::Matrix4& view_matrix, 
						const Fnd::Math::Matrix4& proj_matrix,
						const Fnd::Math::Matrix4& view_proj_matrix,
						OpenGLModel::Model::MeshNode* mesh_node )
{
	
}

MeshSystem::~MeshSystem()
{
}