#pragma once

#if PLATFORM_WINDOWS
#pragma warning(push)
#pragma warning (disable : 4125)// decimal digit terminates...
#pragma warning (disable : 4647)// behavior change __is_pod...
#pragma warning (disable : 4668)// 'symbol' is not defined as a preprocessor macro...
#pragma warning (disable : 4456)// declaration of 'size' hides previous local declaration
#pragma warning (disable : 4577)// 'noexcept' used with no exception handling mode specified
#pragma warning (disable : 4946)// reinterpret_cast used between related classes
#pragma warning (disable : 4005)// 'TEXT': macro redefinition
#pragma warning (disable : 4582)// constructor is not implicitly called
#pragma warning (disable : 4583)// destructor is not implicitly called
#pragma warning (disable : 4800)// Implicit conversion from 'type' to bool. Possible information loss

#ifdef WINDOWS_PLATFORM_TYPES_GUARD
#pragma warning(push)
#include "Windows/HideWindowsPlatformTypes.h"
#endif
#elif PLATFORM_COMPILER_CLANG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wshadow"
#endif