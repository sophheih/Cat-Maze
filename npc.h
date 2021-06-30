#include "global.h"
void magic_init();
void merchant_init();
void magic_draw(int map_x ,int map_y);
void merchant_draw(int map_x, int map_y);
void magic_tap(int map_x ,int map_y);
void merchant_tap(int map_x ,int map_y);
int magic_check(int x, int y);
int merchant_check(int x, int y);
int win_check(int x, int y);
