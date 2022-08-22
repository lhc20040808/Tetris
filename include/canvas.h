#ifndef TETRIS_CANVAS_H
#define TETRIS_CANVAS_H

#include <stdio.h>
#include "block.h"

/**
 *   (10,5)              (40,5)      (56,5)
 *      --------------------------------
 *      |                   |          |
 *      |                   |          |
 *      |                   |          |
 *      |                   |          |
 *      |                   |          |
 *      |           (40,12) |----------|(56,12)
 *      |                   |          |
 *      |                   |  (45,18) |
 *      |                   |   分数:   |
 *      |                   |  (45,22) |
 *      |                   |   等级：  |
 *      |                   |          |
 *      --------------------------------
 *   (10,30)             (40,30)    (56,30)
 *
 *   有24行，28列，由于不考虑保存颜色信息，统一用白色展示，所以用位图其实最节约空间。
 *   但C中没有bit类型，用位域操作有点麻烦，所以声明成char类型的二维数组
 */

#define CANVAS_START_X 10
#define CANVAS_START_Y 5
#define CANVAS_END_X 56
#define CANVAS_END_Y 30
#define CANVAS_GAME_DIVISION_X 40
#define CANVAS_FUNC_DIVISION_Y 12
#define CANVAS_INFO_X 45
#define CANVAS_SCORE_Y 18
#define CANVAS_LEVEL_Y 22

#define BLOCK_SHOW_X 24
#define BLOCK_SHOW_Y 6

#define NEXT_BLOCK_X 46
#define NEXT_BLOCK_Y 8//这里Hard Code不能保证所有图形居中。但不是练习重点，就不花太多时间调了。

#define BOUNDARY_START_X (CANVAS_START_X + 2)
#define BOUNDARY_START_Y (CANVAS_START_Y + 1)
#define BOUNDARY_END_X (CANVAS_GAME_DIVISION_X - 1)
#define BOUNDARY_END_Y (CANVAS_END_Y - 1)

extern void init_game_ui();

extern void block_rotate(Move_Block *moveBlock);

extern void block_move_down(Move_Block *moveBlock);

extern void block_move_left(Move_Block *moveBlock);

extern void block_move_right(Move_Block *moveBlock);

#endif //TETRIS_CANVAS_H
