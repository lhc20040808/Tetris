#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include "include/block.h"
#include "include/keyboard.h"
#include "include/canvas.h"

Move_Block *cur_m_block = NULL;
int next_block_index = -1;

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


void show_next_block() {
    Move_Block tmp;
    tmp.x = NEXT_BLOCK_X;
    tmp.y = NEXT_BLOCK_Y;
    tmp.cur_state = 0;
    tmp.cur_block = &shapes[next_block_index];
    print_block(&tmp);
}

/**
 * Move_Block保存当前正在移动的方块
 * 该方法会生成一个Block存在Move_Block->cur_block中
 * 并且会重置坐标和状态值
 * @param m_block
 */
void generate_blocks(Move_Block *m_block) {
    //更新当前出现的方块
    m_block->x = BLOCK_SHOW_X;
    m_block->y = BLOCK_SHOW_Y;
    m_block->cur_state = 0;
    m_block->cur_block = &shapes[next_block_index];
    next_block_index = (int) random() % BLOCK_SIZE;
}

void key_up() {
    if (!cur_m_block) {
        return;
    }
    block_rotate(cur_m_block);
}

void key_down() {
    if (!cur_m_block) {
        return;
    }

    block_move_down(cur_m_block);
}

void key_left() {
    if (!cur_m_block) {
        return;
    }

    if (cur_m_block->x - 1 < BOUNDARY_START_X) {
        //如果碰到左边界，则不进行任何移动操作
        return;
    }

    block_move_left(cur_m_block);
}

void key_right() {
    if (!cur_m_block) {
        return;
    }

    int curState = cur_m_block->cur_state;
    int width = cur_m_block->cur_block->shape[curState][SHAPE_SIZE];
    if (cur_m_block->x + width * 2 + 1 > BOUNDARY_END_X) {
        //如果碰到右边界，则不进行移动操作
        return;
    }
    block_move_right(cur_m_block);
}

void key_enter() {
    if (!cur_m_block) {
        return;
    }
    printf("enter\n");
}

/**
 * 监听信号量的回调函数
 * @param signum
 */
void sig_handler(int signum) {
    key_down();
}

void init_next_index() {
    srandom(time(NULL));
    if (next_block_index < 0) {
        next_block_index = (int) random() % BLOCK_SIZE;
    }
}

void start_timer(int interval) {
    signal(SIGALRM, sig_handler);
    struct itimerval timer_val = {{0, interval},
                                  {0, 500 * 1000}};
    setitimer(ITIMER_REAL, &timer_val, NULL);
}

void start_game() {
    start_timer(800 * 1000);//启动定时器
    start_key_control();//启动键盘监听，进入死循环直到按q退出
}

int main(int argc, const char *argv[]) {
    init_next_index();
    init_key_control(key_up, key_down, key_left, key_right, key_enter);//注册键盘监听
    //初始化一个块
    cur_m_block = malloc(sizeof(Move_Block));
    generate_blocks(cur_m_block);
    init_game_ui();//绘制游戏Ui
    show_next_block();
    print_block(cur_m_block);//显示块
    start_game();
    printf("\033[?25h");//显示光标
    return 0;
}

