#pragma once

#ifndef _MOCKSCRIPTING_CAMERAANIMATION_HPP_
#define _MOCKSCRIPTING_CAMERAANIMATION_HPP_

#include "../MockScript.hpp"
#include "../../../Logger/Include/Logger.hpp"
#include "../../../EntitySystem/Include/Components.hpp"
#include "../../../EntitySystem/Include/Entity.hpp"
#include "../../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../../EntitySystem/Include/EntitySystem.hpp"
#include "../../../EntitySystem/Include/EntityContainer.hpp"
#include "../../../EntitySystem/Include/SystemNodes.hpp"
#include "../../../EntitySystem/Include/SystemNodesContainer.hpp"

namespace Fnd
{
namespace MockScripting
{
class CameraAnimationScript:
	public Fnd::MockScripting::MockScript
{
	public:

		CameraAnimationScript( Fnd::Scripting::ScriptManager* script_manager ):
			MockScript(script_manager)
		{
		}

		void OnCreate()
		{
			Fnd::Logger::Logger::GetInstance().Log( Fnd::Logger::LogMessage( "CameraAnimationScript::OnCreate()" ) );
		}

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
		{
			auto es = GetScriptManager()->GetEntitySystem();

			auto entity = es->GetEntityContainer().GetEntity(GetOwningEntity());
			auto cam_comp = entity->GetComponent<Fnd::EntitySystem::CameraPropertiesComponent>(*es );

			if ( cam_comp )
			{
				//cam_comp->data.fov -= GetScriptManager()->GetInputHandler()->GetXbox()->GetAxisValue(XBOX_RT) - GetScriptManager()->GetInputHandler()->GetXbox()->GetAxisValue(XBOX_LT);
			}

			auto rb_comp = entity->GetComponent<Fnd::EntitySystem::RigidBodyComponent>(*es);
			auto sc_comp = entity->GetComponent<Fnd::EntitySystem::SceneNodeComponent>(*es);

			if ( rb_comp && sc_comp )
			{
				auto xform = Fnd::Math::Matrix4Helper<>::CreateRotationMatrix( sc_comp->data.rotation );

				auto world_linear_impulse = Fnd::Math::Vector3( GetScriptManager()->GetInputHandler()->GetXbox()->GetAxisValue(XBOX_LEFT_X),
																0,
																GetScriptManager()->GetInputHandler()->GetXbox()->GetAxisValue(XBOX_LEFT_Y))
											* frame_data.dt * 15;//* 0.2f;

				rb_comp->data.linear_impulse = Fnd::Math::Matrix4Helper<>::TransformPosition( world_linear_impulse, xform );

				auto world_angular_impulse = Fnd::Math::Vector3( -GetScriptManager()->GetInputHandler()->GetXbox()->GetAxisValue(XBOX_RIGHT_Y),
																GetScriptManager()->GetInputHandler()->GetXbox()->GetAxisValue(XBOX_RIGHT_X),
																-(GetScriptManager()->GetInputHandler()->GetXbox()->GetAxisValue(XBOX_RT) - GetScriptManager()->GetInputHandler()->GetXbox()->GetAxisValue(XBOX_LT)))
											* frame_data.dt * 2;//* 0.07f;
				
				rb_comp->data.angular_impulse = Fnd::Math::Matrix4Helper<>::TransformPosition( world_angular_impulse, xform );
			}

			if ( sc_comp )
			{
				if ( GetScriptManager()->GetInputHandler()->GetXbox()->IsReleased( XBOX_A ) )
				{
					std::stringstream ss;
					ss << "( " << sc_comp->data.position.x << "," << sc_comp->data.position.y << ", " << sc_comp->data.position.z << " )\n";
					OutputDebugString(ss.str().c_str());
				}
			}
		}

		void OnDestroy()
		{
			Fnd::Logger::Logger::GetInstance().Log( Fnd::Logger::LogMessage( "CameraAnimationScript::OnDestroy()" ) );
		}
};
}
}

#endif