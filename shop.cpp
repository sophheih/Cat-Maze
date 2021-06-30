#include "shop.h"


ALLEGRO_BITMAP *shop_button = NULL;
ALLEGRO_BITMAP *shop = NULL;

void shop_button_init(){
    shop_button = al_load_bitmap("./image/shop_button.png");
}

void shop_button_draw(){
    al_draw_bitmap(shop_button, 750, 550, 0);
}


void shop_init(){
    shop = al_load_bitmap("./image/shop.png");
}

void shop_draw(){
    if(shop_redraw){
        map_redraw = false;
        al_draw_bitmap(shop, 0, 0, 0);
    }
}

void shop_destory(){
    al_destroy_bitmap(shop);
    al_destroy_bitmap(shop_button);
}



