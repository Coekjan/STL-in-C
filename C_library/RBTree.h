/*
	RBTree.h使用方法
		实例化	rbtree(_Type) _RBTree = new(rbtree(_Type, _CMP_FUNC));
		调用方法
			_RBTree.type()					=>	返回当前红黑树中包含的数据类型(字符串形式)
			_RBTree.size()					=>	返回当前红黑树中结点的数目(不含重复元素)
			_RBTree.count(_Data)			=>	返回当前红黑树中元素_Data的数目
			_RBTree.isEmpty()				=>	判断当前红黑树是否为空
			_RBTree.contain(_Data)			=>	判断当前红黑树是否包含元素_Data
			_RBTree.search(_Data)			=>	在红黑树中搜索元素_Data，返回该元素所在的结点
			_RBTree.insert(_Data)			=>	向红黑树中添加元素_Data：若_Data已存在，则在_Data所在结点的计数加一；否则新增一个结点储存_Data1
			_RBTree.erase(_Data)			=>	从红黑树中抹除元素_Data：若_Data不存在，则不做任何操作，若_Data存在但计数大于等于2，则在_Data所在结点的计数减一；否则删除结点
			_RBTree.traversal(_Mode, _Func)	=>	以模式_Mode，函数_Func遍历红黑树：其中_Mode可选为rbt_nlr(先序遍历)，rbt_lnr(中序遍历)，rbt_lrn(后序遍历)
			_RBTree.clear()					=>	清除红黑树的结点及其包含的元素，不释放内存，后续可重新添加元素
			_RBTree.delete()				=>	删除红黑树，释放内存，后续不可使用
		注意事项
			实例化中，第2个参数是一个函数
				函数类型为int (*)(_Type, _Type)
				该函数用于比较两元素之间的大小区别
			使用new实例化rbtree后，请在使用完毕后调用delete，否则有可能导致内存泄漏
 */
#ifndef TEMPLATE_RBTREE_H
	#define TEMPLATE_RBTREE_H

	#include "core/template.h"
	#include "Macro.h"
	#define rbtree_(T) T##_rbtree
	#define rbtree(T) rbtree_(T)
	#define rbnode_(T) T##_rbtree_node
	#define rbnode(T) rbnode_(T)

	typedef enum rbt_node_color rbt_node_color;
	enum rbt_node_color {red, black};

	typedef enum rbt_trl_mode rbt_trl_mode;
	enum rbt_trl_mode {rbt_nlr, rbt_lnr, rbt_lrn};

	#define rbtree_config(T)\
		typedef struct rbnode(T) rbnode(T);\
		struct rbnode(T) {\
			rbnode(T)			*parent;\
			rbnode(T)			*lChild;\
			rbnode(T)			*rChild;\
			rbt_node_color		color;\
			unsigned int		time;\
			T					data;\
		};\
		typedef struct rbtree(T) rbtree(T);\
		struct rbtree(T) {\
			char*				(*type)			();\
			unsigned int		(*size)			();\
			unsigned int		(*count)		(T);\
			bool				(*isEmpty)		();\
			bool				(*contain)		(T);\
			rbnode(T)*			(*search)		(T);\
			rbtree(T)			(*insert)		(T);\
			rbtree(T)			(*erase)		(T);\
			rbtree(T)			(*traversal)	(rbt_trl_mode, void (*)(T));\
			rbtree(T)			(*clear)		();\
			void				(*delete)		();\
		};

	#define __RBTREE_FUNCTION_BODY(T, CMP_FUNC)\
		rbnode(T) *_Minimum(rbnode(T) *_node) {\
			while(_node->lChild != nil) _node = _node->lChild;\
			return _node;\
		}\
		void _LRotate(rbnode(T) *_node) {\
			rbnode(T) *_new_node = _node->rChild;\
			_node->rChild = _new_node->lChild;\
			if(_new_node->lChild != nil) _new_node->lChild->parent = _node;\
			_new_node->parent = _node->parent;\
			if(_node->parent == nil) root = _new_node;\
			else if(_node == _node->parent->lChild) _node->parent->lChild = _new_node;\
			else _node->parent->rChild = _new_node;\
			_new_node->lChild = _node;\
			_node->parent = _new_node;\
		}\
		void _RRotate(rbnode(T) *_node) {\
			rbnode(T) *_new_node = _node->lChild;\
			_node->lChild = _new_node->rChild;\
			if(_new_node->rChild != nil) _new_node->rChild->parent = _node;\
			_new_node->parent = _node->parent;\
			if(_node->parent == nil) root = _new_node;\
			else if(_node == _node->parent->rChild) _node->parent->rChild = _new_node;\
			else _node->parent->lChild = _new_node;\
			_new_node->rChild = _node;\
			_node->parent = _new_node;\
		}\
		void _Transplant(rbnode(T) *_target, rbnode(T) *_origin) {\
			if(_target->parent == nil) root = _origin;\
			else if(_target == _target->parent->lChild) _target->parent->lChild = _origin;\
			else _target->parent->rChild = _origin;\
			_origin->parent = _target->parent;\
		}\
		void _InsertFixUp(rbnode(T) *_fix_node) {\
			rbnode(T) *_temp_node;\
			while(_fix_node->parent->color == red) {\
				if(_fix_node->parent == _fix_node->parent->parent->lChild) {\
					_temp_node = _fix_node->parent->parent->rChild;\
					if(_temp_node->color == red) {\
						_fix_node->parent->color = black;\
						_temp_node->color = black;\
						_fix_node->parent->parent->color = red;\
						_fix_node = _fix_node->parent->parent;\
					} else {\
						if(_fix_node == _fix_node->parent->rChild) {\
							_fix_node = _fix_node->parent;\
							_LRotate(_fix_node);\
						}\
						_fix_node->parent->color = black;\
						_fix_node->parent->parent->color = red;\
						_RRotate(_fix_node->parent->parent);\
					}\
				} else {\
					_temp_node = _fix_node->parent->parent->lChild;\
					if(_temp_node->color == red) {\
						_fix_node->parent->color = black;\
						_temp_node->color = black;\
						_fix_node->parent->parent->color = red;\
						_fix_node = _fix_node->parent->parent;\
					} else {\
						if(_fix_node == _fix_node->parent->lChild) {\
							_fix_node = _fix_node->parent;\
							_RRotate(_fix_node);\
						}\
						_fix_node->parent->color = black;\
						_fix_node->parent->parent->color = red;\
						_LRotate(_fix_node->parent->parent);\
					}\
				}\
			}\
			root->color = black;\
		}\
		void _EraseFixUp(rbnode(T) *_fix_node) {\
			rbnode(T) *_temp_node;\
			while(_fix_node != root && _fix_node->color == black) {\
				if(_fix_node == _fix_node->parent->lChild) {\
					_temp_node = _fix_node->parent->rChild;\
					if(_temp_node->color == red) {\
						_temp_node->color = black;\
						_fix_node->parent->color = red;\
						_LRotate(_fix_node->parent);\
						_temp_node = _fix_node->parent->rChild;\
					}\
					if(_temp_node->lChild->color == black && _temp_node->rChild->color == black) {\
						_temp_node->color = red;\
						_fix_node = _fix_node->parent;\
					} else {\
						if(_temp_node->rChild->color == black) {\
							_temp_node->lChild->color = black;\
							_temp_node->color = red;\
							_RRotate(_temp_node);\
							_temp_node = _fix_node->parent->rChild;\
						}\
						_temp_node->color = _fix_node->parent->color;\
						_fix_node->parent->color = black;\
						_temp_node->rChild->color = black;\
						_LRotate(_fix_node->parent);\
						_fix_node = root;\
					}\
				} else {\
					_temp_node = _fix_node->parent->lChild;\
					if(_temp_node->color == red) {\
						_temp_node->color = black;\
						_fix_node->parent->color = red;\
						_RRotate(_fix_node->parent);\
						_temp_node = _fix_node->parent->lChild;\
					}\
					if(_temp_node->rChild->color == black && _temp_node->lChild->color == black) {\
						_temp_node->color = red;\
						_fix_node = _fix_node->parent;\
					} else {\
						if(_temp_node->lChild->color == black) {\
							_temp_node->rChild->color = black;\
							_temp_node->color = red;\
							_LRotate(_temp_node);\
							_temp_node = _fix_node->parent->lChild;\
						}\
						_temp_node->color = _fix_node->parent->color;\
						_fix_node->parent->color = black;\
						_temp_node->lChild->color = black;\
						_RRotate(_fix_node->parent);\
						_fix_node = root;\
					}\
				}\
			}\
			_fix_node->color = black;\
		}\
		void _Visit_NLR(rbnode(T) *_node, void (*func)(T)) {\
			if(_node == nil) return;\
			(*func)(_node->data);\
			_Visit_NLR(_node->lChild, func);\
			_Visit_NLR(_node->rChild, func);\
		}\
		void _Visit_LNR(rbnode(T) *_node, void (*func)(T)) {\
			if(_node == nil) return;\
			_Visit_LNR(_node->lChild, func);\
			(*func)(_node->data);\
			_Visit_LNR(_node->rChild, func);\
		}\
		void _Visit_LRN(rbnode(T) *_node, void (*func)(T)) {\
			if(_node == nil) return;\
			_Visit_LRN(_node->lChild, func);\
			_Visit_LRN(_node->rChild, func);\
			(*func)(_node->data);\
		}\
		void _Free_RBT(rbnode(T) *_node) {\
			if(_node == nil) return;\
			_Free_RBT(_node->lChild);\
			_Free_RBT(_node->rChild);\
			free(_node);\
		}\
		char *type() {\
			return tostring(rbtree_(T));\
		}\
		rbnode(T) *search(T data) {\
			register int _re = 0;\
			register rbnode(T) *_node = root;\
			while(_node != nil) {\
				if((_re = CMP_FUNC(data, _node->data)) == 0) return _node;\
				else if(_re > 0) _node = _node->rChild;\
				else _node = _node->lChild;\
			}\
			return nil;\
		}\
		unsigned int size() {\
			return node_num;\
		}\
		unsigned int count(T data) {\
			rbnode(T) *node = this.search(data);\
			return node->time;\
		}\
		bool isEmpty() {\
			return !node_num;\
		}\
		bool contain(T data) {\
			if(search(data) == nil) return false;\
			return true;\
		}\
		rbtree(T) insert(T data) {\
			rbnode(T) *_new_node = search(data);\
			if(_new_node != nil) {\
				_new_node->time++;\
				return this;\
			}\
			node_num++;\
			malloc_space(_new_node, rbnode(T), 1);\
			_new_node->data = data;\
			_new_node->color = red;\
			_new_node->time = 1;\
			register int _cmp = 0;\
			rbnode(T) *_target = nil, *_temp = root;\
			while(_temp != nil) {\
				_target = _temp;\
				if((_cmp = CMP_FUNC(data, _temp->data)) < 0) _temp = _temp->lChild;\
				else _temp = _temp->rChild;\
			}\
			_new_node->parent = _target;\
			if(_target == nil) root = _new_node;\
			else if(_cmp < 0) _target->lChild = _new_node;\
			else _target->rChild = _new_node;\
			_new_node->lChild = _new_node->rChild = nil;\
			_InsertFixUp(_new_node);\
			return this;\
		}\
		rbtree(T) erase(T data) {\
			rbnode(T) *_delete_node = search(data);\
			if(_delete_node == nil) return this;\
			if(_delete_node->time > 1) {\
				_delete_node->time--;\
				return this;\
			}\
			node_num--;\
			rbnode(T) *_target = _delete_node, *_temp;\
			rbt_node_color temp_color = _target->color;\
			if(_delete_node->lChild == nil) {\
				_temp = _delete_node->rChild;\
				_Transplant(_delete_node, _delete_node->rChild);\
			} else if(_delete_node->rChild == nil) {\
				_temp = _delete_node->lChild;\
				_Transplant(_delete_node, _delete_node->lChild);\
			} else {\
				_target = _Minimum(_delete_node->rChild);\
				temp_color = _target->color;\
				_temp = _target->rChild;\
				if(_target->parent == _delete_node) _temp->parent = _target;\
				else {\
					_Transplant(_target, _target->rChild);\
					_target->rChild = _delete_node->rChild;\
					_target->rChild->parent = _target;\
				}\
				_Transplant(_delete_node, _target);\
				_target->lChild = _delete_node->lChild;\
				_target->lChild->parent = _target;\
				_target->color = _delete_node->color;\
			}\
			free(_delete_node);\
			if(temp_color == black) _EraseFixUp(_temp);\
			return this;\
		}\
		rbtree(T) traversal(rbt_trl_mode mode, void (*func)(T)) {\
			switch(mode) {\
				case rbt_nlr:\
					_Visit_NLR(root, func);\
					return this;\
				case rbt_lnr:\
					_Visit_LNR(root, func);\
					return this;\
				case rbt_lrn:\
					_Visit_LRN(root, func);\
					return this;\
				default: return this;\
			}\
		}\
		rbtree(T) clear() {\
			_Free_RBT(root);\
			root = nil;\
			node_num = 0;\
			return this;\
		}\
		void delete() {\
			_Free_RBT(root);\
			node_num = 0;\
			free(nil);\
		}

	#define __RBTREE_FUNCTION_ASSIGN\
		this.type = type;\
		this.size = size;\
		this.count = count;\
		this.isEmpty = isEmpty;\
		this.contain = contain;\
		this.search = search;\
		this.insert = insert;\
		this.erase = erase;\
		this.traversal = traversal;\
		this.clear = clear;\
		this.delete = delete;

	#define new_rbtree(T, CMP_FUNC) ({\
		unsigned int node_num = 0;\
		rbtree(T) this;\
		rbnode(T) *root = NULL, *nil = NULL;\
		malloc_space(nil, rbnode(T), 1);\
		memset(&nil->data, 0, sizeof(T));\
		nil->parent = nil->lChild = nil->rChild = nil;\
		nil->color = black;\
		nil->time = 0;\
		root = nil;\
		__RBTREE_FUNCTION_BODY(T, CMP_FUNC);\
		__RBTREE_FUNCTION_ASSIGN;\
		this;\
	})

#endif