#pragma once

#if PLATFORM_WINDOWS
#pragma warning(pop)
#ifndef UE4_MINIMAL_WINDOWS_INCLUDE
#define UE4_MINIMAL_WINDOWS_INCLUDE
#endif
#include "Windows/AllowWindowsPlatformTypes.h"
#elif PLATFORM_COMPILER_CLANG
#pragma clang diagnostic pop
#endif
