#include "mapping.h"
void map_draw(int x, int y){
    if (map_redraw) {

        for (int i=0; i<5; i++) {
            magic_draw((-1400+(magic_pos[i].x-1)*(2400/22))+(x+1400), (-2450+(magic_pos[i].y-1)*(3200/26))+(y+2450));
        }
        for (int i=0; i<2; i++){
            merchant_draw((-1400+(merchant_pos[i].x-1)*(2400/22))+(x+1400), (-2450+(merchant_pos[i].y-1)*(3200/26))+(y+2450));
        }
        for (int i = 0; i < 2; i++) {
            if(box_redraw[i] == 0){
                box_draw((-1400+(box_pos[i].x)*(2400/22))+(x+1400), (-2450+(box_pos[i].y)*(3200/26))+(y+2450));
            }
        }
        for(int i = 0; i < 30; i++){
            if(coin_redraw[i] == 0){
                coin_draw((-1400+(coin_pos[i].x)*(2400/22))+(x+1400), (-2450+(coin_pos[i].y)*(3200/26))+(y+2450));
            }
        }
        map_redraw = false;
    }


    //coin_draw(i*(2400/22), j*(3200/26));

}



