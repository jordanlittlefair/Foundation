#include "../Include/Game.hpp"

#include "../Include/GameTimer.hpp"

#include "../../GameComponentInterfaces/Include/IWindow.hpp"
#include "../../GameComponentInterfaces/Include/IGraphics.hpp"
#include "../../GameComponentInterfaces/Include/IPhysics.hpp"
#include "../../GameComponentInterfaces/Include/IWorld.hpp"
#include "../../EntitySystem/Include/Components.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"
#include "../../AssetManager/Include/AssetManager.hpp"
#include "../../Scripting/Include/ScriptManager.hpp"
#include "../../Input/Include/InputHandler.hpp"
#include "../../Logger/Include/Logger.hpp"
#include "../../GameSystems/Include/SceneGraphSystem.hpp"
#include "../../GameSystems/Include/AssetLinkerSystem.hpp"
#ifdef _WIN32
#include "../../OculusRift/Include/OculusRift.hpp"
#endif
#include "../../Settings/Include/EngineSettings.hpp"
#include "../../Settings/Include/EngineConfig.hpp"

using namespace Fnd::GameComponentInterfaces;
using namespace Fnd::Game;
using namespace Fnd::Logger;

Game::Game( const Fnd::Settings::EngineSettings& engine_settings ):
	_is_initialised(false),
	_window(nullptr),
	_graphics(nullptr),
	_physics(nullptr),
	_world(nullptr),
	_script_manager(nullptr),
	_entity_system(new Fnd::EntitySystem::EntitySystem()),
	_asset_manager(new Fnd::AssetManager::AssetManager()),
	_input_handler(new Fnd::Input::InputHandler()),
	_engine_settings(engine_settings)
{
}

void Game::SetWindow( IWindow* window )
{
	if ( !_is_initialised )
	{
		_window = window;
	}
}

void Game::SetGraphics( IGraphics* graphics )
{
	if ( !_is_initialised )
	{
		_graphics = graphics;
	}
}

void Game::SetPhysics( IPhysics* physics )
{
	if ( !_is_initialised )
	{
		_physics = physics;
	}
}

void Game::SetWorld( IWorld* world )
{
	if ( !_is_initialised )
	{
		_world = world;
	}
}

void Game::SetScriptManager( Fnd::Scripting::ScriptManager* script_manager )
{
	if ( !_script_manager )
	{
		_script_manager = script_manager;
	}
}

bool Game::Initialise()
{
#ifdef _WIN32
	if ( _graphics->VRIsEnabled() && _graphics->VRIsSupported() )
	{
		_oculus.reset( new Fnd::OculusRift::OculusRift() );
		
		_oculus->SetWindow( _window );
		_oculus->SetGraphics( _graphics );
	}
#endif
	Logger::Logger::GetInstance().Log( LogMessage( "Initialising Game...." ) );

	_asset_manager->SetGame(this);

	auto asset_linker_system = std::shared_ptr<Fnd::GameSystems::AssetLinkerSystem>(new Fnd::GameSystems::AssetLinkerSystem());
	_systems.push_back( asset_linker_system );
	
	Logger::Logger::GetInstance().Log( LogMessage( "Initialising Window component...." ) );
	if ( !_window )
	{
		Logger::Logger::GetInstance().Log( LogError( "Window component has not been set." ) );
		return false;
	}
	
	_window->SetWindowMessageListener(this);
    
    // Set a default window size
    _window->SetWindowSize(1280, 720);
    
	if ( !_window->Initialise() )
	{
		Logger::Logger::GetInstance().Log( LogError( "Failed to initialise Window component." ) );
		return false;
	}
	Logger::Logger::GetInstance().Log( LogMessage( "Initialised Window component." ) );


	Logger::Logger::GetInstance().Log( LogMessage( "Initialising Physics component...." ) );
	if ( !_physics )
	{
		Logger::Logger::GetInstance().Log( LogError( "Physics component has not been set" ) );
		return false;
	}

	_physics->SetPhysicsMessageListener(this);
	if ( !_physics->Initialise() )
	{
		Logger::Logger::GetInstance().Log( LogError( "Failed to initialise Physics component." ) );
		return false;
	}
	Logger::Logger::GetInstance().Log( LogMessage( "Initialised Physics component." ) );

	Logger::Logger::GetInstance().Log( LogMessage( "Getting Physics systems...." ) );
	auto physics_systems = _physics->GetSystems();
	this->_systems.insert( _systems.end(), physics_systems.begin(), physics_systems.end() );
	std::stringstream ssph;
	ssph << "Added " << physics_systems.size() << " Physics system" << (physics_systems.size()==1?"":"s") << ".";
	Logger::Logger::GetInstance().Log( LogMessage( ssph.str() ) );

	Logger::Logger::GetInstance().Log( LogMessage( "Initialising Graphics component...." ) );
	if ( !_graphics )
	{
		Logger::Logger::GetInstance().Log( LogError( "Graphics component has not been set" ) );
		return false;
	}

	auto scene_graph_system = std::shared_ptr<Fnd::GameSystems::SceneGraphSystem>(new Fnd::GameSystems::SceneGraphSystem());
	_systems.push_back( scene_graph_system );
	//scene_graph_system->SetEntitySystem(_entity_system.get());
	//scene_graph_system->SetAssetManager(_asset_manager.get());
	//scene_graph_system->Initialise();

#ifdef _WIN32
	if ( _oculus )
	{
		_oculus->InitialiseStart();
	}
#endif

	_graphics->SetGraphicsMessageListener(this);
	_graphics->SetGraphicsSettings(_engine_settings.GetGraphicsSettings());
	_graphics->SetEntitySystem( _entity_system.get() );
	_graphics->SetActiveCamera( IGraphics::Primary_ActiveCamera, 0 );
	_graphics->SetActiveCamera( IGraphics::Secondary_ActiveCamera, 0 );
	if ( !_graphics->Initialise() )
	{
		Logger::Logger::GetInstance().Log( LogError( "Failed to initialise Graphics component." ) );
		return false;
	}
	Logger::Logger::GetInstance().Log( LogMessage( "Initialised Graphics component." ) );

	Logger::Logger::GetInstance().Log( LogMessage( "Getting Graphics systems...." ) );
	auto graphics_systems = _graphics->GetSystems();
	this->_systems.insert( _systems.end(), graphics_systems.begin(), graphics_systems.end() );
	std::stringstream ss;
	ss << "Added " << graphics_systems.size() << " Graphic system" << (graphics_systems.size()==1?"":"s") << ".";
	Logger::Logger::GetInstance().Log( LogMessage( ss.str() ) );

	Logger::Logger::GetInstance().Log( LogMessage( "Initialising Scripting component...." ) );
	_script_manager->SetEntitySystem( _entity_system.get() );
	_script_manager->SetInputHandler( _input_handler.get() );
	if ( !_script_manager )
	{
		Logger::Logger::GetInstance().Log( LogError( "Scripting component has not been set" ) );
		return false;
	}

	Logger::Logger::GetInstance().Log( LogMessage( "Initialised Scripting component." ) );

#ifdef _WIN32
	_input_handler->SetWindow((HWND)_window->GetHWND());
#else
    _input_handler->SetDisplay(_window->GetXWindowsDisplay());
#endif
	_input_handler->Initialise();

	/*
		Oculus stuff
	*/
#ifdef _WIN32
	if ( _graphics->VRIsEnabled() )
	{	
		auto res = _oculus->Initialise();
	}
//	_window->SetWindowSize(1920,1080);
#endif

	for ( unsigned int i = 0; i < _systems.size(); ++i )
	{
		Logger::Logger::GetInstance().Log( LogMessage( "Initialising [" + _systems[i]->GetSystemName() + "] system...." ) );
		_systems[i]->SetEntitySystem(_entity_system.get());
		_systems[i]->SetAssetManager(_asset_manager.get());
		_entity_system->RegisterSystem(_systems[i].get());

		if ( !_systems[i]->Initialise() )
		{
			Logger::Logger::GetInstance().Log( LogError( "Failed to initialise [" + _systems[i]->GetSystemName() + "] system." ) );
			return false;
		}

		Logger::Logger::GetInstance().Log( LogMessage( "Initialised [" + _systems[i]->GetSystemName() + "] system." ) );
	}

	Logger::Logger::GetInstance().Log( LogMessage( "Initialising World component...." ) );
	if ( !_world )
	{
		Logger::Logger::GetInstance().Log( LogError( "World component has not been set" ) );
		return false;
	}

	_world->SetWorldMessageListener(this);
	if ( !_world->Initialise() )
	{
		Logger::Logger::GetInstance().Log( LogError( "Failed to initialise World component." ) );
		return false;
	}
	Logger::Logger::GetInstance().Log( LogMessage( "Initialised World component." ) );

	Logger::Logger::GetInstance().Log( LogMessage( "Initialised Game." ) );

	return true;
}

#include <sstream>
#include <fstream>

void Game::Play()
{
	_window->Show();

	//_input_handler->Activate();
	
	GameTimer game_timer;
	game_timer.SetTimeStep(1);
	game_timer.Start();
	game_timer.Tick();

	while ( _window->IsOpen() )
	{
#ifdef _WIN32
		if ( _oculus )
			_oculus->BeginRender( game_timer.GetTickCount() );
#endif
		_graphics->BeginRender();

		//auto e = _entity_system->GetEntityContainer().CreateEntity();
		//auto c = _entity_system->GetComponentMaps().AddComponent<Fnd::EntitySystem::AmbientLightComponent>(Fnd::EntitySystem::AmbientLightComponent());
		//e->AddComponent<Fnd::EntitySystem::AmbientLightComponent>(c);
		//auto a = Fnd::EntitySystem::AmbientLightComponent();
		//++t;

		/*if (0)// (t/60) == 10 )
		{
			auto en = _entity_system->GetEntityContainer().GetEntityByName("Cube0Light");
			if ( en )
			{
				Fnd::EntitySystem::Component* scc = en->GetComponent<Fnd::EntitySystem::SceneNodeComponent>(*_entity_system);

				if ( scc )
				{
					auto ret = _entity_system->GetComponentMaps().RemoveComponent(scc);

					auto bp = 0;
				}
				//_entity_system->GetEntityContainer().RemoveEntity(en);
			}
		}*/

		//GetEntitySystem().ReleaseComponent<Fnd::EntitySystem::AmbientLightComponent>(t/60);
		//GetEntitySystem().ReleaseComponent<Fnd::EntitySystem::PointLightComponent>(t/60);
		//GetEntitySystem().ReleaseComponent<Fnd::EntitySystem::SpotLightComponent>(t/60);
		//GetEntitySystem().ReleaseComponent<Fnd::EntitySystem::DirectionalLightComponent>(++t/60);
	
		_input_handler->Update();
			
		Fnd::CommonResources::FrameData frame_data;
		frame_data.frame_num = game_timer.GetTickCount();
		frame_data.time = game_timer.GetTime();
		frame_data.dt = game_timer.GetDt();

		std::stringstream ss;
		ss << frame_data.dt;
		
		Logger::Logger::GetInstance().Log( Logger::LogMessage( ss.str() ) );

		for ( unsigned int i = 0; i < _systems.size(); ++i )
		{
			_systems[i]->Update( frame_data );
		}

		_script_manager->Update( frame_data );

		//_graphics->Render();	// should be replaced by the systems
		_graphics->Present();
		_window->HandleWindowMessages();

#ifdef _WIN32
		if ( _oculus )
			_oculus->FinishRender();
#endif

		game_timer.Tick();
	}
}

void Game::OnWindowClose()
{
}

void Game::OnWindowResize( unsigned int width, unsigned int height )
{
	_graphics->Resize( width, height );
}

void Game::OnWindowActivate()
{
}

void Game::OnWindowDeactivate()
{
}

bool Game::VRIsEnabled() const
{
	return _graphics->VRIsEnabled();
}

void* Game::GetHWND() const
{
	return _window->GetHWND();
}

void* Game::GetHDC() const
{
	return _window->GetHDC();
}

void* Game::GetXWindowsDisplay() const
{
    return _window->GetXWindowsDisplay();
}

unsigned long Game::GetXWindowsWindow() const
{
    return _window->GetXWindowsWindow();
}

bool Game::GetVRTextureDimensions( unsigned int& width, unsigned int& height )
{
	width = 1920;
	height = 1080;
	return true;
#ifdef _WIN32
	if ( _oculus )
	{
		width = _oculus->GetTextureWidth();
		height = _oculus->GetTextureHeight();

		return true;
	}
	else
	{
		return false;
	}
#endif
}

Fnd::EntitySystem::EntitySystem& Game::GetEntitySystem()
{
	return *_entity_system;
}

Fnd::AssetManager::AssetManager& Game::GetAssetManager()
{
	return *_asset_manager;
}

Fnd::Scripting::ScriptManager& Game::GetScriptManager()
{
	return *_script_manager;
}

Fnd::GameComponentInterfaces::IGraphics* Game::GetGraphics()
{
	return _graphics;
}

Game::~Game()
{
}