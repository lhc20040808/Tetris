#ifndef _BLOCK_H
#define _BLOCK_H

#include <stdio.h>

#define BLOCK_SIZE 7

#define SHAPE_SIZE 16

typedef struct{
	int state_count;//一共有多少种状态
	int (*shape)[SHAPE_SIZE]; //不同形状的图形长度等于[state_count][16]
}Block;

typedef struct{
	int x;//当前x坐标
	int y;//当前y坐标
	int cur_state;//当前状态
	Block* cur_block;
}Move_Block;

extern Block shapes[];

extern void print_all_type_of_block(int x, int y, Block *b);
#endif
