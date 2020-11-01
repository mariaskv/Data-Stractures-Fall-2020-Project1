#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define LINES 100000

int main(int argc,char* argv[])
{
   char lines[LINES][MAX]; //array of words 
   int i=0; //counter
   while(fgets(lines[i],MAX,stdin)) //while there are still data to be read
   {
       int sum=0; //counter for the times we have read each word in the past
       if(i>0) //if we have read at least one word
       {
           for(int j=0;j<i;j++) //for each of the words have been read before
           {
              if(strcmp(lines[i],lines[j])==0) //compare the word given with the one that have just been read
                  sum++; //increase the counter by one
           }
       }
       printf("%d\n",sum); //print the number of the times each word has been read
       i++; //move on to the next position of the array
   }
}