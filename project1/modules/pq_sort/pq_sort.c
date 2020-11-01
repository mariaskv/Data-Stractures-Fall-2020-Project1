////////////////////////////////
//
// Υλοποίηση του pq_sort module
//
////////////////////////////////

#include <stdlib.h>

#include "pq_sort.h"
#include "ADTPriorityQueue.h"
#include "ADTVector.h"
#include "ADTList.h"

void pq_sort_vector(Vector vec, CompareFunc compare) {
	DestroyFunc old_destroy = vector_set_destroy_value(vec, NULL); //set vector destroy fynction as null so not to destroy the elements
	PriorityQueue pqueue=pqueue_create(compare,NULL,vec); //create a pqueue
	for(int i=vector_size(vec)-1;i>=0;i--) //begining from the end of the vector
	{
		vector_set_at(vec,i,pqueue_max(pqueue)); //set at the i-th position of the vector the max element of the pqueue
		pqueue_remove_max(pqueue); //remove the max element of the pqueue
	}
	pqueue_destroy(pqueue); //destroy the pqueue
	vector_set_destroy_value(vec, old_destroy); //reset the destroy function of the vector to the previous one
}

void pq_sort_list(List list, CompareFunc compare) {
	DestroyFunc old_destroy = list_set_destroy_value(list, NULL); //set list destroy fynction as null so not to destroy the elements
	Vector value=vector_create(list_size(list),NULL); //create a vector
	ListNode node=list_first(list); 
	for(int i=0;i<list_size(list);i++) 
	{
		vector_set_at(value,i,list_node_value(list,node)); //insert all the elements of the list in a vector
		node=list_next(list,node);
	}
	pq_sort_vector(value,compare); //sort the vector using the previous function
	node=LIST_BOF; //starting from the node before the first node of the list
	for(int i=0;i<list_size(list);i++)
	{
		list_remove_next(list,node); //remove the next node from the given
		list_insert_next(list,node,vector_get_at(value,i)); //and re-insert it with the first value of the sorted vector
		if(i==0) //if node=LIST_BOF the next node is the list's first
			node=list_first(list);
		else
			node=list_next(list,node); //else move on to the next node
	}
	vector_destroy(value); //destroy vector
	list_set_destroy_value(list, old_destroy); //reset list's destroy function
	
}