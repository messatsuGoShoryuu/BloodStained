#ifndef BS_DEFINE_H
#define BS_DEFINE_H

//math
#define		BS_REAL				f32
#define		BS_MAX_FLOAT		1.0E8
#define		BS_PI				3.1415927
#define		BS_DEG_TO_RAD		0.01745329251
#define		BS_RAD_TO_DEG		57.2957795131

//index
#define		BS_INVALID_INDEX	0xFFFFFFFF

//container settings
#define		BS_MINIMUM_ARRAY_ALLOC	8

//debug settings
#define		BS_ASSERT
#define		BS_PROFILE_MEMORY

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

#endif // !BS_DEFINE_H
