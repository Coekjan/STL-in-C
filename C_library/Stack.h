/*
	Stack.h使用方法：
		实例化	stack(_Type) _Stack = new(stack(_Type, _Size));
		调用方法
			_Stack.type()					=>	返回当前栈包含元素的类型(字符串形式)
			_Stack.size()					=>	返回当前栈中元素的数目
			_Stack.capacity()				=>	返回当前栈的容量
			_Stack.isEmpty()				=>	判断栈是否为空
			_Stack.isFull()					=>	判断栈是否为满
			_Stack.contain(_Data)			=>	判断栈中是否包含元素_Data
			_Stack.pop()					=>	删除栈顶元素，并返回之
			_Stack.top()					=>	返回栈顶元素
			_Stack.push(_Data)				=>	在栈中压入元素_Data，返回this
			_Stack.traversal(_Func)			=>	使用_Func函数对栈中每个元素进行遍历
			_Stack.clear()					=>	清空栈
		注意事项
			从栈中获取元素时，请确保栈非空
			向栈中压入元素时，请确保栈非满
 */
#ifndef TEMPLATE_STACK_H
	#define TEMPLATE_STACK_H

	#include "core/template.h"
	#include "Macro.h"
	#define stack_(T) T##_stack
	#define stack(T) stack_(T)

	#define stack_config(T)\
		typedef struct stack(T) stack(T);\
		struct stack(T) {\
			char*				(*type)			();\
			unsigned int		(*size)			();\
			unsigned int		(*capacity)		();\
			bool				(*isEmpty)		();\
			bool				(*isFull)		();\
			bool				(*contain)		(T);\
			T					(*pop)			();\
			T					(*top)			();\
			stack(T)			(*push)			(T);\
			stack(T)			(*traversal)	(void (*)(T));\
			stack(T)			(*clear)		();\
		};

	#define __STACK_FUNCTION_BODY(T, STACK_SIZE)\
		char *type() {\
			return tostring(stack(T));\
		}\
		unsigned int size() {\
			return length;\
		}\
		unsigned int capacity() {\
			return STACK_SIZE;\
		}\
		bool isEmpty() {\
			return !length;\
		}\
		bool isFull() {\
			return length >= STACK_SIZE;\
		}\
		bool contain(T data) {\
			register int i;\
			for(i = 0; i < length; ++i) {\
				if(memcmp(&data, &stack[i], sizeof(T)) == 0) return true;\
			}\
			return false;\
		}\
		T pop() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return stack[--length];\
		}\
		T top() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return stack[length - 1];\
		}\
		stack(T) push(T data) {\
			if(length >= STACK_SIZE) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			stack[length++] = data;\
			return this;\
		}\
		stack(T) traversal(void (*func)(T)) {\
			register int i;\
			for(i = 0; i < length; ++i) {\
				(*func)(stack[i]);\
			}\
			return this;\
		}\
		stack(T) clear() {\
			length = 0;\
			return this;\
		}

	#define __STACK_FUNCTION_ASSIGN\
		this.type = type;\
		this.size = size;\
		this.capacity = capacity;\
		this.isEmpty = isEmpty;\
		this.isFull = isFull;\
		this.contain = contain;\
		this.pop = pop;\
		this.top = top;\
		this.push = push;\
		this.traversal = traversal;\
		this.clear = clear;

	#define new_stack(T, STACK_SIZE) ({\
		T stack[STACK_SIZE];\
		unsigned int length = 0;\
		stack(T) this;\
		__STACK_FUNCTION_BODY(T, STACK_SIZE);\
		__STACK_FUNCTION_ASSIGN;\
		this;\
	})

#endif