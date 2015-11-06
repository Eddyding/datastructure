/*
 * list.h
 *
 *  Created on: Nov 5, 2015
 *      Author: lidq
 */

#ifndef LIST_H_
#define LIST_H_

#include "typedef.h"

typedef struct s_list
{
	//0表示原子，1表示子表
	int tag;
	//指数
	int exp;
	//共用体
	union
	{
		//系数
		int coe;
		//子表
		struct s_list* child;
	};

	//下一个结点
	struct s_list* next;

} s_list;

//追加节点
bool list_append(s_list *list, s_list* nlist);

bool list_init(s_list *list);

//插入原子节点或子表
bool list_insert_value(s_list *list, int tag, int exp, int val);

void list_display(s_list *list, char ch);

#endif /* LIST_H_ */
