#include "include/canvas.h"

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


