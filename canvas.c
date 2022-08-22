#include "include/canvas.h"

extern void next_block();

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

/**
 * 将当前块保存到位图中
 * @param moveBlock
 */
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
 * 更新位图
 */
void update_bitmap() {
    for (int i = 0; i < BOUNDARY_END_Y - BOUNDARY_START_Y + 1; i++) {
        for (int j = 0; j < BOUNDARY_END_X - BOUNDARY_START_X + 1; j = j + 2) {
            if (bitmap[i][j] == 1) {
                printf("\033[%d;%dH", i + BOUNDARY_START_Y, j + BOUNDARY_START_X);
                printf("\033[%dm[]", 47);//保存下来的图形画成白色
                printf("\033[0m");
            }
        }
    }
    fflush(NULL);
}

/**
 * 擦除待展示区的方块，给下次绘制提供空间
 * @param m_block
 */
void erase_next_area() {
    int move_x = NEXT_BLOCK_X;
    int move_y = NEXT_BLOCK_Y;
    for (int i = 0; i < SHAPE_SIZE; i++) {
        if (i != 0 && i % 4 == 0) {
            move_x = NEXT_BLOCK_X;
            move_y++;
        }
        printf("\033[%d;%dH", move_y, move_x);
        printf("  ");//绘制图形的时候用的[]，占两个字符，所以擦除需要两个空格
        printf("\033[0m");
        move_x += 2;
    }
    fflush(NULL);
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

    //如果旋转后，方块的宽度超过右边界则不旋转
    if (moveBlock->x + moveBlock->cur_block->shape[next_state][SHAPE_SIZE] * 2 - 1 > BOUNDARY_END_X) {
        return;
    }

    //如果旋转后没有足够空间，则不旋转
    if (!check_area(moveBlock->cur_block, next_state, moveBlock->x, moveBlock->y)) {
        return;
    }

    //删除原图像
    erase_block(moveBlock);
    //旋转
    moveBlock->cur_state = (next_state) % (moveBlock->cur_block->state_count);
    //绘制图像
    print_block(moveBlock);
}

int check_area(Block *block, int state, int x, int y) {
    int line = y - BOUNDARY_START_Y;
    int column = x - BOUNDARY_START_X;
    for (int i = 0; i < SHAPE_SIZE; i++) {

        if (i != 0 && i % 4 == 0) {
            line++;
            column = x - BOUNDARY_START_X;
        }

        if (block->shape[state][i] == 1 &&
            bitmap[line][column] == 1) {
            return 0;
        }

        column += 2;
    }
    return 1;
}

/**
 * 判断当前方块下方是否还有足够的下落空间
 * @param moveBlock
 * @return 0 没有足够下落空间 1 有足够下落空间
 */
int has_enough_area(Move_Block *moveBlock, int next_x, int next_y) {
    return check_area(moveBlock->cur_block, moveBlock->cur_state, next_x, next_y);
}

/**
 * 向下移动方块
 * @param moveBlock
 * @return 0 方块没有移动到底  1 方块移动到底
 */
int block_move_down(Move_Block *moveBlock) {
    int curState = moveBlock->cur_state;
    int height = moveBlock->cur_block->shape[curState][SHAPE_SIZE + 1];

    //检查是否撞底，撞底则保存图案
    //最下边一格的坐标是(moveBlock->y + height - 1)，然后移动一位需要加1，所以这边的判断是(moveBlock->y + height)
    if (moveBlock->y + height > BOUNDARY_END_Y || !has_enough_area(moveBlock, moveBlock->x, moveBlock->y + 1)) {
        store_block(moveBlock);//保存图案
        update_bitmap();//这里不清除原图像也无所谓，刷新Bitmap的时候会覆盖掉
        next_block();
        return 1;
    }

    erase_block(moveBlock);
    moveBlock->y++;
    print_block(moveBlock);
    return 0;
}

void block_move_left(Move_Block *moveBlock) {
    if (moveBlock->x - 2 < BOUNDARY_START_X || !has_enough_area(moveBlock, moveBlock->x - 2, moveBlock->y)) {
        //如果碰到左边界，则不进行任何移动操作
        return;
    }
    erase_block(moveBlock);
    moveBlock->x -= 2;
    print_block(moveBlock);
}

void block_move_right(Move_Block *moveBlock) {
    int curState = moveBlock->cur_state;
    int width = moveBlock->cur_block->shape[curState][SHAPE_SIZE];
    //最右边一格的坐标是(moveBlock->x + width * 2 - 1)，然后移动一位需要加2，所以这边的判断是(moveBlock->x + width * 2 + 1)
    int end_x = (moveBlock->x + width * 2 - 1) + 2;
    if (end_x > BOUNDARY_END_X || !has_enough_area(moveBlock, end_x, moveBlock->y)) {
        //如果碰到右边界，则不进行移动操作
        return;
    }
    erase_block(moveBlock);
    moveBlock->x += 2;
    print_block(moveBlock);
}



