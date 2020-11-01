#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lifestate.h"
#include "ADTMap.h"
#include "ADTList.h"
#include "bmp.h"
#include "gif.h"

int positive(int a){
    if(a<0)
        return -a;
    return a;
}

int main(int argc , char* argv[] ){

    char* state=argv[1];
    int top=atoi(argv[2]);
    int left=atoi(argv[3]);
    int bottom=atoi(argv[4]);
    int right=atoi(argv[5]);
    int frames=atoi(argv[6]);
    //float zoom=atoi(argv[7]);
    int speed=atoi(argv[8]);
    int delay=atoi(argv[9]);
    char* Gif=argv[10];

    unsigned int palette[] = { 0xFF000000, 0xFFFFFFFF };


    //create a gif and a bitmap with the given sizes
    int w=bottom-top;
    w=positive(w);
    int h=right-left;
    h=positive(h);
    GIF* gif = gif_create(w, h);
	Bitmap* bitmap = bm_create(w, h);

    //set gif's delay
    gif->default_delay = delay;

    //set gif's pallete
    gif_set_palette(gif,palette,2);

    //create a LifeState from the rle format
    LifeState life=life_create_from_rle(state);
    
    //for the amount of frames given
    for(int i=0; i<frames; i++){

        bm_set_color(bitmap, bm_atoi("black"));
		bm_clear(bitmap);

        //print with white the alive cells
        for(MapNode node=map_first(life);node!=MAP_EOF;node=map_next(life,node)){
            LifeCell* cell=map_node_key(life,node);
		    bm_set_color(bitmap, bm_atoi("white"));
		    bm_fillrect(bitmap, cell->y, cell->x, cell->y, cell->x);
        }
        gif_add_frame(gif, bitmap); //and add that frame to the gif
        ListNode *loop=NULL;
        List list=life_evolve_many(life,speed,loop); //call the evolve many function with step=speed
        life=list_node_value(list,list_last(list)); //and keep the last node of the list created which is about to be the next state
        for(ListNode destroy=list_first(list) ; destroy!=list_last(list) ; destroy=list_next(list,destroy)){
            map_destroy(list_node_value(list,destroy));
        }     
        list_destroy(list);
    }
    gif_save(gif, Gif); //store the gif and free the memory
    bm_free(bitmap);
	gif_free(gif);
    life_destroy(life);
} 