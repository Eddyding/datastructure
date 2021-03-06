/*
 * tree.c
 *
 *  Created on: Nov 10, 2015
 *      Author: lidq
 */

#include <stdlib.h>
#include "tree.h"

//初始化树
bool tree_init(s_tree *tree, void (*visit_node)(), void (*free_node)())
{
	if (tree == null)
	{
		return false;
	}

	tree->root = null;
	tree->visit_node = visit_node;
	tree->free_node = free_node;

	return true;
}

//销毁树
bool tree_destroy(s_tree *tree)
{
	if (tree == null)
	{
		return false;
	}

	//清空树
	tree_clear(tree, tree->root);

	//根节点置空
	tree->root = null;

	return true;
}

//清空树
void tree_clear(s_tree *tree, s_node *node)
{
	if (node == null)
	{
		return;
	}

	//递归清空左子树
	tree_clear(tree, node->left_child);
	node->left_child = null;
	//递归清空右子树
	tree_clear(tree, node->right_child);
	node->right_child = null;

	//如果数据项不为空
	if (node->data != null)
	{
		//释放数据项内存
		tree->free_node(node->data);
	}

	if (node == tree->root)
	{
		tree->root = null;
	}

	//释放当前节点内存
	free(node);
}

//初始化节点
bool tree_init_node(s_node *node, void *data)
{
	if (node == null)
	{
		return true;
	}

	node->parent = null;
	node->left_child = null;
	node->right_child = null;
	node->data = data;

	return true;
}

//前序遍历
void tree_preamble_visit(s_tree *tree, s_node *node)
{
	if (tree == null)
	{
		return;
	}
	if (tree->root == null)
	{
		return;
	}
	if (node == null)
	{
		return;
	}

	//中
	tree->visit_node(node->data);
	//左
	tree_preamble_visit(tree, node->left_child);
	//右
	tree_preamble_visit(tree, node->right_child);
}

//由一个有序链表构建赫夫曼树
bool tree_create(s_tree *tree, s_list *list)
{
	if (tree == null)
	{
		return false;
	}
	if (list == null)
	{
		return false;
	}
	if (list->next == null)
	{
		return false;
	}

	//当有序链表中前两个节点不为空时
	while (list->next != null && list->next->next != null)
	{
		//取出有序链表中第一个节点
		s_list *p0 = list->next;
		//取出有序链表中第二个节点
		s_list *p1 = list->next->next;

		//取得树节点，权重小的为左节点，权重大的为右节点，
		s_node *n_left = (s_node *) p0->data;
		s_node *n_right = (s_node *) p1->data;

		//权重相同时无子树的为左节点
		if (p0->weights == p1->weights)
		{
			s_node *n_temp = n_left;
			n_left = n_right;
			n_right = n_temp;
		}

		//申请新节点内存
		s_node *n_node = (s_node *) malloc(sizeof(s_node));

		//权重相加
		int weights = p0->weights + p1->weights;
		//删除有序链表中的前两个节点
		list_delete(list, p0->data);
		list_delete(list, p1->data);

		//构建新节点
		n_node->parent = null;
		n_node->data = null;
		n_node->left_child = n_left;
		n_node->right_child = n_right;
		n_left->parent = n_node;
		n_right->parent = n_node;

		//将新节点插入有序链表
		list_insert(list, weights, n_node);
	}

	//经由上面处理后，有序链表中只留下一个节点
	s_list *p = list->next;
	//取得二叉树的根节点
	s_node *n_root = (s_node *) p->data;
	//设定二叉树的根节点
	tree->root = n_root;

	return true;
}
