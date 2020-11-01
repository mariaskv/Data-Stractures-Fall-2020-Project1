/// Βιβλιοθήκη που περιέχει όλα τα πρότυπα του module Life
//Το module Life υλοποιείται μέσω ADTVector

#pragma once // #include το πολύ μία φορά

#include "ADTMap.h"

#include "ADTList.h"

#include "common_types.h"

typedef Map LifeState;


typedef struct{
    int x,y;
} LifeCell;


//ΣΥΜΒΑΤΙΚΑ ΘΕΩΡΕΙΤΑΙ:
//ΖΩΝΤΑΝΟ=1
//ΝΕΚΡΟ=0

//Δημιουργεί μία κατάσταση του παιχνιδιού όπου όλα τα κελιά είναι ΝΕΚΡΑ
LifeState life_create();

//Δημιουργεί μία κατάσταση στο παιχνίδι με βάση τα δεδομένα του αρχείου file
LifeState life_create_from_rle(char* file);

//Αποθηκεύει την κατάσταση state στο αρχείο file (RLE format)
void life_save_to_rle(LifeState state,char* file);

//Επιστρέφει την τιμή του κελιού cell στην κατάσταση state(true:ζωντανο,false:νεκρό)
bool life_get_cell(LifeState state,LifeCell cell);

//Αλλάζει την τιμή του κελιού cell στην κατάσταση state
void life_set_cell(LifeState state,LifeCell cell,bool value);

//Παράγει μια νέα κατάσταση που προκύπτει από την εξέλιξη της κατάστασης state
LifeState life_evolve(LifeState state);

//Καταστρέφει την κατάσταση ελευθερώντας οποιαδήποτε μνήμη έχει δεσμευτεί
void life_destroy(LifeState state);

// Επιστρέφει μία λίστα από το πολύ steps εξελίξεις, ξεκινώνας από την κατάσταση
// state. Αν βρεθεί επανάληψη τότε στο *loop αποθηκεύεται ο κόμβος στον οποίο
// συνεχίζει η εξέλιξη μετά τον τελευταίο κόμβο της λίστας, διαφορετικά NULL
List life_evolve_many(LifeState state, int steps, ListNode* loop);