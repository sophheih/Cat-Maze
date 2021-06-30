#include "items.h"


typedef struct items
{
    int x, y; // the position of image
    int map_x ,map_y;
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    ALLEGRO_BITMAP *pic;
    ALLEGRO_SAMPLE_INSTANCE *sound;
}Items;
Items coin1, coin2, box;
ALLEGRO_BITMAP *new_cat1 = NULL;
ALLEGRO_BITMAP *new_cat2 = NULL;

void coin_init(){
    char temp1[50];
    char temp2[50];

    sprintf( temp1, "./image/coin1.png");
    coin1.pic = al_load_bitmap(temp1);

    coin1.x = 0;
    coin1.y = 0;
    coin1.map_x = 0;
    coin1.map_y = 0;

    coin1.dir = false;

    coin1.width = al_get_bitmap_width(coin1.pic);
    coin1.height = al_get_bitmap_height(coin1.pic);

    sprintf( temp2, "./image/coin2.png");
    coin2.pic = al_load_bitmap(temp2);

    coin2.x = 0;
    coin2.y = 0;
    coin2.map_x = 0;
    coin2.map_y = 0;

    coin2.dir = false;

    coin2.width = al_get_bitmap_width(coin2.pic);
    coin2.height = al_get_bitmap_height(coin2.pic);
}

int coin_count = 0;
void coin_draw(int map_x ,int map_y) {
    Items temp_coin1 = coin1;
    Items temp_coin2 = coin2;

    if((map_x+map_y) % 2 == 0){
        temp_coin1.map_x = map_x;
        temp_coin1.map_y = map_y;

        temp_coin1.dir = false;
        if( temp_coin1.dir )
            al_draw_bitmap(temp_coin1.pic, map_x, map_y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(temp_coin1.pic, map_x, map_y, 0);
    }
    if((map_x+map_y) % 2 == 1){
        temp_coin2.map_x = map_x;
        temp_coin2.map_y = map_y;

        temp_coin2.dir = false;
        if( temp_coin2.dir )
            al_draw_bitmap(temp_coin2.pic, map_x, map_y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(temp_coin2.pic, map_x, map_y, 0);
    }
    map_redraw = false;
};

void box_init(){
    char temp[50];
    sprintf( temp, "./image/box.png");
    box.pic = al_load_bitmap(temp);

    box.x = 0;
    box.y = 0;
    box.map_x = 0;
    box.map_y = 0;

    box.dir = false;

    box.width = al_get_bitmap_width(box.pic);
    box.height = al_get_bitmap_height(box.pic);
}

void box_draw(int map_x ,int map_y) {
    Items temp_box = box;

    temp_box.map_x = map_x;
    temp_box.map_y = map_y;

    temp_box.dir = false;
    if( temp_box.dir )
        al_draw_bitmap(temp_box.pic, map_x, map_y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(temp_box.pic, map_x, map_y, 0);
    map_redraw = false;
};

int coin_check(int x, int y) {  // coin --> $10
    for (int i = 0; i < 30; i++) {
        if (coin_pos[i].x >= x-1 &&  coin_pos[i].x <= x+1 && coin_pos[i].y >= y-1 && coin_pos[i].y <= y+1) {
            coin_destory(i);
            return 1;
        }
    }
    return 0;
}

void coin_destory(int n){
    //al_destroy_bitmap(coins[n].pic);
    coin_pos[n].x = 50;
    coin_pos[n].y = 50;
    coin_redraw[n] = 1;

}

int box_check(int x ,int y){
    for (int i = 0; i < 2; i++) {
        if (box_pos[i].x == x && box_pos[i].y == y) {
            new_cat_draw(i);
            al_rest(2);
            new_cat_destroy(i);
            al_rest(1);
            box_destory(i);
            //printf("%d %d\n", x, y);
            return 1;
        }
    }
    return 0;
}
void box_destory(int n){
    box_pos[n].x = 50;
    box_pos[n].y = 50;
    box_redraw[n] = 1;
}

void new_cat_init(){
    new_cat1 = al_load_bitmap("./image/new_cat1.png");
    new_cat2 = al_load_bitmap("./image/new_cat2.png");
}

void new_cat_draw(int n){
    if(n == 0){
        new_cat[0] = 1;
        al_draw_bitmap(new_cat1, 200, 100, 0);
    }
    else if(n == 1){
        new_cat[1] = 1;
        al_draw_bitmap(new_cat2, 200, 75, 0);
    }
    al_flip_display();
}

void new_cat_destroy(int n){
    if(n == 0){
         al_destroy_bitmap(new_cat1);
    }
    else if(n == 1){
         al_destroy_bitmap(new_cat2);
    }

}
