#pragma once

#ifndef _WORLDLOADERERRORS_HPP_
#define _WORLDLOADERERRORS_HPP_

#include <string>

namespace Fnd
{
namespace WorldLoader
{

/**
	An enum returned when loading a world file.
*/
enum WorldLoaderResult
{
	WorldLoaderSuccess,
	WorldLoaderRapidxmlFail,
	WorldLoaderUnexpectedTag,
	WorldLoaderMissingTag,
	WorldLoaderInvalidComponent,
	WorldLoaderInvalidComponentData
};

inline bool IsSuccess( WorldLoaderResult res )
{
	return res == WorldLoaderSuccess;
}

inline std::string GetStringFromError(WorldLoaderResult res)
{
	std::string ret;

	switch (res)
	{
	case WorldLoaderSuccess:
		ret = "World created successfully.";
		break;
	case WorldLoaderRapidxmlFail:
		ret = "Failed to load and parse the xml file.";
		break;
	case WorldLoaderUnexpectedTag:
		ret = "Failed to create World: unexpected tag.";
		break;
	case WorldLoaderMissingTag:
		ret = "Failed to create World: tag missing.";
		break;
	case WorldLoaderInvalidComponent:
		ret = "Failed to create World: invalid component.";
		break;
	case WorldLoaderInvalidComponentData:
		ret = "Failed to create World: invalid component data.";
		break;
	default:
		ret = "Unknown Error.";
		break;
	}

	return ret;
}

}
}

#endif