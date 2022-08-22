#include "include/canvas.h"

/**
 * 位图
 */
static char bitmap[BOUNDARY_END_Y - BOUNDARY_START_Y + 1][BOUNDARY_END_X - BOUNDARY_START_X + 1] = {0};

void drawInfo(int score, int level) {
    printf("\033[%d;%dH分数：%d \033[0m", CANVAS_SCORE_Y, CANVAS_INFO_X, score);
    printf("\033[%d;%dH等级：%d \033[0m", CANVAS_LEVEL_Y, CANVAS_INFO_X, level);
    fflush(NULL);
}

/**
 * 绘制游戏界面UI
 */
void init_game_ui() {
    printf("\033[?25l");//隐藏光标
    printf("\033[2J");//清屏
    //绘制上下两条竖线
    for (int i = CANVAS_START_X; i <= CANVAS_END_X; i++) {
        printf("\033[%d;%dH\033[43m \033[0m", CANVAS_START_Y, i);
        printf("\033[%d;%dH\033[43m \033[0m", CANVAS_END_Y, i);
    }

    //绘制竖直的三条线
    for (int i = CANVAS_START_Y; i <= CANVAS_END_Y; i++) {
        printf("\033[%d;%dH\033[43m  \033[0m", i, CANVAS_START_X);
        printf("\033[%d;%dH\033[43m  \033[0m", i, CANVAS_END_X);
        printf("\033[%d;%dH\033[43m  \033[0m", i, CANVAS_GAME_DIVISION_X);
    }

    //绘制功能区分界面
    for (int i = CANVAS_GAME_DIVISION_X; i <= CANVAS_END_X; i++) {
        printf("\033[%d;%dH\033[43m \033[0m", CANVAS_FUNC_DIVISION_Y, i);
    }

    drawInfo(0, 1);
    fflush(NULL);
}

void store_block(Move_Block *moveBlock) {
    int line = moveBlock->y - BOUNDARY_START_Y;
    int column = moveBlock->x - BOUNDARY_START_X;
    int cur_state = moveBlock->cur_state;
    for (int i = 0; i < SHAPE_SIZE; i++) {

        if (i != 0 && i % 4 == 0) {
            line++;
            column = moveBlock->x - BOUNDARY_START_X;
        }

        if (moveBlock->cur_block->shape[cur_state][i] == 1) {
            bitmap[line][column] = 1;
            bitmap[line][column + 1] = 1;
        }

        column += 2;
    }
}

/**
 * 旋转方块
 * @param moveBlock
 */
void block_rotate(Move_Block *moveBlock) {
    //检查边界，如果旋转后会触碰边界，需要修改坐标
    int cur_state = moveBlock->cur_state;
    int state_count = moveBlock->cur_block->state_count;
    int next_state = (cur_state + 1) % (state_count);
    int width = moveBlock->cur_block->shape[next_state][SHAPE_SIZE];

    //删除原图像
    erase_block(moveBlock);

    while (moveBlock->x + width * 2 > BOUNDARY_END_X) {
        //如果旋转后会超过右边界，则修改x坐标
        moveBlock->x--;
    }

    //TODO 检查是否沉底

    //旋转
    moveBlock->cur_state = (next_state) % (moveBlock->cur_block->state_count);
    //绘制图像
    print_block(moveBlock);
}

void block_move_down(Move_Block *moveBlock) {
    int curState = moveBlock->cur_state;
    int height = moveBlock->cur_block->shape[curState][SHAPE_SIZE + 1];

    //检查是否撞底，撞底则保存图案
    //最下边一格的坐标是(moveBlock->y + height - 1)，然后移动一位需要加1，所以这边的判断是(moveBlock->y + height)
    if (moveBlock->y + height > BOUNDARY_END_Y) {
        erase_block(moveBlock);
        store_block(moveBlock);//保存图案
        return;
    }

    erase_block(moveBlock);
    moveBlock->y++;
    print_block(moveBlock);
}

void block_move_left(Move_Block *moveBlock) {
    if (moveBlock->x - 1 < BOUNDARY_START_X) {
        //如果碰到左边界，则不进行任何移动操作
        return;
    }
    erase_block(moveBlock);
    moveBlock->x--;
    print_block(moveBlock);
}

void block_move_right(Move_Block *moveBlock) {
    int curState = moveBlock->cur_state;
    int width = moveBlock->cur_block->shape[curState][SHAPE_SIZE];

    //最右边一格的坐标是(moveBlock->x + width * 2 - 1)，然后移动一位需要加1，所以这边的判断是(moveBlock->x + width * 2)
    if (moveBlock->x + width * 2 > BOUNDARY_END_X) {
        //如果碰到右边界，则不进行移动操作
        return;
    }
    erase_block(moveBlock);
    moveBlock->x++;
    print_block(moveBlock);
}



