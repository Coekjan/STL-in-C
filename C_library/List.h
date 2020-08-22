/*
	List.h使用方法
		实例化	list(_Type) _List = new(list(_Type));
		调用方法
			_List.type()					=>	返回当前列表包含元素的类型(字符串形式)
			_List.size()					=>	返回当前列表中元素的数目
			_List.isEmpty()					=>	判断当前列表是否为空
			_List.pop()						=>	删除列表最后一个元素，并返回之
			_List.shift()					=>	删除列表第一个元素，并返回之
			_List.pull(_Index)				=>	删除列表第_Index个元素，并返回之
			_List.first()					=>	返回列表第一个元素的地址
			_List.last()					=>	返回列表最后一个元素的地址
			_List.at(_Index)				=>	返回列表第_Index个元素的地址
			_List.indexOf(_Data)			=>	返回_Data元素在列表中第一次出现的索引；若_Data在列表中未出现，则返回-1
			_List.lastIndexOf(_Data)		=>	返回_Data元素在列表中最后一次出现的索引；若_Data在列表中未出现，则返回-1
			_List.push(_Data)				=>	在列表最后一个元素后压入元素_Data，返回this
			_List.unshift(_Data)			=>	在列表第一个元素前压入元素_Data，返回this
			_List.insert(_Data, _Index)		=>	在列表第(_Index - 1)和第_Index个元素之间插入元素_Data，返回this
			_List.setCmp(_Func)				=>	设置用于排序的比较函数；若在排序前不设置，则默认将元素按ASCII升序排序
			_List.erase(_Data)				=>	删除列表中所有的_Data元素
			_List.traversal(_Func)			=>	使用_Func函数对列表每个元素进行遍历
			_List.sort()					=>	使用当前用于排序的比较函数进行排序
			_List.reverse()					=>	反转列表
			_List.delete()					=>	删除列表
		注意事项
			从列表中获取元素(或其地址/索引)时，请保证列表非空
			根据索引查元素时，请保证索引合法
			使用new实例化list后，请在使用完毕后调用delete，否则有可能造成内存泄漏
 */
#ifndef TEMPLATE_LIST_H
	#define TEMPLATE_LIST_H

	#include "core/template.h"
	#include "Macro.h"

	#define list_(T) T##_list
	#define list(T) list_(T)
	#define list_node_(T) T##_list_node
	#define list_node(T) list_node_(T)

	#define list_config(T)\
		typedef struct list_node(T) list_node(T);\
		struct list_node(T) {\
			list_node(T)			*prev;\
			list_node(T)			*next;\
			T					data;\
		};\
		typedef struct list(T) list(T);\
		struct list(T) {\
			char*				(*type)			();\
			unsigned int		(*size)			();\
			bool				(*isEmpty)		();\
			T					(*pop)			();\
			T					(*shift)		();\
			T					(*pull)			(unsigned int);\
			T*					(*first)		();\
			T*					(*last)			();\
			T*					(*at)			(unsigned int);\
			int					(*indexOf)		(T);\
			int					(*lastIndexOf)	(T);\
			list(T)				(*push)			(T);\
			list(T)				(*unshift)		(T);\
			list(T)				(*insert)		(T, unsigned int);\
			list(T)				(*setCmp)		(int (*)(T, T));\
			list(T)				(*erase)		(T);\
			list(T)				(*traversal)	(void (*)(T*));\
			list(T)				(*sort)			();\
			list(T)				(*reverse)		();\
			void				(*delete)		();\
		};

	#define __LIST_FUNCTION_BODY(T)\
		int _CmpFunc(T a, T b) {\
			return memcmp(&a, &b, sizeof(T));\
		}\
		list_node(T) *_Merge(list_node(T) *h1, list_node(T) *h2) {\
			if(h1 == NULL) return h2;\
			if(h2 == NULL) return h1;\
			register list_node(T) *p;\
			list_node(T) *res;\
			if((*_cmp)(h1->data, h2->data) < 0) {\
				res = h1;\
				h1 = h1->next;\
			} else {\
				res = h2;\
				h2 = h2->next;\
			}\
			p = res;\
			while(h1 != NULL && h2 != NULL) {\
				if((*_cmp)(h1->data, h2->data) < 0) {\
					p->next = h1;\
					h1 = h1->next;\
				} else {\
					p->next = h2;\
					h2 = h2->next;\
				}\
				p->next->prev = p;\
				p = p->next;\
			}\
			if(h1 == NULL) {\
				p->next = h2;\
				h2->prev = p;\
			} else {\
				p->next = h1;\
				h1->prev = p;\
			}\
			return res;\
		}\
		list_node(T) *_MergeSort(list_node(T) *h) {\
			if(h == NULL || h->next == NULL) return h;\
			register list_node(T) *f, *s;\
			f = s = h;\
			while(f->next != NULL && f->next->next != NULL) {\
				f = f->next->next;\
				s = s->next;\
			}\
			f = s;\
			s = s->next;\
			f->next = NULL;\
			f = _MergeSort(h);\
			s = _MergeSort(s);\
			return _Merge(f, s);\
		}\
		char *type() {\
			return tostring(list(T));\
		}\
		unsigned int size() {\
			return length;\
		}\
		bool isEmpty() {\
			return !length;\
		}\
		T pop() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			list_node(T) *node = head->prev;\
			T temp = node->data;\
			node->next->prev = node->prev;\
			node->prev->next = node->next;\
			free(node);\
			length--;\
			return temp;\
		}\
		T shift() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			list_node(T) *node = head->next;\
			T temp = node->data;\
			node->next->prev = node->prev;\
			node->prev->next = node->next;\
			free(node);\
			length--;\
			return temp;\
		}\
		T pull(unsigned int index) {\
			if(!length || index >= length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			register list_node(T) *node = head->next;\
			register unsigned int i;\
			for(i = 0; i < index; ++i, node = node->next);\
			T temp = node->data;\
			node->next->prev = node->prev;\
			node->prev->next = node->next;\
			free(node);\
			length--;\
			return temp;\
		}\
		T *first() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return &head->next->data;\
		}\
		T *last() {\
			if(!length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			return &head->prev->data;\
		}\
		T* at(unsigned int index) {\
			if(!length || index >= length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			register list_node(T) *node = head->next;\
			register unsigned int i;\
			for(i = 0; i < index; ++i, node = node->next);\
			return &node->data;\
		}\
		int indexOf(T data) {\
			register int i = 0;\
			register list_node(T) *node = head->next;\
			while(node != head) {\
				if(memcmp(&data, &node->data, sizeof(T)) == 0) return i;\
				node = node->next;\
				++i;\
			}\
			return -1;\
		}\
		int lastIndexOf(T data) {\
			register int i = length - 1;\
			register list_node(T) *node = head->prev;\
			while(node != head) {\
				if(memcmp(&data, &node->data, sizeof(T)) == 0) return i;\
				node = node->prev;\
				--i;\
			}\
			return -1;\
		}\
		list(T) push(T data) {\
			list_node(T) *node = NULL;\
			malloc_space(node, list_node(T), 1);\
			node->data = data;\
			node->next = head;\
			node->prev = head->prev;\
			head->prev->next = node;\
			head->prev = node;\
			length++;\
			return this;\
		}\
		list(T) unshift(T data) {\
			list_node(T) *node = NULL;\
			malloc_space(node, list_node(T), 1);\
			node->data = data;\
			node->next = head->next;\
			node->prev = head;\
			head->next->prev = node;\
			head->next = node;\
			length++;\
			return this;\
		}\
		list(T) insert(T data, unsigned int index) {\
			if(index >= length) {\
				printf("Error : Illegal memmory-visit in the Function '%s' in File '%s'.",\
					__func__,\
					__FILE__\
				);\
				exit(0);\
			}\
			register list_node(T) *p = head->next;\
			register unsigned int i;\
			for(i = 0; i < index; ++i, p = p->next);\
			list_node(T) *node = NULL;\
			malloc_space(node, list_node(T), 1);\
			node->data = data;\
			node->next = p;\
			node->prev = p->prev;\
			p->prev->next = node;\
			p->prev = node;\
			length++;\
			return this;\
		}\
		list(T) setCmp(int (*cmpFunc)(T, T)) {\
			_cmp = cmpFunc;\
			return this;\
		}\
		list(T) erase(T data) {\
			register list_node(T) *node = head->next, *p = NULL;\
			while(node != head) {\
				if(memcmp(&data, &node->data, sizeof(T)) == 0) {\
					p = node->next;\
					node->prev->next = node->next;\
					node->next->prev = node->prev;\
					free(node);\
					node = p;\
				} else node = node->next;\
			}\
			return this;\
		}\
		list(T) traversal(void (*func)(T*)) {\
			register list_node(T) *node = head->next;\
			while(node != head) {\
				(*func)(&node->data);\
				node = node->next;\
			}\
			return this;\
		}\
		list(T) sort() {\
			head->prev->next = NULL;\
			head->next = _MergeSort(head->next);\
			head->next->prev = head;\
			register list_node(T) *p;\
			for(p = head->next; p->next != NULL; p = p->next);\
			head->prev = p;\
			p->next = head;\
			return this;\
		}\
		list(T) reverse() {\
			list_node(T) *front, *back;\
			front = head->prev;\
			back = head->next;\
			while(front != back && front->next != back) {\
				swap(front->data, back->data);\
				front = front->prev;\
				back = back->next;\
			}\
			return this;\
		}\
		void delete() {\
			while(length) pop();\
			free(head);\
			head = NULL;\
		}\

	#define __LIST_FUNCTION_ASSIGN\
		this.type = type;\
		this.size = size;\
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
		this.sort = sort;\
		this.reverse = reverse;\
		this.delete = delete;\

	#define new_list(T) ({\
		unsigned int length = 0;\
		list(T) this;\
		list_node(T) *head = NULL;\
		int (*_cmp)(T, T);\
		malloc_space(head, list_node(T), 1);\
		head->prev = head;\
		head->next = head;\
		__LIST_FUNCTION_BODY(T);\
		_cmp = _CmpFunc;\
		__LIST_FUNCTION_ASSIGN;\
		this;\
	})

#endif