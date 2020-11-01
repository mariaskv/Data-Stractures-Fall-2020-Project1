#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTMap.h"
#define MAX 200

int compare(Pointer a, Pointer b) 
{
   return strcmp(a,b);
}

int* create_int()
{
    int* i=malloc(sizeof(int));
    *i=1;
    return i;
}

char* create_string(char* s)
{
    char* str=malloc(MAX*(sizeof(char)));
    strcpy(str,s);
    return str;
}

int main(int argc,char* argv[])
{
    char key[MAX]; //buf for the word be read
    Map map=map_create(compare,free,free); //map to keep the words
    while(fgets(key,MAX,stdin))
    {
        if(map_find(map,key)) //if the word already is in the map
        {
            MapNode node = map_find_node(map,key); //find the value of that node
            int* value=map_node_value(map,node);
            printf("%d\n", *value); //and print it
            *value += 1; //increase the value by one
            map_insert(map, create_string(key), value); //and insert the new value
        }
        else //else
        {
            printf("0\n"); //print 0,cause the element does not exists in the map
            map_insert(map, create_string(key), create_int()); //insert a node with key the word an value 1
        }      
    }
    map_destroy(map); //destroy the map,free the memory allocated
}