
//Module with the functions included at th lifestate.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ADTMap.h"
#include "lifestate.h"
 

//function compare used at the life_create

 int compare_cell(Pointer cell1, Pointer cell2) {
     LifeCell *a,*b;    
     a=cell1;
     b=cell2;
	if((*a).x==(*b).x) //if the value of x is the same
        return a->y-b->y; //return the different of y's
    else                  //else
        return a->x-b->x; //return the different of x's
} 

//funtion life_create

LifeState life_create(){
    LifeState lifestate = map_create(compare_cell,free,NULL); //create a map using compare_cell with key destroy function free                    
    return lifestate;                                         //no destroy function for the values(because they are const strings)
}

//function create from rle file

LifeState life_create_from_rle(char* file){
    LifeState life=life_create(); //create an empty lifestate
    FILE* ifp;
    if((ifp=fopen(file,"rb"))==NULL){ //open the given file and if it is empty
        life_destroy(life);           //destroy the lifestate
        exit(1);                      //exit with code 1
    }
    int x=0;    // rows
    int y=0;    // colums  
    int temp=0; // counter
    char* token=malloc(2*sizeof(char)); //buf for the charachter given
    fgets(token,2,ifp);                 //read the charachter with buf size 2(1 for the charachter and 1 for the \0)
    while(strcmp(token,"!")!=0){        //while it is not equal to ! se we have not reached the end of the file
        if(temp!=0){                    //if the counter is not equal to 0,search for any other numbers next to it
            if(strcmp(token,"b")==0){
                y+=temp;
                temp=0;
            }
            else if(strcmp(token,"$")==0){
                y=0;
                x+=temp;
                temp=0;
            }
            else if(strcmp(token,"o")==0){
                for(int i=0;i<temp;i++){
                    LifeCell *cell=malloc(sizeof(LifeCell));
                    cell->x=x;
                    cell->y=y;
                    map_insert(life,cell,"TRUE");
                    y++;
                }
                temp=0;
            }
            else{
                   temp=temp*10+atoi(token); //and increase it
            }
        }                                    //make sure that the counter will be reset to 0 before it will be reused
        else{                                //if counter is equal to 0
        if(strcmp(token,"b")==0){            //if the cell is dead increase y by one
            y++;
        }
        else if(strcmp(token,"$")==0){      //if charachter is equal to $ increase x by one because you change line
            y=0;                            //and set y as 0
            x++;
        }
        else if(strcmp(token,"o")==0){      //else if charachter is equal to o it means you find an alive cell,so insert it to the lifestate 
            LifeCell *cell=malloc(sizeof(LifeCell));
            cell->x=x;
            cell->y=y;
            map_insert(life,cell,"TRUE");
            y++;
        }
        else if(strcmp(token,"!")==0){ //you reached the end of the file
            break;
        }
        else{                          //you found a number
            temp=atoi(token);          //so store its integer value to a temporary variable
        }
        }
    fgets(token,2,ifp);     
    }
    fclose(ifp); //close the file
    free(token); //free the memory
    return life;
} 

//function life save to rle
void life_save_to_rle(LifeState state,char* file){
    FILE *ifp;
    if((ifp=fopen(file,"wb"))==NULL)
        exit(1);
    int maxx=INT_MIN;
    int maxy=INT_MIN;
    int minx=INT_MAX;
    int miny=INT_MAX;
    //find the maximum and minimum of the x,y of the cells and keep the biggest and the smalest of these two
    for(MapNode node=map_first(state);node!=MAP_EOF;node=map_next(state,node)){
        LifeCell *cell=map_node_key(state,node);
        if(cell->x > maxx)
            maxx=cell->x;
        if(cell->x < minx)
            minx=cell->x;
        if(cell->y > maxy)
            maxy=cell->y;
        if(cell->y < miny)
            miny=cell->y;
    }
    int max,min;
    if(maxx>maxy)
        max=maxx;
    else
        max=maxy;
    if(minx<miny)
        min=minx;
    else
        min=miny;
    int live=0;
    int dead=0;
    //for each pair of i,j search if it belongs to the state or not
    //keep the alive or dead in the row cells and print them when one of the other kind is found
    for(int i=min;i<=max;i++){
        for(int j=min;j<=max;j++){
            LifeCell *cell=malloc(sizeof(LifeCell));
            cell->x=i;
            cell->y=j;
            int temp=life_get_cell(state,*cell);
            if(temp==1){
                live++;
                if(dead>0){
                    if(dead>1){
                        fprintf(ifp,"%db",dead);
                    }
                    else{
                        fprintf(ifp,"b");
                    }
                    dead=0;
                }
            }
            else if(temp==0){
                dead++;
                if(live>0){
                    if(live>1){
                        fprintf(ifp,"%do",live);
                    }
                    else{
                        fprintf(ifp,"o");
                    }
                    live=0;
                }
            }
        free(cell);
        }
            dead=0;
            if(live>0){
                if(live>1){
                    fprintf(ifp,"%do",live);
                }
                else{
                    fprintf(ifp,"o");
                }
                live=0;
            }
            if(i!=max)
                fprintf(ifp,"$"); //at the end of each line print $
    }
    fprintf(ifp,"!"); //at the end of the file print !
    fclose(ifp);
}
//function life set cell

void life_set_cell(LifeState state,LifeCell cell,bool value){
    LifeCell *test=&cell; //store the value of the cell to a temporary variable
    MapNode temp=map_find_node(state,test); //search for that node into the state
    if(temp==MAP_EOF){  //if the node does not exist into the state
        if(value==1){   //and the boolean value is equal to 1 insert it into the state
            LifeCell *Cell=malloc(sizeof(LifeCell));
            Cell->x=cell.x;
            Cell->y=cell.y;
            map_insert(state,Cell,"TRUE");
        }
    }
    else if(temp!=MAP_EOF){ //if the cell exists into the state
        if(value==0){       //and value is equal to 0   
            map_remove(state,test); //remove it from the state
        }
    }
}

//function life get cell

bool life_get_cell(LifeState state,LifeCell cell){
    LifeCell *temp=&cell; 
    Pointer find=map_find(state,temp);
    //if the element exists into the state return 1 else return 0
    if(find!=NULL)
        return 1;
    else
        return 0;
}

//function life evolve

LifeState life_evolve(LifeState state){
    LifeState final=life_create();
    int maxx=INT_MIN;
    int maxy=INT_MIN;
    int minx=INT_MAX;
    int miny=INT_MAX;
    //find the maximum and minimum of the x,y of the cells and keep the biggest and the smalest of these two
    for(MapNode node=map_first(state);node!=MAP_EOF;node=map_next(state,node)){
        LifeCell *cell=map_node_key(state,node);
        if(cell->x > maxx)
            maxx=cell->x;
        if(cell->x < minx)
            minx=cell->x;
        if(cell->y > maxy)
            maxy=cell->y;
        if(cell->y < miny)
            miny=cell->y;
    }
    int max,min;
    if(maxx>maxy)
        max=maxx;
    else
        max=maxy;
    if(minx<miny)
        min=minx;
    else
        min=miny;
    LifeCell *test=malloc(sizeof(LifeCell));
    //for each pair of x,y find the neighbours and count how many of them are alive
    for(int x=min-1;x<=max+1;x++){
        for(int y=min-1;y<=max+1;y++){
            int counter=0;
            for(int i=x-1;i<=x+1;i++){
                for(int j=y-1;j<=y+1;j++){
                    if(i!=x || j!=y){
                    test->x=i;
                    test->y=j;
                    if(map_find(state,test)!=NULL)
                        counter++;
                    }
                }
            }
            LifeCell *temp=malloc(sizeof(LifeCell));
            temp->x=x;
            temp->y=y;
            //if that pair of x,y belongs to the state(it is alive)
            if(map_find(state,temp)!=NULL){
                if(counter>=2 && counter<=3) //if it has 2<=neighbours<=3
                    map_insert(final,temp,"TRUE"); //insert it to the new state
                else
                    free(temp);
                
            }
            else{
                if(counter==3) //if the pair does not exist into the state and has exactly 3 neighbours
                    map_insert(final,temp,"TRUE"); //insert it into the new state
                else
                    free(temp);
            }
        }
    }
free(test);
return final; //return the new state
}

//function life destroy

void life_destroy(LifeState state){
     map_destroy(state); //destroy the map using the map_destroy function
}