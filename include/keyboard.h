#ifndef TETRIS_KEYBOARD_H
#define TETRIS_KEYBOARD_H

#include <stdio.h>
#include <termios.h>

void init_key_control(void (*up)(void), void (*down)(void), void (*left)(void),
                      void (*right)(void), void (*enter)(void));

void start_key_control();

void recover_termios();

#endif //TETRIS_KEYBOARD_H
