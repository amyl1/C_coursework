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

void insertEnd(struct node** head, char data) {
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

void insertPos(struct node** start, int pos, char value)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node*)); 
    new_node->data = value;
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
        printf("data: %c\n",current->data);
        current=current->next;
    }
}

int main(){
    struct node *head = NULL;
    insertEnd(&head,'f');
    insertEnd(&head,'x');
    insertPos(&head,1,'9');
    insertEnd(&head,'o');
    display(head);
    return 0;
}