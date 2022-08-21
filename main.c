#include <stdio.h>
#include "include/block.h"
#include <time.h>
#include <stdlib.h>
#include "include/keyboard.h"

#define START_X 6
#define START_Y 3

Move_Block *cur_m_block = NULL;

void print_blocks() {
    int x = START_X;
    int y = START_Y;

    for (int i = 0; i < BLOCK_SIZE; i++) {
        print_all_type_of_block(x, y, &shapes[i]);
        x = 6;
        y += 4;
        getchar();
    }
}

/**
 * Move_Block保存当前正在移动的方块
 * 该方法会生成一个Block存在Move_Block->cur_block中
 * 并且会重置坐标和状态值
 * @param m_block
 */
void generate_blocks(Move_Block *m_block) {
    srandom((unsigned int) time(NULL));
    int i_block = (int) random() % BLOCK_SIZE;
    m_block->x = START_X;
    m_block->y = START_Y;
    m_block->cur_state = 0;
    m_block->cur_block = &shapes[i_block];
}

void key_up() {
    if (cur_m_block) {
        block_rotate(cur_m_block);
    }
}

void key_down() {
    if (cur_m_block) {
        block_move_down(cur_m_block);
    }
}

void key_left() {
    if (cur_m_block) {
        block_move_left(cur_m_block);
    }
}

void key_right() {
    if (cur_m_block) {
        block_move_right(cur_m_block);
    }
}

void key_enter() {
    printf("enter\n");
}

void key_quit() {
    printf("quit\n");
}

int main(int argc, const char *argv[]) {
    printf("\033[2J");//清屏
    printf("\033[?25l");//隐藏光标
    //注册键盘监听
    init_key_control(key_up, key_down, key_left, key_right, key_enter, key_quit);
    //初始化一个块
    cur_m_block = malloc(sizeof(Move_Block));
    generate_blocks(cur_m_block);
    print_block(cur_m_block);//显示块
    start_key_control();//启动键盘监听
    printf("\033[?25h");//显示光标
    return 0;
}

