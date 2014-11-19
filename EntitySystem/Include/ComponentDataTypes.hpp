#pragma once

#ifndef _ENTITYSYSTEM_COMPONENTDATATYPES_HPP_
#define _ENTITYSYSTEM_COMPONENTDATATYPES_HPP_

namespace Fnd
{
namespace EntitySystem
{
class Entity;
class SystemNode;
class IModel;
}
}

#include <string>
#include <cstdlib>
#include <vector>
#include <cassert>

typedef unsigned char			uint8;
typedef signed char				sint8;
typedef unsigned short int		uint16;
typedef signed short int		sint16;
typedef unsigned long int		uint32;
typedef signed long int			sint32;
typedef unsigned long long int	uint64;
typedef signed long long int	sint64;
typedef float					float32;
typedef double					float64;
typedef char					string64[64];
typedef char					string512[512];
typedef char					string1024[1024];

#define RIGIDBODYCOLLIDERTYPE_UNDEFINED		0
#define RIGIDBODYCOLLIDERTYPE_INFINITEPLANE	1
#define RIGIDBODYCOLLIDERTYPE_PLANE			2
#define RIGIDBODYCOLLIDERTYPE_SPHERE		3
#define RIGIDBODYCOLLIDERTYPE_CUBE			4
#define RIGIDBODYCOLLIDERTYPE_MESH			5

#include "../../Math/Include/Math.hpp"

#endif
