/*
	Macro.h提供了一系列常用宏
		type_str(_Var)						=>	返回一个字符串字面量，内容是_Var的类型(仅支持基本数据类型)
		swap(_A, _B)						=>	交换两个变量的值
		swap_space(_A, _B, _Size)			=>	交换两个内存空间内的值
		malloc_space(_Ptr, _Type, _N)		=>	为_Ptr申请一片内存区域，区域大小为_N * sizeof(_Type)
		realloc_space(_Ptr, _Type, _N)		=>	为_Ptr重新申请一片内存区域，区域大小为_N * sizeof(_Type)
	注意事项
		swap和swap_space的参数_A/_B，malloc_space和realloc_space的参数_Ptr必须为变量本身，不允许出现表达式(尤其是有副作用的表达式)
		使用realloc_space的对象，必须已经经过malloc_space申请内存
 */
#ifndef MACRO_H
	#define MACRO_H

	#define type_str(v)					_Generic((v),\
										signed char							: "signed char",\
										char								: "char",\
										int									: "int",\
										short								: "short",\
										long								: "long",\
										long long							: "long long",\
										bool								: "bool",\
										unsigned char						: "unsigned char",\
										unsigned int						: "unsigned int",\
										unsigned short						: "unsigned char",\
										unsigned long						: "unsigned long",\
										unsigned long long					: "unsigned long long",\
										float								: "float",\
										double								: "double",\
										long double							: "long double",\
										signed char*						: "signed char*",\
										char*								: "char*",\
										int*								: "int*",\
										short*								: "short*",\
										long*								: "long*",\
										long long*							: "long long*",\
										bool*								: "bool*",\
										unsigned char*						: "unsigned char*",\
										unsigned int*						: "unsigned int*",\
										unsigned short*						: "unsigned char*",\
										unsigned long*						: "unsigned long*",\
										unsigned long long*					: "unsigned long long*",\
										float*								: "float*",\
										double*								: "double*",\
										long double*						: "long double*",\
										void*								: "void*",\
										default								: "other"\
	)

	#define swap(a, b)					do{\
										typeof(a) _Temp = a;\
										a = b;\
										b = _Temp;\
	} while(0)

	#define swap_space(a, b, size)		({\
										int _Size = (size);\
										char _Buffer[_Size];\
										memmove(_Buffer, (a), _Size);\
										memmove((a), (b), _Size);\
										memmove((b), _Buffer, _Size);\
	})

	#define malloc_space(ptr, type, n)	({\
										ptr = (type*)malloc(sizeof(type) * (n));\
										if(!ptr) {\
																			printf("Error : The Function '%s' in File '%s' fails to MALLOC for %s.\n",\
																													__func__,\
																													__FILE__,\
																													tostring(ptr)\
																			);\
																			exit(0);\
										}\
	})

	#define realloc_space(ptr, type, n)	({\
										void *_New_Ptr = realloc(ptr, sizeof(type) * (n));\
										if(!_New_Ptr) {\
																			printf("Error : The Function '%s' in File '%s' fails to REALLOC for %s.\n",\
																													__func__,\
																													__FILE__,\
																													tostring(ptr)\
																			);\
																			exit(0);\
										} else ptr = (type*)_New_Ptr;\
	})

#endif