#include "scene.h"
#include <string.h>

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *correct = NULL;
ALLEGRO_BITMAP *wrong = NULL;
ALLEGRO_BITMAP *magic_background1 = NULL;
ALLEGRO_BITMAP *magic_background2 = NULL;
ALLEGRO_BITMAP *magic_background3 = NULL;
ALLEGRO_BITMAP *magic_background4 = NULL;
ALLEGRO_BITMAP *magic_background5 = NULL;
ALLEGRO_BITMAP *menu_background = NULL;
ALLEGRO_BITMAP *merchant_background1 = NULL;
ALLEGRO_BITMAP *merchant_background2 = NULL;
ALLEGRO_BITMAP *merchant_ok1 = NULL;
ALLEGRO_BITMAP *merchant_ok2 = NULL;
ALLEGRO_BITMAP *coin_background = NULL;
ALLEGRO_BITMAP *energy_background = NULL;
ALLEGRO_BITMAP *win_background = NULL;
ALLEGRO_BITMAP *fail_background = NULL;
ALLEGRO_SAMPLE *win_sample = NULL;
ALLEGRO_SAMPLE_INSTANCE *win_sound;
ALLEGRO_SAMPLE *fail_sample = NULL;
ALLEGRO_SAMPLE_INSTANCE *fail_sound;
ALLEGRO_BITMAP *setting_background = NULL;
ALLEGRO_BITMAP *setting_cat = NULL;
ALLEGRO_BITMAP *setting_button = NULL;
// the state of character
enum {CLOSE=0, SHOW_C, SHOW_W, SHOW_OK1, SHOW_OK2};
int answer_state = CLOSE;
int merchant_state = CLOSE;
int cat_x = 400, cat_y = 300;
// 1 left 0 right
bool magic_answers[5];
bool merchant_prices[2];
bool set_cat_change = false;
bool cat_changed = false;
int m_x, m_y;
int scene_x = 1000-2400, scene_y = 750-3200;
// function of menu
void setting_init() {
    setting_background = al_load_bitmap("./image/setting.png");
    setting_cat = al_load_bitmap("./image/set_cat.png");
}

void menu_init(){
    setting_init();
    menu_background = al_load_bitmap("./image/menu.png");
}
void setting_draw(){
    if (setting_show) {
        al_draw_bitmap(setting_background, 0, 0, 0);
        al_draw_bitmap(setting_cat, cat_x, cat_y, 0);
        set_cat_redraw(cat_x, cat_y);
    }
}

void set_cat_redraw(int x, int y) {
    if (set_cat_change) {
        cat_changed = true;
        cat_x = m_x-30;
        cat_y = y;
        set_cat_change = false;
    }
}

void setting_process(ALLEGRO_EVENT event) {
    if(setting_show) {
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            if( event.mouse.button == 1 ){
                m_x = event.mouse.x;
                m_y = event.mouse.y;

                if (m_x >= 865&& m_x <= 960 && m_y >=25 && m_y <=125) {
                    setting_show = false;
                } else if (m_x >=200 && m_x <= 750&& m_y >= 350&& m_y <=400) {
                    sound_mul = ((m_x-200)/100);
                    volumn_change = true;
                    set_cat_redraw(m_x, 300);
                    set_cat_change = true;
                }

            }
        }
    }

}

void menu_process(ALLEGRO_EVENT event) {

    /*
        TODO: Process the mouse event.
        Seperate the processing fo click event and moving event is encouraged.
    */
    if (!setting_show) {
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
            if( event.mouse.button == 1 ){
                m_x = event.mouse.x;
                m_y = event.mouse.y;
                if ( m_x>= 338.5 && m_x<= 651 && m_y >= 325 && m_y<=375) judge_next_window = true;
                else if ( m_x>= 338.5 && m_x<= 651 && m_y >=425 && m_y<=485 ) {
                       setting_show = true;
                }else if ( m_x>= 338.5 && m_x<= 651 && m_y >= 550 && m_y<= 610) {
                       msg = -1;
                }
            }
        }
    }

}


void menu_draw(){

    al_draw_bitmap(menu_background, 0, 0, 0);
    setting_draw();
}

void setting_main_init() {
    setting_button = al_load_bitmap("./image/setting_button.png");
}


void setting_button_draw(){
    if(!setting_show) {
        al_draw_bitmap(setting_button, 30, 630, 0);
    }

}

void setting_button_process(ALLEGRO_EVENT event) {
   if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
        if( event.mouse.button == 1 ){
            m_x = event.mouse.x;
            m_y = event.mouse.y;
            if (m_x>= 27.8 && m_x<= 111.11 && m_y >= 639 && m_y<=722){
                setting_show = true;
            }
        }
   }
}
void magic_window_init() {
    wrong = al_load_bitmap("./image/wrong.png");
    correct = al_load_bitmap("./image/correct.png");
    magic_background1 = al_load_bitmap("./image/magicQ1.png");
    magic_background2 = al_load_bitmap("./image/magicQ2.png");
    magic_background3 = al_load_bitmap("./image/magicQ3.png");
    magic_background4 = al_load_bitmap("./image/magicQ4.png");
    magic_background5 = al_load_bitmap("./image/magicQ5.png");
    magic_answers[0] = 1;
    magic_answers[1] = 1;
    magic_answers[2] = 1;
    magic_answers[3] = 1;
    magic_answers[4] = 1;
}

void magic_destroy(int i) {
    if (i==0 ) al_destroy_bitmap(magic_background1);
    else if (i==1) al_destroy_bitmap(magic_background2);
    else if (i==2) al_destroy_bitmap(magic_background3);
    else if (i==3) al_destroy_bitmap(magic_background4);
    else if (i==4) al_destroy_bitmap(magic_background5);
}

void merchant_destroy(int i) {
    if (i==0 ) al_destroy_bitmap(merchant_background1);
    else if (i==1) al_destroy_bitmap(merchant_background2);
}

void magic_window() {
    ALLEGRO_EVENT event;

    if(magic_show) {
        if (npc_now == 0) {
            al_draw_bitmap(magic_background1, 0, 0,0);
        } else if(npc_now==1) {
            al_draw_bitmap(magic_background2, 0, 0,0);
        } else if(npc_now==2) {
            al_draw_bitmap(magic_background3, 0, 0,0);
        } else if(npc_now==3) {
            al_draw_bitmap(magic_background4, 0, 0,0);
        } else if(npc_now==4) {
            al_draw_bitmap(magic_background5, 0, 0,0);
        }

        if( key_state[ALLEGRO_KEY_Y] ){
            if( magic_answers[npc_now] == 1) {
                answer_state = SHOW_C;
                energy_now += 1000;
            } else {
                answer_state = SHOW_W;
                energy_now -= 20;
            }
        } else if (key_state[ALLEGRO_KEY_N]) {
             if( magic_answers[npc_now] == 0) {
                answer_state = SHOW_C;
                energy_now += 5000;
            //if( event.keyboard.keycode == ALLEGRO_KEY_ENTER)  al_destroy_bitmap(correct);
            } else {
                answer_state = SHOW_W;
                energy_now -= 100;
            }
        }
    }
}

void merchant_window_init() {
    wrong = al_load_bitmap("./image/wrong.png");
    correct = al_load_bitmap("./image/correct.png");
    merchant_background1 = al_load_bitmap("./image/merchant1.png");
    merchant_background2 = al_load_bitmap("./image/merchant2.png");

    merchant_ok1 = al_load_bitmap("./image/merchant1_ok.png");
    merchant_ok2 = al_load_bitmap("./image/merchant2_ok.png");

    merchant_prices[0] = 100;
    merchant_prices[1] = 200;
}

void merchant_window() {
    ALLEGRO_EVENT event;

    if(merchant_show) {
        if (npc_now == 0) {
            al_draw_bitmap(merchant_background1, 0, 0,0);
        } else if(npc_now==1) {
            al_draw_bitmap(merchant_background2, 0, 0,0);
        }
        if( key_state[ALLEGRO_KEY_Y] ){
            if( coins_now >= merchant_prices[npc_now]) {
                if (npc_now == 0) {
                    energy_now += 500;
                    coins_now -= 10;
                    merchant_state = SHOW_OK1;

                } else {
                    energy_now += 1000;
                    coins_now -= 50;
                    merchant_state = SHOW_OK2;

                }
            } else {
                merchant_show = false;
                merchant_state = CLOSE;
            }
        } else if (key_state[ALLEGRO_KEY_N]) {
             merchant_show = false;
             merchant_state = CLOSE;
        }
    }
}

void merchant_window_draw () {
    if (merchant_state == SHOW_OK1) {
        al_draw_bitmap(merchant_ok1, 100, 100, 0);

        if (key_state[ALLEGRO_KEY_SPACE]) {
            merchant_show = false;
            merchant_state = CLOSE;
            merchant_destroy(npc_now);
            mapp[merchant_pos[npc_now].x][merchant_pos[npc_now].y] = 0;
            merchant_pos[npc_now].x = -5;
            merchant_pos[npc_now].y = -5;
        }
    } else if (merchant_state == SHOW_OK2) {
        al_draw_bitmap(merchant_ok2, 100, 100, 0);

        if (key_state[ALLEGRO_KEY_SPACE]) {
            merchant_show = false;
            merchant_state = CLOSE;
            merchant_destroy(npc_now);
            mapp[merchant_pos[npc_now].x][merchant_pos[npc_now].y] = 0;
            merchant_pos[npc_now].x = -5;
            merchant_pos[npc_now].y = -5;
        }
    }
}

void answer_draw() {
    if (answer_state == SHOW_C) {
        al_draw_bitmap(correct, 250, 200, 0);
        if (key_state[ALLEGRO_KEY_SPACE])  {
            answer_state = CLOSE;
            magic_show = false;
            magic_destroy(npc_now);
            mapp[magic_pos[npc_now].x][magic_pos[npc_now].y] = 0;
            magic_pos[npc_now].x = -10;
            magic_pos[npc_now].y = -10;
        }
    } else if (answer_state == SHOW_W) {
        al_draw_bitmap(wrong, 250, 200, 0);
        if (key_state[ALLEGRO_KEY_SPACE])  {
            answer_state = CLOSE;
            magic_show = false;
            magic_destroy(npc_now);
            mapp[magic_pos[npc_now].x][magic_pos[npc_now].y] = 0;
            magic_pos[npc_now].x = -10;
            magic_pos[npc_now].y = -10;
        }
    }
}

void menu_destroy(){
    al_destroy_bitmap(menu_background);
    al_destroy_bitmap(setting_background);
    al_destroy_bitmap(setting_cat);
}

void item_list_init() {
    coin_background = al_load_bitmap("./image/coin_state.png");
    energy_background = al_load_bitmap("./image/energy_state.png");
    font = al_load_ttf_font("./font/fontt.otf",30,0);
}

void item_list_draw() {
    al_draw_bitmap(coin_background, 0, 15,0);
    al_draw_bitmap(energy_background, 400, 0,0);
    char tmp_c[100];
    sprintf(tmp_c, "%d", coins_now);
    char tmp_e[100];
    sprintf(tmp_e, "%d", energy_now);
    al_draw_text(font, al_map_rgb(0, 0, 0), 200, 55, ALLEGRO_ALIGN_CENTRE, tmp_c);
    al_draw_text(font, al_map_rgb(0, 0, 0), 600, 50, ALLEGRO_ALIGN_CENTRE, tmp_e);
}

void win_init() {
    win_background = al_load_bitmap("./image/win.png");
    // load effective sound
    win_sample = al_load_sample("./sound/win.mp3");
    win_sound  = al_create_sample_instance(win_sample);
    al_set_sample_instance_playmode(win_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(win_sound, al_get_default_mixer());

}

void win_draw( ALLEGRO_EVENT event) {
    if (win_show) {
        game_end = true;
        map_redraw = false;
        al_draw_bitmap(win_background, 0, 0,0);
        al_play_sample_instance(win_sound);
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){

            m_x = event.mouse.x;
            m_y = event.mouse.y;
            if (m_x>= 725 && m_x<= 950 && m_y >= 625 && m_y<= 725) {
                game_scene_destroy();
                msg = -1;
            }

        }
    }
}

void fail_init() {
    fail_background = al_load_bitmap("./image/fail.png");
    fail_sample = al_load_sample("./sound/fail.mp3");
    fail_sound  = al_create_sample_instance(fail_sample);
    al_set_sample_instance_playmode(fail_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(fail_sound, al_get_default_mixer());

}
void fail_draw( ALLEGRO_EVENT event) {
    if (fail_show) {
        game_end = true;
        map_redraw = false;
        al_draw_bitmap(fail_background, 0, 0,0);
        al_play_sample_instance(fail_sound);
        if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){

            m_x = event.mouse.x;
            m_y = event.mouse.y;
            if (m_x>= 725 && m_x<= 950 && m_y >= 625 && m_y<= 725) {
                game_scene_destroy();
                msg = -1;
            }
        }
    }
}
void energy_fail () {
    if (energy_now < 0) {
        fail_show = true;
    }
}
// function of game_scene
void game_scene_init(){
    character_init();
    pos_init();
    map_init();
    item_list_init();
    magic_init();
    merchant_init();
    magic_window_init();
    merchant_window_init();
    box_init();
    coin_init();
    new_cat_init();
    book_button_init();
    shop_button_init();
    book_init();
    shop_init();
    setting_init();
    win_init();
    fail_init();
    setting_main_init();
    background = al_load_bitmap("./image/forest.png");
}

void game_scene_draw(){
    if(!game_end){
        al_draw_bitmap(background, scene_x, scene_y, 0);
        character_draw();
        map_draw(scene_x, scene_y);
        map_redraw = true;
    }

    if (map_redraw) {
        setting_button_draw();
        book_button_draw();
        shop_button_draw();
        item_list_draw();
    }
    magic_window();
    merchant_window();
    answer_draw();
    merchant_window_draw();
    setting_draw();
    book_draw();
    shop_draw();

    energy_fail ();

}

void game_scene_move(int x, int y){
    if (scene_move) {
        int tmp_x = scene_x + x;
        int tmp_y = scene_y + y;
        if (tmp_x > -1400 && tmp_x < 250)  {
                scene_x += x;
                energy_now -= 10;
        }
        if (tmp_y > -2450 && tmp_y < 200)  {
                scene_y += y;
                energy_now -= 10;
        }
        al_draw_bitmap(background, scene_x, scene_y, 0);
        map_redraw = true;
        scene_move = false;
    }

}

void book_process(ALLEGRO_EVENT event) {
   if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
        if( event.mouse.button == 1 ){
            m_x = event.mouse.x;
            m_y = event.mouse.y;
            if (m_x>= 562.5 && m_x<= 719 && m_y >= 583.3 && m_y<=695){
                book_redraw = true;
                number1 = true;
                number2 = false;
                number3 = false;
            }
            else if(m_x>= 687.5 && m_x<= 718.75 && m_y >= 166.6 && m_y<=211.1){
                book_redraw = false;
            }

            if(m_x>= 287.5 && m_x<= 418.75 && m_y >= 472.2 && m_y<=555.5){
                number1 = true;
                number2 = false;
                number3 = false;
            }
            else if(m_x>= 437.5 && m_x<= 575 && m_y >= 472.2 && m_y<=555.5){
                if(new_cat[0] == 1){
                    number1 = false;
                    number2 = true;
                    number3 = false;
                }
            }
            else if(m_x>= 593.7 && m_x<= 693.7 && m_y >= 472.2 && m_y<=555.5){
                if(new_cat[1] == 1){
                    number1 = false;
                    number2 = false;
                    number3 = true;
                }
            }
        }
    }
}

void shop_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
        if( event.mouse.button == 1 ){
            m_x = event.mouse.x;
            m_y = event.mouse.y;
            if (m_x>= 812.5 && m_x<= 968.5 && m_y >= 611.1 && m_y<=694.4){
                shop_redraw = true;
            }
            else if(m_x>= 781.5 && m_x<= 831.2 && m_y >= 200 && m_y<=266.7){
                shop_redraw = false;
            }
            if(m_x>= 250 && m_x<= 375 && m_y >= 472.2 && m_y<= 527.7){
                if (coins_now >= 30) {
                    coins_now -= 30;
                    energy_now += 500;
                }
            }
            else if(m_x>= 562.5 && m_x<= 750 && m_y >= 472.2 && m_y<=527.7){
                if (coins_now >= 50) {
                    coins_now -= 50;
                    energy_now += 1000;
                }
            }
        }
    }
}

void game_scene_destroy(){
    al_destroy_bitmap(background);
    al_destroy_bitmap(coin_background);
    al_destroy_bitmap(energy_background);
    al_destroy_bitmap(correct);
    al_destroy_bitmap(wrong);
    al_destroy_bitmap(win_background);
    al_destroy_bitmap(fail_background);
    book_destory();
    shop_destory();
    character_destory();
}
