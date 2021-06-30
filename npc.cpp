#include "npc.h"


typedef struct npc{
    int x, y; // the position of image
    int map_x ,map_y;
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    ALLEGRO_BITMAP *npc_pic;
    ALLEGRO_SAMPLE_INSTANCE *sound;
}Npc;

Npc magic, merchant;
ALLEGRO_SAMPLE *sampleM = NULL;
ALLEGRO_SAMPLE *sampleE = NULL;

void magic_init() {
    char temp[50];
    sprintf( temp, "./image/magic.png" );
    magic.npc_pic = al_load_bitmap(temp);

    // load effective sound
    sampleM = al_load_sample("./sound/en_magic.mp3");
    magic.sound  = al_create_sample_instance(sampleM);
    al_set_sample_instance_playmode(magic.sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(magic.sound, al_get_default_mixer());

    magic.x = 0;
    magic.y = 0;
    magic.map_x = 0;
    magic.map_y = 0;
    magic.dir = false;

     // initial the geometric information of character
    magic.width = al_get_bitmap_width(magic.npc_pic);
    magic.height = al_get_bitmap_height(magic.npc_pic);

}

void merchant_init() {
    char temp[50];
    sprintf( temp, "./image/merchant.png" );
    merchant.npc_pic = al_load_bitmap(temp);

    sampleE = al_load_sample("./sound/en_merchant.mp3");
    merchant.sound  = al_create_sample_instance(sampleE);
    al_set_sample_instance_playmode(merchant.sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(merchant.sound, al_get_default_mixer());

    merchant.width = al_get_bitmap_width(merchant.npc_pic);
    merchant.height = al_get_bitmap_height(merchant.npc_pic);
    merchant.x = 0;
    merchant.y = 0;
    merchant.map_x = 0;
    merchant.map_y = 0;
    merchant.dir = false;
}

void magic_draw(int map_x ,int map_y) {
    Npc temp_magic = magic;

    temp_magic.map_x = map_x;
    temp_magic.map_y = map_y;

    temp_magic.dir = false;
    if( temp_magic.dir )
        al_draw_bitmap(temp_magic.npc_pic, map_x, map_y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(temp_magic.npc_pic, map_x, map_y, 0);
    map_redraw = false;
};

void merchant_draw(int map_x ,int map_y) {
    Npc temp_merchant = merchant;

    temp_merchant.map_x = map_x;
    temp_merchant.map_y = map_y;

    temp_merchant.dir = false;
    if( temp_merchant.dir )
        al_draw_bitmap(temp_merchant.npc_pic, map_x, map_y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(temp_merchant.npc_pic, map_x, map_y, 0);
    map_redraw = false;
};


int magic_check(int x, int y) {
    for (int i =0;i < 5;i++) {
        if (magic_pos[i].x < 0) continue;
        else if ((magic_pos[i].x <= x+1 && magic_pos[i].x >= x-1)&& \
            (magic_pos[i].y <= y+1 && magic_pos[i].y >= y-1)) {
            al_play_sample_instance(magic.sound);
            npc_now = i;
            return 1;
        }
    }
    return 0;
}

int merchant_check(int x, int y) {
    for (int i =0;i < 2;i++) {
        if (merchant_pos[i].x < 0) continue;
        else if((merchant_pos[i].x <= x+1 && merchant_pos[i].x >= x-1)&& \
            (merchant_pos[i].y <= y+1 && merchant_pos[i].y >= y-1)) {
            al_play_sample_instance(merchant.sound);
            npc_now = i;
            return 1;
        }
    }
    return 0;
}

int win_check(int x, int y) {
    if(x <= 7+1 && x >= 7-1 && y <= 0+1 && y >= 0-1){

        return 1;
    }
    return 0;
}


