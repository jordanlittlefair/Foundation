#pragma once

#ifndef _ENTITYSYSTEM_COMPONENTDATACONVERSION_HPP_
#define _ENTITYSYSTEM_COMPONENTDATACONVERSION_HPP_

#include "ComponentDataTypes.hpp"

namespace Fnd
{
namespace EntitySystem
{
class EntitySystem;
}
namespace ContentManager
{
class ContentManager;
}
}

namespace Fnd
{
namespace EntitySystem
{

template <typename T>
void ConvertFromString( const std::string& as_string, T& t );

}
}

#endif