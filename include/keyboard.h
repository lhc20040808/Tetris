//
// Created by 李昊琛 on 2022/8/21.
//

#ifndef TETRIS_KEYBOARD_H
#define TETRIS_KEYBOARD_H

#include <stdio.h>
#include <termios.h>

void init_key_control(void (*up)(void),void (*down)(void), void (*left)(void), void (*right)(void),
                      void (*enter)(void), void (*quit)(void));

void start_key_control();

#endif //TETRIS_KEYBOARD_H
