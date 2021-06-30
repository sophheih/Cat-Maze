#include "charater.h"

// the state of character
typedef struct character {
    int x, y; // the position of image
    int x_map ,y_map;
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[6];
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation

} Character;
Character chara;
ALLEGRO_BITMAP *background2 = NULL;
enum {STOP = 0, MOVE, ATK};
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_SAMPLE *sampleMM = NULL;
ALLEGRO_SAMPLE *sampleEE = NULL;

void character_init(){
    // load character images
    for(int i = 1 ; i <= 6 ; i++){
        char temp[50];
        sprintf( temp, "./image/cat_move%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
    }

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = WIDTH/2;
    chara.y = HEIGHT/2;
    chara.x_map = 2000;
    chara.y_map = 3000;
    chara.dir = false;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;

}

void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;

        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER){
            int temp_x = chara.x_map/(2400/22);
            int temp_y = chara.y_map/(3200/26);
            //printf("temp_X %d %d\n",temp_x, temp_y);
            if (magic_check(temp_x, temp_y)) {
                chara.state = STOP;
                magic_show = true;

            } else if (merchant_check(temp_x, temp_y)) {
                chara.state = STOP;
                merchant_show = true;

            } else if (win_check(temp_x, temp_y)) {

                chara.state = STOP;
                win_show = true;
            }

        }

    }
}

int w =0, a =0, s=0, d=0;

void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        if (item(chara.x_map, chara.y_map-5) == 0) {

            if (chara.y > 250) {
                chara.y_map -=5;
                chara.y -= 5;
                energy_now -= 10;
            } else {

                chara.y_map -=10;
                game_scene_move(0, 10);
                if (w == 0) scene_move = true;
                w++;
            }


        }
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_A] ){
        chara.dir = false;
        if (item(chara.x_map-5, chara.y_map) == 0) {
            if (chara.x > 250) {

                chara.x_map -= 5;
                chara.x -= 5;
                energy_now -= 10;
            } else {
                chara.x_map -= 10;
                energy_now -= 10;
                game_scene_move(10, 0);
                if (a == 0) scene_move = true;
                a++;
            }
        }
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        if (item(chara.x_map, chara.y_map+5) == 0) {
            if (chara.y < 500) {
                chara.y += 5;
                chara.y_map += 5;
                energy_now -= 10;
            } else {
                chara.y_map += 10;
                energy_now -= 10;
                game_scene_move(0, -10);
                if (s == 0) scene_move = true;
                s++;
            }
        }
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        chara.dir = true;
        if (item(chara.x_map+5, chara.y_map) == 0) {
            if (chara.x < 750) {
                chara.x += 5;
                chara.x_map += 5;
                energy_now -= 10;
            } else {
                chara.x_map += 10;
                game_scene_move(-10, 0);
                if (d == 0) scene_move = true;
                d++;
            }
        }
        chara.state = MOVE;
    }else if( chara.anime == chara.anime_time-1 ){
        chara.anime = 0;
        chara.state = STOP;
    }else if ( chara.anime == 0 ){
        chara.state = STOP;
    }
    w =0;
    a=0;
    d=0;
    s=0;
    if(coin_check(chara.x_map/(2400/22), chara.y_map/(3200/26)) == 1){
        if((chara.x_map/(2400/22) + chara.y_map/(3200/26)) % 2 == 0){
            coins_now = coins_now + 30;
        }
        else{
            coins_now = coins_now + 10;
        }
    }
    if(box_check(chara.x_map/(2400/22), chara.y_map/(3200/26)) == 1){
        printf("new cat!\n");
    }
}

void character_draw(){
    // with the state, draw corresponding image
    if( chara.state == STOP ){
        //map_redraw = true;
        if( chara.dir )
            al_draw_bitmap(chara.img_move[0+change_cat], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0+change_cat], chara.x, chara.y, 0);
    }else if( chara.state == MOVE ){
        //map_redraw = true;
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0+change_cat], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[1+change_cat], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0+change_cat], chara.x, chara.y,0);
            }
            else{
                al_draw_bitmap(chara.img_move[1+change_cat], chara.x, chara.y, 0);
            }
        }

    }
}
void character_destory(){
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_bitmap(chara.img_move[2]);
    al_destroy_bitmap(chara.img_move[3]);
    al_destroy_bitmap(chara.img_move[4]);
    al_destroy_bitmap(chara.img_move[5]);
}
