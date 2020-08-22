/*
	Heap.h使用方法
		实例化	heap(_Type) _Heap = new(heap(_Type, _Size, _CMP_Func));
		调用方法
			_Heap.type()					=>	返回当前堆包含的元素类型(字符串形式)
			_Heap.size()					=>	返回当前堆中元素的数目
			_Heap.capacity()				=>	返回当前堆的容量
			_Heap.isEmpty()					=>	判断当前堆是否为空
			_Heap.isFull()					=>	判断当前堆是否为满
			_Heap.contain(_Data)			=>	判断当前堆中是否有元素_Data
			_Heap.top()						=>	返回堆顶元素
			_Heap.pop()						=>	删除堆顶元素，并返回之
			_Heap.insert(_Data)				=>	在堆中插入元素_Data
			_Heap.traversal(_Func)			=>	使用_Func函数对堆中每个元素进行遍历
			_Heap.clear()					=>	清空堆
		注意事项
			实例化中第2个参数为堆的最大容量
			第3个参数为一个函数
				函数类型为int (*)(_Type __Arg_1, _Type __Arg_2)
				返回值为负数时，__Arg_1将置于__Arg_2的上方(堆顶为所有元素的上方，堆顶的两个子堆也满足此性质)
			从堆中获取元素时，请确保堆非空
			向堆中插入元素时，请确保堆非满
 */
#ifndef TEMPLATE_HEAP_H
	#define TEMPLATE_HEAP_H

	#include "core/template.h"
	#include "Macro.h"
	#define heap_(T) T##_heap
	#define heap(T) heap_(T)

	#define heap_config(T)\
		typedef struct heap(T) heap(T);\
		struct heap(T) {\
			char*				(*type)			();\
			unsigned int		(*size)			();\
			unsigned int		(*capacity)		();\
			bool				(*isEmpty)		();\
			bool				(*isFull)		();\
			bool				(*contain)		(T);\
			T					(*top)			();\
			T					(*pop)			();\
			heap(T)				(*insert)		(T);\
			heap(T)				(*traversal)	(void (*)(T));\
			heap(T)				(*clear)		();\
		};

	#define __HEAP_FUNCTION_BODY(T, HEAP_SIZE, CMP_FUNC)\
		char *type() {\
			return tostring(heap(T));\
		}\
		unsigned int size() {\
			return length;\
		}\
		unsigned int capacity() {\
			return HEAP_SIZE;\
		}\
		bool isEmpty() {\
			return !length;\
		}\
		bool isFull() {\
			return length >= HEAP_SIZE;\
		}\
		bool contain(T data) {\
			register unsigned int i;\
			for(i = 0; i < length; ++i) {\
				if(memcmp(&data, &heap[i], sizeof(T)) == 0) return true;\
			}\
			return false;\
		}\
		T top() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return heap[0];\
		}\
		T pop() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			T re = heap[0];\
			swap(heap[0], heap[length - 1]);\
			length--;\
			_Adjust(T, 0, length, CMP_FUNC);\
			return re;\
		}\
		heap(T) insert(T data) {\
			if(length >= HEAP_SIZE) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			unsigned int i, p = 0;\
			heap[i = length] = data;\
			length++;\
			while(i) {\
				p = (i - 1) >> 1;\
				if(CMP_FUNC(heap[p], heap[i]) > 0) {\
					swap(heap[p], heap[i]);\
					i = p;\
				} else break;\
			}\
			return this;\
		}\
		heap(T) traversal(void (*func)(T)) {\
			register unsigned int i;\
			for(i = 0; i < length; ++i) {\
				(*func)(heap[i]);\
			}\
			return this;\
		}\
		heap(T) clear() {\
			length = 0;\
			return this;\
		}

	#define _Adjust(T, i, n, CMP_FUNC) ({\
		unsigned int j = (i << 1) + 1;\
		T temp = heap[i];\
		while(j < n) {\
			if(j + 1 < n && CMP_FUNC(heap[j], heap[j + 1]) > 0) ++j;\
			if(CMP_FUNC(temp, heap[j]) > 0) {\
				heap[(j - 1) >> 1] = heap[j];\
				j = (j << 1) + 1;\
			} else break;\
		}\
		heap[(j - 1) >> 1] = temp;\
	})

	#define __HEAP_FUNCTION_ASSIGN\
		this.type = type;\
		this.size = size;\
		this.capacity = capacity;\
		this.isEmpty = isEmpty;\
		this.isFull = isFull;\
		this.contain = contain;\
		this.top = top;\
		this.pop = pop;\
		this.insert = insert;\
		this.traversal = traversal;\
		this.clear = clear;

	#define new_heap(T, HEAP_SIZE, CMP_FUNC) ({\
		T heap[HEAP_SIZE];\
		unsigned int length = 0;\
		heap(T) this;\
		__HEAP_FUNCTION_BODY(T, HEAP_SIZE, CMP_FUNC);\
		__HEAP_FUNCTION_ASSIGN;\
		this;\
	})

#endif