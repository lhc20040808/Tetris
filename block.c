#include "include/block.h"

//block.c主要负责方块的定义，方块的绘制

int shape1[][SHAPE_SIZE + 2] = {{
                                        1, 1, 0, 0,
                                        1, 1, 0, 0,
                                        0, 0, 0, 0,
                                        0, 0, 0, 0,
                                        2, 2
                                }
};

int shape2[][SHAPE_SIZE + 2] = {
        {
                1, 0, 0, 0,
                1, 0, 0, 0,
                1, 0, 0, 0,
                1, 0, 0, 0,
                1, 4
        },
        {
                1, 1, 1, 1,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                4, 1
        }
};

int shape3[][SHAPE_SIZE + 2] = {
        {
                0, 1, 1, 0,
                1, 1, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                3, 2
        },
        {
                1, 0, 0, 0,
                1, 1, 0, 0,
                0, 1, 0, 0,
                0, 0, 0, 0,
                2, 3
        }
};

int shape4[][SHAPE_SIZE + 2] = {
        {
                1, 1, 0, 0,
                0, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                3, 2
        },
        {
                0, 1, 0, 0,
                1, 1, 0, 0,
                1, 0, 0, 0,
                0, 0, 0, 0,
                2, 3
        }
};

int shape5[][SHAPE_SIZE + 2] = {
        {
                1, 0, 0, 0,
                1, 0, 0, 0,
                1, 1, 0, 0,
                0, 0, 0, 0,
                2, 3
        },
        {
                1, 1, 1, 0,
                1, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                3, 2
        },
        {
                1, 1, 0, 0,
                0, 1, 0, 0,
                0, 1, 0, 0,
                0, 0, 0, 0,
                2, 3
        },
        {
                0, 0, 1, 0,
                1, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                3, 2
        }
};

int shape6[][SHAPE_SIZE + 2] = {
        {
                0, 1, 0, 0,
                0, 1, 0, 0,
                1, 1, 0, 0,
                0, 0, 0, 0,
                2, 3
        },
        {
                1, 0, 0, 0,
                1, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                3, 2
        },
        {
                1, 1, 0, 0,
                1, 0, 0, 0,
                1, 0, 0, 0,
                0, 0, 0, 0,
                2, 3
        },
        {
                1, 1, 1, 0,
                0, 0, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                3, 2
        }
};

int shape7[][SHAPE_SIZE + 2] = {
        {
                0, 1, 0, 0,
                1, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                3, 2
        },
        {
                1, 0, 0, 0,
                1, 1, 0, 0,
                1, 0, 0, 0,
                0, 0, 0, 0,
                2, 3
        },
        {
                1, 1, 1, 0,
                0, 1, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                3, 2
        },
        {
                0, 1, 0, 0,
                1, 1, 0, 0,
                0, 1, 0, 0,
                0, 0, 0, 0,
                2, 3
        }
};

Block shapes[BLOCK_SIZE] =
        {
                //方块
                {
                        1,//方块只有一个状态
                        40,
                        shape1
                },
                //竖
                {
                        2,//竖有两个状态
                        41,
                        shape2
                },
                //反Z
                {
                        2,
                        42,
                        shape3
                },
                //正Z
                {
                        2,
                        43,
                        shape4
                },
                //正L
                {
                        4,
                        44,
                        shape5
                },
                //反L
                {
                        4,
                        45,
                        shape6
                },
                //T
                {
                        4,
                        46,
                        shape7
                }
        };

/**
 *
 * @param x 打印的横坐标起点
 * @param y 打印的纵坐标起点
 * @param b 待打印的方块
 */
void print_all_type_of_block(int x, int y, Block *b) {
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
                printf("\033[%dm[]", b->color);
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
            printf("\033[%dm[]", m_block->cur_block->color);
            printf("\033[0m");
        }

        move_x += 2;
    }
    fflush(NULL);
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
            printf("  ");//绘制图形的时候用的[]，占两个字符，所以擦除需要两个空格
            printf("\033[0m");
        }
        move_x += 2;
    }

    fflush(NULL);
}

void block_down_to_bottom() {

}

