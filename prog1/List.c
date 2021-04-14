#include "List.h"
#include <stdlib.h>
#include <stdio.h>

// Type 1: List is a list with extra node structure
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
}NodeObj;
typedef NodeObj* Node;

typedef struct ListObj{
    Node head;
    int length;
}ListObj;


//creates a new list and sets its contents
List newList(void){
    List l = (List) malloc(sizeof(ListObj)); //allocating memory for the linked list
    if (l != NULL){
	l->length = 0; //starting length
	l->head = NULL; //the first element in the list
    }
    return l; //returns the new list
}


//creates the node and sets its contents
Node newNode(int data){
    Node n = (Node) malloc(sizeof(NodeObj)); //allocating memory for the node
    if (n != NULL){
	n->data = data; //the data for the node
	n->next = NULL; //setting the following node/position to null
    }
    return n; //returning new node
}


//frees memory associated with pN
void freeNode(Node *pN){
    if (pN != NULL && *pN != NULL){
        free(*pN); //frees the node
        *pN = NULL;
    }
}


//frees memory associated with pL
void freeList( List* pL ){
    if (pL != NULL && *pL != NULL){
	Node temp; //temp node in order to free current node
	while ((*pL)->head != NULL){ //while pL != the last element in the list
	    temp = (*pL)->head->next;
	    freeNode(&(*pL)->head);
	    (*pL)->head = temp; //sets the new current node to the next node
	}
	free(*pL); //frees the pointer
	*pL = NULL; 
    }
}


//returns the length of the list
int length(List L){
    if (L == NULL){
        fprintf(stderr, "the list does not exist\n");
	exit(-1);
    }
    return L->length;
}


//returns the first occurence of i in the linked list L
int  find( List L, int i ){
    int index = 0; //index of the element
    Node temp = L->head;
    while (temp != NULL){
	//temp = L->head->next;
	if (temp->data == i){
	    return index;
	}
	temp = temp->next; //moving on to the next node
	index += 1;
    }
    return -1; //returns -1 if i is not found
}

//deletes the ith element in the linked list
int delElement(List L, int i){

    if (L->length < i+1){ //not enough elements in the list
        fprintf(stderr, "There is not enough elements in the list\n");
        exit(-1); //exit the progam
    }
    int value = 0;
    Node ptr1 = L->head; //ptr nodes
    if (i == 0 && L != NULL){
        value = L->head->data; //stores the value of the element being deleted
        L->head = L->head->next; //moves the head to the next node
        free(ptr1);
        L->length--;
        return value;
    } else { //deleting the middle or end node
	Node temp = L->head;
	Node temp2 = L->head->next;
	int count = 1;
	while (count < i){ //iterating until the element before the element to be deleted
	    temp = temp->next;
	    temp2 = temp2->next;
	    count++;
	}
	temp->next = temp2->next; //setting temps next to temps next next
	value = temp2->data; //storing the value
	freeNode(&temp2);
	L->length--; //shortening the length
    }
    return value;
}


//returns the index of the maximum value in the linked list
int max(List L){
    if (L == NULL || L->length == 0){
        fprintf(stderr, "list DNE or is empty\n");
        exit(-1);
    }

    int maxIndex = 0; //starting at the beginning of the list
    int index2 = 0;
    int maxValue = 0; //the max value
    Node temp = L->head; //temp node to store the following node
    if (length(L) == 1){ //the head is the max
        return maxIndex;
    } else {
        while (temp != NULL){ //iterate until end of linked list
            if (maxValue < temp->data){ //if next value is greater than the current
                maxValue = temp->data; //update the maxValue
                maxIndex = index2;
            }
            temp = temp->next;
            index2 += 1;
        }
    }
    return maxIndex;
}


//appends i to the end of the link list
void appendList( List L, int i ){
    if (L == NULL){
	exit(-1);
    }
    
    Node n = newNode(i); //creating a new node to append
    if (L->length == 0){
	L->head = n;
    } else{
	Node temp = L->head; //allows us to start at the beginning of L
	while (temp->next != NULL){ //iterates through the list
	    temp = temp->next;
	}
	temp->next = n; //sets n to the last node in L
    }
    L->length++; //incrementing the size of the list by 1
}



//prints the data in the linked list
void printList(List L){
    Node temp = L->head; //allows us to start at the beginning
    while (temp != NULL){
        printf("%d, ", temp->data);
	temp = temp->next;
    }
    printf("\n");
}
