/*
	Vector.h使用方法：
		实例化	vector(_Type) _Vector = new(vector(_Type));
		调用方法
			_Vector.type()					=>	返回当前容器包含元素的类型(字符串形式)
			_Vector.size()					=>	返回当前容器中元素的数目
			_Vector.capacity()				=>	返回当前容器的容量
			_Vector.isEmpty()				=>	判断当前容器是否为空
			_Vector.pop()					=>	删除容器最后一个元素，并返回之
			_Vector.shift()					=>	删除容器第一个元素，并返回之
			_Vector.pull(_Index)			=>	删除容器第_Index个元素，并返回之
			_Vector.first()					=>	返回容器第一个元素的地址
			_Vector.last()					=>	返回容器最后一个元素的地址
			_Vector.at(_Index)				=>	返回容器第_Index个元素的地址
			_Vector.indexOf(_Data)			=>	返回_Data在容器中第一次出现的索引；若_Data在容器中未出现，则返回-1
			_Vector.lastIndexOf(_Data)		=>	返回_Data在容器中最后一次出现的索引；若_Data在容器中未出现，则返回-1
			_Vector.push(_Data)				=>	在容器最后一个元素后压入元素_Data，返回this
			_Vector.unshift(_Data)			=>	在容器第一个元素前压入元素_Data，返回this
			_Vector.insert(_Data, _Index)	=>	在容器第(_Index - 1)和第_Index个元素之间插入元素_Data，返回this
			_Vector.setCmp(_Func)			=>	设置用于排序的比较函数；若在排序前不设置，则默认将元素按ASCII升序排序
			_Vector.erase(_Data)			=>	删除容器中所有的_Data元素
			_Vector.traversal(_S, _E, _F)	=>	使用_F函数对容器从第_S个元素到第_E个元素进行遍历
			_Vector.resize(_Size)			=>	重新设置容器的容量
			_Vector.sort()					=>	使用当前用于排序的比较函数进行排序
			_Vector.reverse()				=>	反转容器
			_Vector.clear()					=>	清除容器中存储的元素，不释放内存
			_Vector.delete()				=>	释放内存
		注意事项
			从容器中获取元素(或其地址/索引)时，请保证容器非空
			根据索引查元素时，请保证索引合法
			使用new实例化vector后，请在使用完毕后调用delete，否则有可能造成内存泄漏
 */
#ifndef TEMPLATE_VECTOR_H
	#define TEMPLATE_VECTOR_H

	#include "core/template.h"
	#include "Macro.h"
	#define _Vector_Init_Size 0x100
	#define vector_(T) T##_vector
	#define vector(T) vector_(T)

	#define vector_config(T)\
		typedef struct vector(T) vector(T);\
		struct vector(T) {\
			char*				(*type)			();\
			unsigned int		(*size)			();\
			unsigned int		(*capacity)		();\
			bool				(*isEmpty)		();\
			T					(*pop)			();\
			T					(*shift)		();\
			T					(*pull)			(unsigned int);\
			T*					(*first)		();\
			T*					(*last)			();\
			T*					(*at)			(unsigned int);\
			int					(*indexOf)		(T);\
			int					(*lastIndexOf)	(T);\
			vector(T)			(*push)			(T);\
			vector(T)			(*unshift)		(T);\
			vector(T)			(*insert)		(T, unsigned int);\
			vector(T)			(*setCmp)		(int (*)(const void*, const void*));\
			vector(T)			(*erase)		(T);\
			vector(T)			(*traversal)	(unsigned int, unsigned int, void (*)(T*));\
			vector(T)			(*resize)		(unsigned int);\
			vector(T)			(*sort)			();\
			vector(T)			(*reverse)		();\
			vector(T)			(*clear)		();\
			vector(T)			(*delete)		();\
		};
	
	#define __VECTOR_FUNCTION_BODY(T)\
		int _CmpFunc(const void *a, const void *b) {\
			return memcmp(a, b, sizeof(T));\
		}\
		char *type() {\
			return tostring(vector(T));\
		}\
		unsigned int size() {\
			return length;\
		}\
		unsigned int capacity() {\
			return maxsize;\
		}\
		bool isEmpty() {\
			return !length;\
		}\
		T pop() {\
			_AutoMemSub(T);\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return vector[--length];\
		}\
		T shift() {\
			_AutoMemSub(T);\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			T re = vector[0];\
			memmove(vector, vector + 1, --length * sizeof(T));\
			return re;\
		}\
		T pull(unsigned int index) {\
			_AutoMemSub(T);\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			T re = vector[index];\
			memmove(vector + index, vector + index + 1, (--length - index) * sizeof(T));\
			return re;\
		}\
		T* first() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return vector;\
		}\
		T* last() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return vector + length - 1;\
		}\
		T* at(unsigned int index) {\
			if(!length || index >= length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return vector + index;\
		}\
		int indexOf(T data) {\
			register unsigned int i;\
			for(i = 0; i < length; ++i) {\
				if(memcmp(&data, &vector[i], sizeof(T)) == 0) return i;\
			}\
			return -1;\
		}\
		int lastIndexOf(T data) {\
			register unsigned int i;\
			for(i = length - 1;; --i) {\
				if(memcmp(&data, &vector[i], sizeof(T)) == 0) return i;\
				if(!i) break;\
			}\
			return -1;\
		}\
		vector(T) push(T data) {\
			_AutoMemAdd(T);\
			vector[length++] = data;\
			return this;\
		}\
		vector(T) unshift(T data) {\
			_AutoMemAdd(T);\
			memmove(vector + 1, vector, sizeof(T) * length++);\
			vector[0] = data;\
			return this;\
		}\
		vector(T) insert(T data, unsigned int index) {\
			_AutoMemAdd(T);\
			if(index >= length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			memmove(vector + index + 1, vector + index, (length - index) * sizeof(T));\
			vector[index] = data;\
			length++;\
			return this;\
		}\
		vector(T) setCmp(int (*cmpFunc)(const void*, const void*)) {\
			_cmp = cmpFunc;\
			return this;\
		}\
		vector(T) erase(T data) {\
			register unsigned int i;\
			for(i = 0; i < length; ++i) {\
				while(memcmp(&data, &vector[i], sizeof(T)) == 0) {\
					this.pull(i);\
				}\
			}\
			return this;\
		}\
		vector(T) traversal(unsigned int from, unsigned int to, void (*func)(T*)) {\
			if(from >= length || to >= length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			register unsigned int i;\
			if(from <= to) for(i = from; i <= to; ++i) {\
				(*func)(&vector[i]);\
			} else for(i = from;; --i) {\
				(*func)(&vector[i]);\
				if(i == to) break;\
			}\
			return this;\
		}\
		vector(T) resize(unsigned int size) {\
			realloc_space(vector, T, size);\
			maxsize = size;\
			if(maxsize < length) length = maxsize;\
			return this;\
		}\
		vector(T) sort() {\
			qsort(vector, length, sizeof(T), _cmp);\
			return this;\
		}\
		vector(T) reverse() {\
			register int l = -1, r = length;\
			while(++l < --r) swap(vector[l], vector[r]);\
			return this;\
		}\
		vector(T) clear() {\
			length = 0;\
			return this;\
		}\
		vector(T) delete() {\
			free(vector);\
			length = maxsize = 0;\
			return this;\
		}\
	
	#define _AutoMemAdd(T) ({\
		while(maxsize <= length) {\
			realloc_space(vector, T, maxsize + _Vector_Init_Size);\
			maxsize += _Vector_Init_Size;\
		}\
	})

	#define _AutoMemSub(T) ({\
		while(maxsize - length > _Vector_Init_Size) {\
			realloc_space(vector, T, maxsize - _Vector_Init_Size);\
			maxsize -= _Vector_Init_Size;\
		}\
	})

	#define __VECTOR_FUNCTION_ASSIGN\
		this.type = type;\
		this.size = size;\
		this.capacity = capacity;\
		this.isEmpty = isEmpty;\
		this.pop = pop;\
		this.shift = shift;\
		this.pull = pull;\
		this.first = first;\
		this.last = last;\
		this.at = at;\
		this.indexOf = indexOf;\
		this.lastIndexOf = lastIndexOf;\
		this.push = push;\
		this.unshift = unshift;\
		this.insert = insert;\
		this.setCmp = setCmp;\
		this.erase = erase;\
		this.traversal = traversal;\
		this.resize = resize;\
		this.sort = sort;\
		this.reverse = reverse;\
		this.clear = clear;\
		this.delete = delete;

	#define new_vector(T) ({\
		T *vector = NULL;\
		unsigned int length = 0;\
		unsigned int maxsize = 0;\
		int (*_cmp)(const void*, const void*);\
		vector(T) this;\
		__VECTOR_FUNCTION_BODY(T);\
		_cmp = _CmpFunc;\
		__VECTOR_FUNCTION_ASSIGN;\
		this;\
	})

#endif