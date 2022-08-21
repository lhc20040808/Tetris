#include "include/block.h"

//block.c主要负责方块的定义，方块的绘制

int shape1[][SHAPE_SIZE] = {{
                                    1, 1, 0, 0,
                                    1, 1, 0, 0,
                                    0, 0, 0, 0,
                                    0, 0, 0, 0
                            }
};

int shape2[][SHAPE_SIZE] = {
        {
                1, 0, 0, 0,
                1, 0, 0, 0,
                1, 0, 0, 0,
                1, 0, 0, 0
        },
        {
                1, 1, 1, 1,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        }
};

int shape3[][SHAPE_SIZE] = {
        {
                0, 1, 1, 0,
                1, 1, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        },
        {
                1, 0, 0, 0,
                1, 1, 0, 0,
                0, 1, 0, 0,
                0, 0, 0, 0
        }
};

int shape4[][SHAPE_SIZE] = {
        {
                1, 1, 0, 0,
                0, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        },
        {
                0, 1, 0, 0,
                1, 1, 0, 0,
                1, 0, 0, 0,
                0, 0, 0, 0
        }
};

int shape5[][SHAPE_SIZE] = {
        {
                1, 0, 0, 0,
                1, 0, 0, 0,
                1, 1, 0, 0,
                0, 0, 0, 0
        },
        {
                1, 1, 1, 0,
                1, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        },
        {
                1, 1, 0, 0,
                0, 1, 0, 0,
                0, 1, 0, 0,
                0, 0, 0, 0
        },
        {
                0, 0, 1, 0,
                1, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        }
};

int shape6[][SHAPE_SIZE] = {
        {
                0, 1, 0, 0,
                0, 1, 0, 0,
                1, 1, 0, 0,
                0, 0, 0, 0
        },
        {
                1, 0, 0, 0,
                1, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        },
        {
                1, 1, 0, 0,
                1, 0, 0, 0,
                1, 0, 0, 0,
                0, 0, 0, 0
        },
        {
                1, 1, 1, 0,
                0, 0, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        }
};

int shape7[][SHAPE_SIZE] = {
        {
                0, 1, 0, 0,
                1, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        },
        {
                0, 1, 0, 0,
                0, 1, 1, 0,
                0, 1, 0, 0,
                0, 0, 0, 0
        },
        {
                1, 1, 1, 0,
                0, 1, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
        },
        {
                0, 1, 0, 0,
                1, 1, 0, 0,
                0, 1, 0, 0,
                0, 0, 0, 0
        }
};

Block shapes[BLOCK_SIZE] =
        {
                //方块
                {
                        1,//方块只有一个状态
                        shape1
                },
                //竖
                {
                        2,//竖有两个状态
                        shape2
                },
                //反Z
                {
                        2,
                        shape3
                },
                //正Z
                {
                        2,
                        shape4
                },
                //正L
                {
                        4,
                        shape5
                },
                //反L
                {
                        4,
                        shape6
                },
                //T
                {
                        4,
                        shape7
                }
        };

//以x,y坐标为起点，打印块的所有图形
void print_block_of_all_type(int x, int y, Block *b) {
    int move_x = x;
    int move_y = y;
    for (int i = 0; i < b->state_count; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {

            if (j != 0 && j % 4 == 0) {
                move_x = x;
                move_y++;
            }

            if (b->shape[i][j] == 1) {
                printf("\033[%d;%dH", move_y, move_x);
                printf("\033[%dm[]", 43);
                printf("\033[0m");
            }

            move_x += 2;
        }
        //同一个块的不同类型横向打印
        x += 8;
        move_y = y;
        move_x = x;
    }
}

void print_block(Move_Block *m_block) {
    int move_x = m_block->x;
    int move_y = m_block->y;
    int curState = m_block->cur_state;

    for (int i = 0; i < SHAPE_SIZE; i++) {

        if (i != 0 && i % 4 == 0) {
            move_x = m_block->x;
            move_y++;
        }

        if (m_block->cur_block->shape[curState][i] == 1) {
            printf("\033[%d;%dH", move_y, move_x);
            printf("\033[%dm[]", 43);
            printf("\033[0m");
        }

        move_x += 2;
    }
}

void erase_block(Move_Block *m_block) {
    int move_x = m_block->x;
    int move_y = m_block->y;
    int curState = m_block->cur_state;
    for (int i = 0; i < SHAPE_SIZE; i++) {
        if (i != 0 && i % 4 == 0) {
            move_x = m_block->x;
            move_y++;
        }

        if (m_block->cur_block->shape[curState][i] == 1) {
            printf("\033[%d;%dH", move_y, move_x);
            printf(" ");
            printf("\033[0m");
        }
        move_x += 2;
    }
}

/**
 * 旋转方块
 * @param moveBlock
 * @param right 0朝左旋转，1朝右旋转
 */
void block_rotate(Move_Block *moveBlock, int right) {
    //删除原图像
    erase_block(moveBlock);
    //旋转
    if (right) {
        moveBlock->cur_state = (moveBlock->cur_state + 1) % (moveBlock->cur_block->state_count);
    } else {
        moveBlock->cur_state--;
        if (moveBlock->cur_state < 0) {
            moveBlock->cur_state = moveBlock->cur_block->state_count - 1;
        }
    }
    //绘制图像
    print_block(moveBlock);
}

void block_move_down(Move_Block *moveBlock) {
    erase_block(moveBlock);
    moveBlock->y++;
    print_block(moveBlock);
}

void block_move_left(Move_Block *moveBlock) {
    erase_block(moveBlock);
    moveBlock->x--;
    print_block(moveBlock);
}

void block_move_right(Move_Block *moveBlock) {
    erase_block(moveBlock);
    moveBlock->x++;
    print_block(moveBlock);
}

void block_down_to_bottom() {

}

