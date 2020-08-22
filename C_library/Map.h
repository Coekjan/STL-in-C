/*
	Map.h使用方法
		实例化	map(_Key_TYPE, _Val_TYPE) _Map = new(map(_Key_TYPE, _Val_TYPE, _CMP_FUNC));
		调用方法
			_Map.type()						=>	返回当前映射集中包含的数据类型(字符串形式)
			_Map.size()						=>	返回当前映射集中映射的对数
			_Map.isEmpty()					=>	判断当前映射集是否为空
			_Map.contain(_Key)				=>	判断当前映射集是否包含键_Key
			_Map.valOf(_Key)				=>	返回键_Key对应的值_Val的地址
			_Map.insert(_Pair)				=>	向映射集中添加映射_Pair
			_Map.erase(_Pair)				=>	从映射集中移除映射_Pair
			_Map.traversal(_Func)			=>	使用_Func函数遍历映射集
			_Map.clear()					=>	清空映射集，不释放内存
			_Map.delete()					=>	删除映射集，释放内存
		注意事项
			_Pair是Ultility.h中定义的结构，使用时应如下面所示
				(pair(_Key_TYPE, _Val_TYPE)){_Key, _Val}
				即代表一个_Key到_Val的映射对
			实例化中，第3个参数是一个函数
				函数类型为int (*)(_Pair, _Pair)
				该函数用于比较两映射之间的大小区别
			使用new实例化map后，请在使用完毕后调用delete，否则有可能导致内存泄漏
 */
#ifndef TEMPLATE_MAP_H
	#define TEMPLATE_MAP_H

	#include "core/template.h"
	#include "Macro.h"
	#include "Ultility.h"
	#include "RBTree.h"

	#define map_(K, V) K##_##V##_map
	#define map(K, V) map_(K, V)

	#define map_config(K, V)\
		pair_config(K, V);\
		typedef struct map(K, V) map(K, V);\
		struct map(K, V) {\
			char*				(*type)			();\
			unsigned int		(*size)			();\
			bool				(*isEmpty)		();\
			bool				(*contain)		(K);\
			V*					(*valOf)		(K);\
			map(K, V)			(*insert)		(pair(K, V));\
			map(K, V)			(*erase)		(pair(K, V));\
			map(K, V)			(*traversal)	(void (*)(pair(K, V)));\
			map(K, V)			(*clear)		();\
			void				(*delete)		();\
		};

	#define __MAP_FUNCTION_BODY(K, V)\
		char *type() {\
			return tostring(map(K, V));\
		}\
		bool contain(K key) {\
			V _temp;\
			memset(&_temp, 0, sizeof(V));\
			return _core_tree.contain((pair(K, V)){key, _temp});\
		}\
		V* valOf(K key) {\
			V _temp;\
			memset(&_temp, 0, sizeof(V));\
			rbnode(pair(K, V)) *_node = _core_tree.search((pair(K, V)){key, _temp});\
			return &_node->data.second;\
		}\
		map(K, V) insert(pair(K, V) p) {\
			if(contain(p.first)) return this;\
			_core_tree.insert(p);\
			return this;\
		}\
		map(K, V) erase(pair(K, V) p) {\
			if(!contain(p.first)) return this;\
			_core_tree.erase(p);\
			return this;\
		}\
		map(K, V) traversal(void (*func)(pair(K, V))) {\
			_core_tree.traversal(rbt_lnr, func);\
			return this;\
		}\
		map(K, V) clear() {\
			_core_tree.clear();\
			return this;\
		}

	#define __MAP_FUNCTION_ASSIGN\
		this.type = type;\
		this.size = _core_tree.size;\
		this.isEmpty = _core_tree.isEmpty;\
		this.contain = contain;\
		this.valOf = valOf;\
		this.insert = insert;\
		this.erase = erase;\
		this.traversal = traversal;\
		this.clear = clear;\
		this.delete = _core_tree.delete;

	#define new_map(K, V, CMP_FUNC) ({\
		rbtree_config(pair(K, V));\
		rbtree(pair(K, V)) _core_tree = new_rbtree(pair(K, V), CMP_FUNC);\
		map(K, V) this;\
		__MAP_FUNCTION_BODY(K, V);\
		__MAP_FUNCTION_ASSIGN;\
		this;\
	})


#endif