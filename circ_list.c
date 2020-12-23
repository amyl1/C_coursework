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

void insertEnd(struct node** header,int data) {
    struct node* newnode=(struct node*)malloc(sizeof(struct node*));
    newnode->data=data;
    newnode->prev=NULL;
    newnode->next=NULL;

    if(*header == NULL) {
        *header=newnode;
        return;
    }

    struct node* temp = *header;

    while(temp->next != NULL) {
        temp=temp->next;
    }
    temp->next = newnode;
    newnode->prev = temp;
}
void display(struct node *current){
    while(current!=NULL){
        printf("%d\n",current->data);
        current=current->next;
    }
}

void free_list(struct node *current){
  if (current!=NULL) {
    free_list(current->next);
    free(current);
  }
}

int main(){
    struct node *head = NULL;
    insertEnd(&head,4);
    insertEnd(&head,8);
    insertEnd(&head,5);
    display(head);
    return 0;
}