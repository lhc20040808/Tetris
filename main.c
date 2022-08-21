#include <stdio.h>
#include "include/block.h"

void print_blocks() {
    int x = 6;
    int y = 3;

    for (int i = 0; i < BLOCK_SIZE; i++) {
        print_block_of_all_type(x, y, &shapes[i]);
        x = 6;
        y += 4;
        getchar();
    }
}

int main(int argc, const char *argv[]) {
    print_blocks();
    return 0;
}

