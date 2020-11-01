#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTSet.h"
#define MAX 200

int compare(Pointer a, Pointer b) //compare function
{
   return strcmp(a,b);
}

char* create_string(char* s) //create string function
{
    char* str=malloc(MAX*(sizeof(char)));
    strcpy(str,s);
    return str;
}

int main(int argc,char* argv[])
{
    char value[MAX]; //temporary variable for fgets
    Set set=set_create(compare,free); //create a set so to keep the inputs
    while(fgets(value,MAX,stdin))
    {
        char* buf=NULL;
        set_insert(set,create_string(value)); //insert to the set the input
        SetNode node=set_find_node(set,value); //find into the set the node for value=input
        node=set_next(set,node); //keep the next node
        if(node!=SET_EOF) //if you have not reached the end of the set
            buf=set_node_value(set,node); //keep the value of that node
        if(buf) //if it is not equal to NULL
        {
            printf("%s",buf); //print that node because it is the minimum of the nodes that are bigger or equal from the node
        }                     //given to the input
        else //else
        {
            printf("<none>\n"); //print none because there is not such a node
        }
    }
    set_destroy(set); //destroy the set,free the memory
}