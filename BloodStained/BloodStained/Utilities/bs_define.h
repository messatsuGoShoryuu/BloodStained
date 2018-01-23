#ifndef _BS_DEFINE_H_
#define _BS_DEFINE_H_


//math
#define		BS_REAL				f32
#define		BS_MAX_FLOAT		1.0E8
#define		BS_FLOAT_0			1.0E-7
#define		BS_PI				3.1415926535897932384626433832795
#define		BS_DEG_TO_RAD		0.01745329251994329576923690768489
#define		BS_RAD_TO_DEG		57.295779513082320876798154814105

//index
#define		BS_INVALID_INDEX	0xFFFFFFFF

//container settings
#define		BS_MINIMUM_ARRAY_ALLOC	8

//debug settings
#define		BS_ASSERT

//multiple argument templates
#define MULTIPLE_ARGS_1 Arg0 arg0
#define MULTIPLE_ARGS_2 MULTIPLE_ARGS_1, Arg1 arg1
#define MULTIPLE_ARGS_3 MULTIPLE_ARGS_2, Arg2 arg2
#define MULTIPLE_ARGS_4 MULTIPLE_ARGS_3, Arg3 arg3
#define MULTIPLE_ARGS_5 MULTIPLE_ARGS_4, Arg4 arg4
#define MULTIPLE_ARGS_6 MULTIPLE_ARGS_5, Arg5 arg5

#define MULTIPLE_PARAMS_1 arg0
#define MULTIPLE_PARAMS_2 MULTIPLE_PARAMS_1, arg1
#define MULTIPLE_PARAMS_3 MULTIPLE_PARAMS_2, arg2
#define MULTIPLE_PARAMS_4 MULTIPLE_PARAMS_3, arg3
#define MULTIPLE_PARAMS_5 MULTIPLE_PARAMS_4, arg4
#define MULTIPLE_PARAMS_6 MULTIPLE_PARAMS_5, arg5

#define MULTIPLE_TYPES_1 typename Arg0
#define MULTIPLE_TYPES_2 MULTIPLE_TYPES_1, typename Arg1
#define MULTIPLE_TYPES_3 MULTIPLE_TYPES_2, typename Arg2
#define MULTIPLE_TYPES_4 MULTIPLE_TYPES_3, typename Arg3
#define MULTIPLE_TYPES_5 MULTIPLE_TYPES_4, typename Arg4
#define MULTIPLE_TYPES_6 MULTIPLE_TYPES_5, typename Arg5


//Non pointer this
#define SELF (*this)


//Undecorated function name
#if _MSC_VER
#include <crtdefs.h>
#define BS_UNDECORATED_FUNCTION __FUNCTION__
#endif

//OGL draw types
#define	BS_DRAWTYPE_STATIC	GL_STATIC_DRAW
#define BS_DRAWTYPE_DYNAMIC	GL_DYNAMIC_DRAW
#define BS_DRAWTYPE_STREAM	GL_STREAM_DRAW


//Debug
#ifdef _DEBUG
#define BS_DEBUG_BUILD
#endif

#pragma warning( disable : 4267 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )

#endif // !BS_DEFINE_H
