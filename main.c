#include <stdio.h>
#include "include/block.h"
#include <time.h>
#include <stdlib.h>
#include "include/keyboard.h"

#define START_X 6
#define START_Y 3


void print_blocks() {
    int x = 6;
    int y = 3;

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

void key_down() {
    printf("down\n");
}

void key_left() {
    printf("left\n");
}

void key_right() {
    printf("right\n");
}

void key_enter() {
    printf("enter\n");
}

void key_quit() {
    printf("quit\n");
}

int main(int argc, const char *argv[]) {
//    print_blocks();
    init_key_control(key_down, key_left, key_right, key_enter, key_quit);
    start_key_control();
    return 0;
}

