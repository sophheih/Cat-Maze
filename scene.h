#include "global.h"
#include "charater.h"
#include "mapping.h"
#include "npc.h"
#include "items.h"
#include "book.h"

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void setting_draw();
void menu_destroy();

void game_scene_init();
void game_scene_draw();
//void game_scene_move(int x, int y);
void game_scene_destroy();

void magic_window_init();
void magic_window(int i);
void win_draw(ALLEGRO_EVENT event);
void fail_draw(ALLEGRO_EVENT event);

void book_process(ALLEGRO_EVENT event);
void shop_process(ALLEGRO_EVENT event);
void setting_process(ALLEGRO_EVENT event);
void setting_button_process(ALLEGRO_EVENT event);
void set_cat_redraw(int x, int y);
