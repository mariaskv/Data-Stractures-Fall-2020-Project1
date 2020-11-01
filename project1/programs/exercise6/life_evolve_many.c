//module που περιέχει την υλοποίηση του life_evolve_many της άσκησης 6
#include <stdio.h>
#include <stdlib.h>
#include "ADTList.h"
#include "ADTMap.h"
#include "lifestate.h"


//two states are compared by their size
//if it is the same they are compared by their cells
//if they are all the same returns 0
//if any other case returns -1
int compare_lifestate(Pointer a,Pointer b){
    LifeState state1=a;
    LifeState state2=b;
    if(map_size(state1)==map_size(state2)){
        int counter=0;
        MapNode node1=map_first(state1);
        MapNode node2=map_first(state2);
        for(int i=0;i<map_size(state1);i++){
            LifeCell *cell1=map_node_key(state1,node1);
            LifeCell *cell2=map_node_key(state2,node2);
            node1=map_next(state1,node1);
            node2=map_next(state2,node2);
            if(cell1->x==cell2->x && cell1->y==cell2->y)
                counter++;
        }
        if(counter==map_size(state1))
            return 0;
    }
    return -1;
}


//function life_evolve_many

List life_evolve_many(LifeState state, int steps, ListNode* loop){
    List list=list_create(NULL); //map_destroy could also be used but I need to keep the last node so I erase them manually
    LifeState insert=state;
    list_insert_next(list,list_last(list),insert);
    //cals the life_evolve function as many times as the step's value and insert each state into a list
    for(int i=0;i<steps;i++){
        insert=life_evolve(insert);
        list_insert_next(list,list_last(list),insert);
        //if loop is equal to NULL search if the last function already exists into the list and store it into loop
        if(loop==NULL){ 
            loop=list_find(list,insert,compare_lifestate);
        }
    }
    return list;
}