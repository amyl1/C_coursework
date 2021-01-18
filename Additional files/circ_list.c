#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
  int data;
  struct node *next;
  struct node *prev;
};

void insertEnd(struct node** head,int data) {
    struct node* newnode=(struct node*)malloc(sizeof(struct node*));
    newnode->data=data;
    newnode->prev=NULL;
    newnode->next=NULL;
    if(*head == NULL) {
        *head=newnode;
        return;
    }

    struct node* temp = *head;

    while(temp->next != NULL) {
        temp=temp->next;
    }
    temp->next = newnode;
    newnode->prev = temp;
}

// The new node is inserted after the node with // with value2 
void insertAfter(struct node** start, int value1, int value2) 
{ 
    struct node* new_node = (struct node*)malloc(sizeof(struct node*)); 
    new_node->data = value1; // Inserting the data 
    // Find node having value2 and next node of it 
    struct node *temp = *start; 
    while (temp->data != value2) 
        temp = temp->next; 
    struct node *next = temp->next; 
    
    // insert new_node between temp and next. 
    temp->next = new_node; 
    new_node->prev = temp; 
    new_node->next = next; 
    next->prev = new_node; 
    
}
void insertPos(struct node** start, int pos, int value)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node*)); 
    new_node->data = value; // Inserting the data 
    // Find node having value2 and next node of it 
    struct node *temp = *start; 
    pos--;
    while (pos>0){
      temp = temp->next;
      pos--;
    }
    struct node *next = temp->next; 
    temp->next = new_node; 
    new_node->prev = temp; 
    new_node->next = next; 
    next->prev = new_node; 
}

void display(struct node *current){
    while(current!=NULL){
        printf("data: %d\n",current->data);
        current=current->next;
    }
}

void free_list(struct node *current){
  if (current!=NULL) {
    free_list(current->next);
    free(current);
    display(current);
  }
}

int main(){
    struct node *head = NULL;
    insertEnd(&head,4);
    insertEnd(&head,8);
    insertPos(&head,1,9);
    insertEnd(&head,5);
    display(head);
    free_list(head);
    return 0;
}