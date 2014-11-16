#pragma once

#ifndef _UTILITYDEBUG_HPP_
#define _UTILITYDEBUG_HPP_

#include <cassert>
#include <Windows.h>

#define FND_ASSERT(x) assert(x)

#define FND_BREAKPOINT DebugBreak

#endif