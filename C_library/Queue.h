/*
	Queue.h使用方法
		实例化	queue(_Type) _Queue = new(queue(_Type, _Size));
		调用方法
			_Queue.type()					=>	返回当前队包含的元素类型(字符串形式)
			_Queue.size()					=>	返回当前队中元素的数目
			_Queue.capacity()				=>	返回当前队的容量
			_Queue.isEmpty()				=>	判断队是否为空
			_Queue.isFull()					=>	判断队是否为满
			_Queue.contain(_Data)			=>	判断队中是否有元素_Data
			_Queue.pop()					=>	删除队首元素，并返回之
			_Queue.front()					=>	返回队首元素
			_Queue.back()					=>	返回队尾元素
			_Queue.push(_Data)				=>	将元素_Data入队，返回this
			_Queue.traversal(_Func)			=>	使用_Func函数对队中的每个元素进行遍历
			_Queue.clear()					=>	清空队
		注意事项
			从队中获取元素时，请确保队非空
			向队中压入元素时，请确保队非满
 */
#ifndef TEMPLATE_QUEUE_H
	#define TEMPLATE_QUEUE_H

	#include "core/template.h"
	#include "Macro.h"
	#define queue(T) T##_queue

	#define queue_config(T)\
		typedef struct queue(T) queue(T);\
		struct queue(T) {\
			char*				(*type)			();\
			unsigned int		(*size)			();\
			unsigned int		(*capacity)		();\
			bool				(*isEmpty)		();\
			bool				(*isFull)		();\
			bool				(*contain)		(T);\
			T					(*pop)			();\
			T					(*front)		();\
			T					(*back)			();\
			queue(T)			(*push)			(T);\
			queue(T)			(*traversal)	(void (*)(T));\
			queue(T)			(*clear)		();\
		};

	#define __QUEUE_FUNCTION_BODY(T, QUEUE_SIZE)\
		char *type() {\
			return tostring(queue(T));\
		}\
		unsigned int size() {\
			return count;\
		}\
		unsigned int capacity() {\
			return QUEUE_SIZE;\
		}\
		bool isEmpty() {\
			return !count;\
		}\
		bool isFull() {\
			return count >= QUEUE_SIZE;\
		}\
		bool contain(T data) {\
			register unsigned int i, j;\
			for(i = 0, j = first; i < count; ++i, j = (j + 1) % QUEUE_SIZE) {\
				if(memcmp(&data, &queue[j], sizeof(T)) == 0) return true;\
			}\
			return false;\
		}\
		T pop() {\
			if(!count) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			T re = queue[first];\
			count--;\
			first = (first + 1) % QUEUE_SIZE;\
			return re;\
		}\
		T front() {\
			if(!count) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return queue[first];\
		}\
		T back() {\
			if(!count) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return queue[last];\
		}\
		queue(T) push(T data) {\
			if(count >= QUEUE_SIZE) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			last = (last + 1) % QUEUE_SIZE;\
			queue[last] = data;\
			count++;\
			return this;\
		}\
		queue(T) traversal(void (*func)(T)) {\
			register unsigned int i, j;\
			for(i = 0, j = first; i < count; ++i, j = (j + 1) % QUEUE_SIZE) {\
				(*func)(queue[j]);\
			}\
			return this;\
		}\
		queue(T) clear() {\
			count = 0;\
			first = 0;\
			last = QUEUE_SIZE - 1;\
			return this;\
		}\

	#define __QUEUE_FUNCTION_ASSIGN\
		this.type = type;\
		this.size = size;\
		this.capacity = capacity;\
		this.isEmpty = isEmpty;\
		this.isFull = isFull;\
		this.contain = contain;\
		this.pop = pop;\
		this.front = front;\
		this.back = back;\
		this.push = push;\
		this.traversal = traversal;\
		this.clear = clear;

	#define new_queue(T, QUEUE_SIZE) ({\
		T queue[QUEUE_SIZE];\
		unsigned int count = 0;\
		unsigned int first = 0, last = QUEUE_SIZE - 1;\
		queue(T) this;\
		__QUEUE_FUNCTION_BODY(T, QUEUE_SIZE);\
		__QUEUE_FUNCTION_ASSIGN;\
		this;\
	})


#endif