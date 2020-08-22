/*
	Ultility.h提供了一个泛型结构pair(T, U)
		目前该结构用于Map.h中
		目前该结构不支持嵌套使用
 */
#ifndef TEMPLATE_ULTILITY_H
	#define TEMPLATE_ULTILITY_H

	#include "core/template.h"
	
	#define pair(T, U) T##_##U##_pair

	#define pair_config(T, U)\
		typedef struct pair(T, U) pair(T, U);\
		struct pair(T, U) {\
			T first;\
			U second;\
		};


#endif