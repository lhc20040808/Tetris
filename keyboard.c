//
// Created by 李昊琛 on 2022/8/21.
//

#include "include/keyboard.h"

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

void key_control() {
    int ch;
    while (1) {
        ch = get_ch();
        if (ch == 'q' || ch == 'Q') {
            break;
        } else if (ch == '\r') {
            printf("down\n");
        } else if (ch == '\33') {
            //在Linux终端读取^[为ESC，用'\33'表示(八进制)
            ch = getchar();
            if (ch == '[') {
                ch = getchar();
                switch (ch) {
                    case 'A':
                        printf("up\n");
                        break;
                    case 'B':
                        printf("down\n");
                        break;
                    case 'C':
                        printf("right\n");
                        break;
                    case 'D':
                        printf("left\n");
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

int main() {
    key_control();
}


