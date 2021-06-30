#include "book.h"

ALLEGRO_BITMAP *book_button = NULL;
ALLEGRO_BITMAP *book[8];

void book_button_init(){
    book_button = al_load_bitmap("./image/book_button.png");
}

void book_button_draw(){
    al_draw_bitmap(book_button, 550, 600, 0);
}

void book_init(){
    for(int i = 1 ; i <= 8 ; i++){
        char temp[50];
        sprintf( temp, "./image/book%d.png", i);
        book[i-1] = al_load_bitmap(temp);
    }
}

void book_draw(){
    if(book_redraw){
        map_redraw = false;
        al_draw_bitmap(book[0], 0, 0, 0);
        change_cat = 0;
        if(new_cat[0] == 1 && new_cat[1] != 1){
            if(number2){
                al_draw_bitmap(book[3], 0, 0, 0);
                change_cat = 2;
            }
            else if(number1){
                al_draw_bitmap(book[1], 0, 0, 0);
                change_cat = 0;
            }
        }
        else if(new_cat[0] != 1 && new_cat[1] == 1){
            if(number3){
                al_draw_bitmap(book[7], 0, 0, 0);
                change_cat = 4;
            }
            else if(number1){
                al_draw_bitmap(book[6], 0, 0, 0);
                change_cat = 0;
            }
        }
        else if(new_cat[0] == 1 && new_cat[1] == 1){
            if(number2){
                al_draw_bitmap(book[4], 0, 0, 0);
                change_cat = 2;
            }
            else if(number3){
                al_draw_bitmap(book[5], 0, 0, 0);
                change_cat = 4;
            }
            else if(number1){
                al_draw_bitmap(book[2], 0, 0, 0);
                change_cat = 0;
            }
        }
    }
}

void book_destory(){
    al_destroy_bitmap(book_button);
    al_destroy_bitmap(book[0]);
    al_destroy_bitmap(book[1]);
    al_destroy_bitmap(book[2]);
    al_destroy_bitmap(book[3]);
    al_destroy_bitmap(book[4]);
    al_destroy_bitmap(book[5]);
    al_destroy_bitmap(book[6]);
    al_destroy_bitmap(book[7]);
}
