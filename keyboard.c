//
// Created by 李昊琛 on 2022/8/21.
//

#include "include/keyboard.h"

void (*up_ptr)(void) = NULL;

void (*down_ptr)(void) = NULL;

void (*left_ptr)(void) = NULL;

void (*right_ptr)(void) = NULL;

void (*enter_ptr)(void) = NULL;

/**
 * 初始化键盘监听
 * @param down 向下建的
 * @param left
 * @param right
 * @param quit
 */
void init_key_control(void (*up)(void), void (*down)(void), void (*left)(void), void (*right)(void),
                      void (*enter)(void)) {
    up_ptr = up;
    down_ptr = down;
    left_ptr = left;
    right_ptr = right;
    enter_ptr = enter;
}

int get_ch() {
    struct termios term_raw, term_old;
    //保存当前属性
    tcgetattr(0, &term_old);
    //获取原始属性
    cfmakeraw(&term_raw);
    //设置原始属性
    tcsetattr(0, 0, &term_raw);
    int ch = getchar();
    //恢复原来的属性
    tcsetattr(0, 0, &term_old);
    return ch;
}

void start_key_control() {
    int ch;
    while (1) {
        ch = get_ch();
        if (ch == 'q' || ch == 'Q') {
            break;
        } else if (ch == '\r') {
            enter_ptr();
        } else if (ch == '\33') {
            //在Linux终端读取^[为ESC，用'\33'表示(八进制)
            ch = getchar();
            if (ch == '[') {
                ch = getchar();
                switch (ch) {
                    case 'A':
                        up_ptr();
                        break;
                    case 'B':
                        down_ptr();
                        break;
                    case 'C':
                        right_ptr();
                        break;
                    case 'D':
                        left_ptr();
                        break;
                    default:
                        break;
                }
            }
        }
    }
}


