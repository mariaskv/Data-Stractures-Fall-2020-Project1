//unit tests for the life.c module

#include <stdio.h>
#include <string.h>
#include "acutest.h"
#include "lifestate.h"

void life_create_test(void){
//check for life_create function
    LifeState life=life_create();
    TEST_CHECK(life!=NULL);
    life_destroy(life);
} 

void life_create_from_rle_test(void){
//check for create_from_rle function
    char* file="test.txt";
    LifeState life=life_create_from_rle(file);
    TEST_CHECK(map_size(life)>0);
    MapNode node=map_first(life);
//check for get_cell function
    for(int i=0;i<map_size(life);i++){
        int check=life_get_cell(life,*(LifeCell*)map_node_key(life,node));
        TEST_CHECK(check==1);
        node=map_next(life,node);
    }
    life_destroy(life);
} 

void life_set_cell_test(void){
//check for set_cell function
    LifeState state=life_create();
        LifeCell *cell=malloc(sizeof(LifeCell));
        cell->x=1;
        cell->y=1;
        map_insert(state,cell,"TRUE");
        int test=map_size(state);

        life_set_cell(state,*(LifeCell*)cell,1);
        TEST_CHECK(map_size(state)==test);

        life_set_cell(state,*(LifeCell*)cell,0);
        TEST_CHECK(map_size(state)==test-1);

        LifeCell cell1;
        cell1.x=5;
        cell1.y=4;

        test=map_size(state);
        life_set_cell(state,cell1,0);
        TEST_CHECK(map_size(state)==test);

        life_set_cell(state,cell1,1);
        TEST_CHECK(map_size(state)==test+1);

        life_destroy(state);
} 


void life_save_to_rle_test(void){
    char* file="temp.txt";
    char* temp="test.txt";
    LifeState state=life_create_from_rle(temp);
    life_save_to_rle(state,file);
    FILE *ifp1;
    if((ifp1=fopen(file,"rb"))==NULL)
        exit(1);
    char text1[1000];
    fscanf(ifp1,"%s",text1);
    FILE *ifp2;
    if((ifp2=fopen(temp,"rb"))==NULL)
        exit(1);
    char text2[1000];
    fscanf(ifp2,"%s",text2);
    TEST_CHECK(strcmp(text1,text2)==0);
    life_destroy(state);
    fclose(ifp1);
    fclose(ifp2);
}

void life_evolve_test(void){
//check for live evolve function
    char* file="test.txt";
    LifeState state=life_create_from_rle(file);
    LifeState test=life_evolve(state);
    TEST_CHECK(map_size(test)==5);
    life_destroy(test);
    life_destroy(state);    
}

TEST_LIST = {
	{ "life_create", life_create_test},
    { "life_create_from_rle", life_create_from_rle_test},
    { "life_save_to_rle_test", life_save_to_rle_test},
    { "life_get_cell", life_create_from_rle_test},
    { "life_set_cell", life_set_cell_test},
    { "life_evolve_test", life_evolve_test},
	{ NULL, NULL } 
};