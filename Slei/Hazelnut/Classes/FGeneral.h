//
//  FGeneral.h
//  Hazelnut
//
//  Created by Dominik Reisner on 21.01.16.
//
//

#ifndef Hazelnut_FGeneral_h
#define Hazelnut_FGeneral_h

#include <cocos2d.h>
#include "FUtil.h"

USING_NS_CC;

//==================================================
// Warning

// compiler_warning.h
#define STRINGISE_IMPL(x) #x
#define STRINGISE(x) STRINGISE_IMPL(x)

// Use: #pragma message WARN("My message")
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#   define FILE_LINE_LINK __FILE__ "(" STRINGISE(__LINE__) ") : "
#   define WARN(exp) (FILE_LINE_LINK "WARNING: " exp)
#else//__GNUC__ - may need other defines for different compilers
#   define WARN(exp) ("WARNING: " exp)
#endif

//==================================================
// Deprecated
#ifdef __GNUC__
#define DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif


//==================================================
// Inline

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#    define FORCEINLINE __forceinline
#else
#    define FORCEINLINE __attribute__((always_inline)) inline
#endif

//we use C++11, here are selfmade C++14 features
namespace std14
{
    template<typename T, typename ...Args>
    FORCEINLINE
    std::unique_ptr<T> make_unique( Args&& ...args )
    {
        return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
    }
}


#endif
