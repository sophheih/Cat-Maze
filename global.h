#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
typedef struct pos{
    int x;
    int y;
}Pos;
extern int msg;
// note that you can't assign initial value here!
extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool judge_next_window;
extern ALLEGRO_TIMER *fps;
extern int mapp[22][26];
extern int item(int x, int y);
extern int npc_now;
extern int coins_now;
extern int energy_now;
extern bool map_redraw;
extern bool book_redraw;
extern bool shop_redraw;
extern bool number1;
extern bool number2;
extern bool number3;
extern bool magic_show;
extern bool merchant_show;
extern bool win_show;
extern bool fail_show;
extern bool setting_show;
extern bool volumn_change;
extern bool game_end;
extern bool scene_move;
extern Pos magic_pos[5];
extern Pos merchant_pos[2];
extern Pos box_pos[2];
extern Pos coin_pos[30];
extern int box_redraw[2];
extern int coin_redraw[30];
extern int new_cat[2];
extern int change_cat;
extern int sound_mul;
void map_init();
void pos_init();

#endif
