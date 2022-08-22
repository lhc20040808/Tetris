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
/**
 * 掉落间隔，单位微秒
 */
int drop_interval = 800 * 1000;
/**
 * 用户游戏等级
 */
int user_level = 0;
/**
 * 用户游戏分数
 */
int user_score = 0;

void exit_game();

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

/**
 *
 * @return 0 游戏结束 1游戏结束
 */
int check_end_game() {
    if (cur_m_block == NULL) {
        return 0;
    }

    //方块当前位置大于起始行位置就不判了，说明在下落过程中
    if (cur_m_block->y > BLOCK_SHOW_Y) {
        return 0;
    }

    if (has_enough_area(cur_m_block, cur_m_block->x, cur_m_block->y)) {
        return 0;
    }

    return 1;
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
    block_move_left(cur_m_block);
}

void key_right() {
    if (!cur_m_block) {
        return;
    }
    block_move_right(cur_m_block);
}

void key_enter() {
    if (!cur_m_block) {
        return;
    }

    while (1) {
        if (block_move_down(cur_m_block)) {
            break;
        }
    }
}

/**
 * 监听信号量的回调函数
 * @param signum
 */
void sig_handler(int signum) {
    if (signum != SIGALRM) {
        return;
    }
    if (check_end_game()) {
        exit_game();
    } else {
        key_down();
    }
}

void exit_game() {
    printf("\033[32;9H**************   Game Over  **************\033[0m");
    printf("\033[?25h");//显示光标
    printf("\n\n");
    recover_termios();
    exit(0);
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
    start_timer(drop_interval);//启动定时器
    start_key_control();//启动键盘监听，进入死循环直到按q退出
}

void next_block() {
    generate_blocks(cur_m_block);
    erase_next_area();
    show_next_block();
}

int main(int argc, const char *argv[]) {
    init_next_index();
    init_key_control(key_up, key_down, key_left, key_right, key_enter);//注册键盘监听
    init_game_ui();//绘制游戏Ui
    //初始化一个块
    cur_m_block = malloc(sizeof(Move_Block));
    generate_blocks(cur_m_block);
    show_next_block();
    print_block(cur_m_block);//显示块
    start_game();
    printf("\033[?25h");//显示光标
    return 0;
}

