/*
	template.h提供了一系列宏，方便实现模板化数据结构与算法
 */
#ifndef __GNUC__
	#error 'C_library' only support GNU C Compiler.
#endif
#ifndef TEMPLATE_H
	#define TEMPLATE_H

	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
	#include <stdbool.h>

	#define new(type)					new##_##type

	#define config(st, t1, ...)			st##_config( t1 ,##__VA_ARGS__ )

	#define _tostring(x)				#x
	#define tostring(x)					_tostring(x)
	#define _tochar(x)					*#x
	#define tochar(x)					_tochar(x)

#endif
