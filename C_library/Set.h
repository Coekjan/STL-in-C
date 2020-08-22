/*
	Set.h使用方法
		实例化	set(_Type)	_Set = new(set(_Type, _CMP_FUNC));
		调用方法
			_Set.type()						=>	返回当前集合中包含的数据类型(字符串形式)
			_Set.size()						=>	返回当前集合中元素的数目
			_Set.isEmpty()					=>	判断当前集合是否为空
			_Set.contain(_Data)				=>	判断当前集合是否包含元素_Data
			_Set.insert(_Data)				=>	向集合中添加元素_Data
			_Set.erase(_Data)				=>	从集合中移除元素_Data
			_Set.traversal(_Func)			=>	使用_Func函数遍历集合
			_Set.clear()					=>	清空集合，不释放内存
			_Set.delete()					=>	删除集合，释放内存
		注意事项
			实例化中，第2个参数是一个函数
				函数类型为int (*)(_Type, _Type)
				该函数用于比较两元素之间的大小区别
			使用new实例化set后，请在使用完毕后调用delete，否则有可能导致内存泄漏
 */
#ifndef TEMPLATE_SET_H
	#define TEMPLATE_SET_H

	#include "core/template.h"
	#include "Macro.h"
	#include "RBTree.h"

	#define set_(T) T##_set
	#define set(T) set_(T)

	#define set_config(T)\
		typedef struct set(T) set(T);\
		struct set(T) {\
			char*				(*type)			();\
			unsigned int		(*size)			();\
			bool				(*isEmpty)		();\
			bool				(*contain)		(T);\
			set(T)				(*insert)		(T);\
			set(T)				(*erase)		(T);\
			set(T)				(*traversal)	(void (*)(T));\
			set(T)				(*clear)		();\
			void				(*delete)		();\
		};

	#define __SET_FUNCTION_BODY(T)\
		char *type() {\
			return tostring(set(T));\
		}\
		set(T) insert(T data) {\
			if(_core_tree.contain(data)) return this;\
			_core_tree.insert(data);\
			return this;\
		}\
		set(T) erase(T data) {\
			_core_tree.erase(data);\
			return this;\
		}\
		set(T) traversal(void (*func)(T)) {\
			_core_tree.traversal(rbt_lnr, func);\
			return this;\
		}\
		set(T) clear() {\
			_core_tree.clear();\
			return this;\
		}\

	#define __SET_FUNCTION_ASSIGN\
		this.type = type;\
		this.size = _core_tree.size;\
		this.isEmpty = _core_tree.isEmpty;\
		this.contain = _core_tree.contain;\
		this.insert = insert;\
		this.erase = erase;\
		this.traversal = traversal;\
		this.clear = clear;\
		this.delete = _core_tree.delete;

	#define new_set(T, CMP_FUNC) ({\
		rbtree_config(T);\
		rbtree(T) _core_tree = new_rbtree(T, CMP_FUNC);\
		set(T) this;\
		__SET_FUNCTION_BODY(T);\
		__SET_FUNCTION_ASSIGN;\
		this;\
	})

#endif