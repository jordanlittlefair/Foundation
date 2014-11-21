#include "../Include/LogRecords.hpp"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "../../Settings/Include/GameComponentSettings.hpp"

#include <sstream>

using namespace Fnd::Logger;

std::string Fnd::Logger::ParseLogSessionIdJson( const std::string& json )
{
	std::string ret;
	
	rapidjson::Document doc;
	doc.Parse(json.c_str());

	if ( doc.HasMember("logSessionId") )
	{
		rapidjson::Value& logsessionid_val = doc["logSessionId"];

		ret = logsessionid_val.GetString();
	}

	return ret;
}

std::string Fnd::Logger::WriteWindowSetupDataJson( const Fnd::Settings::WindowSettings& window_data )
{
	std::string ret;

	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
	writer.StartObject();
		writer.String("windowData");
		writer.StartObject();
			writer.String("implementation");
			writer.String(Settings::EngineConfig::GetWindowImplementationString(window_data.implementation).c_str());
			writer.String("windowTitle");
			writer.String(window_data.window_title.c_str());
			writer.String("initialWidth");
			writer.Int(window_data.initial_width);
			writer.String("initialHeight");
			writer.Int(window_data.initial_height);
			writer.String("isResizable");
			writer.Bool(window_data.is_resizable);
			writer.String("isFullscreen");
			writer.Bool(window_data.is_fullscreen);
		writer.EndObject();
	writer.EndObject();
	
	ret = s.GetString();

	return ret;
}

std::string Fnd::Logger::WriteGraphicsSetupDataJson( const Fnd::Settings::GraphicsSettings& graphics_data )
{
	std::string ret;

	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
	writer.StartObject();
		writer.String("graphicsData");
		writer.StartObject();
			writer.String("implementation");
			writer.String(Settings::EngineConfig::GetGraphicsImplementationString(graphics_data.implementation).c_str());
			writer.String("vr_enabled");
			writer.Bool(graphics_data.enable_vr);
		writer.EndObject();
	writer.EndObject();
	
	ret = s.GetString();

	return ret;
}

std::string Fnd::Logger::WriteWorldSetupDataJson( const Fnd::Settings::WorldSettings& world_data )
{
	std::string ret;

	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
	writer.StartObject();
		writer.String("worldData");
		writer.StartObject();
			writer.String("implementation");
			writer.String(Settings::EngineConfig::GetWorldImplementationString(world_data.implementation).c_str());
				
			writer.String("worldFiles");
			writer.StartArray();
			for ( auto iter = world_data.world_files.begin(); iter != world_data.world_files.end(); ++iter )
			{
				writer.StartObject();
					std::stringstream ss;
					ss << iter->first;
					writer.String(ss.str().c_str());
					writer.String(iter->second.world_filename.c_str());
				writer.EndObject();
			}
			writer.EndArray();

		writer.EndObject();
	writer.EndObject();
	
	ret = s.GetString();

	return ret;
}

std::string Fnd::Logger::WriteLogMessageJson( const LogMessage& log_message, unsigned int time )
{
	std::string ret;

	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
	writer.StartObject();
		writer.String("type");
		writer.String("message");
		writer.String("time");
		writer.Int(time);
		writer.String("message");
		writer.String(log_message.message.c_str());
	writer.EndObject();
	
	ret = s.GetString();

	return ret;
}

std::string Fnd::Logger::WriteLogErrorJson( const LogError& log_error, unsigned int time )
{
	std::string ret;

	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
	writer.StartObject();
		writer.String("type");
		writer.String("error");
		writer.String("time");
		writer.Int(time);
		writer.String("message");
		writer.String(log_error.message.c_str());
	writer.EndObject();
	
	ret = s.GetString();

	return ret;
}

std::string Fnd::Logger::WriteLogWarningJson( const LogWarning& log_warning, unsigned int time )
{
	std::string ret;

	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
	writer.StartObject();
		writer.String("type");
		writer.String("warning");
		writer.String("time");
		writer.Int(time);
		writer.String("message");
		writer.String(log_warning.message.c_str());
	writer.EndObject();
	
	ret = s.GetString();

	return ret;
}