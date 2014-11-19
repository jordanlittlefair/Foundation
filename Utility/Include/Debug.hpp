#pragma once

#ifndef _UTILITY_DEBUG_HPP_
#define _UTILITY_DEBUG_HPP_

#include <cassert>
#include <Windows.h>

#define FND_ASSERT(x) assert(x)

#define FND_BREAKPOINT DebugBreak

#endif