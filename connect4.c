//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include"connect4.h"
struct node
{
  char * data;
  struct node *next;
  struct node *prev;
};

struct board_structure {
/*Put something suitable here*/
};

void insertEnd(struct node** head,char * data) {
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

void insertPos(struct node** start, int pos, char * data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node*)); 
    new_node->data = data; // Inserting the data 
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
        printf("%s\n",current->data);
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

board setup_board(){
//You may put code here
}

void cleanup_board(board u){
//You may put code here
}

void read_in_file(FILE *infile){
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, infile)) != -1) {
    printf("%s", line);
  }
  fclose(infile);
  if (line)
    free(line);
  struct node *head = NULL;
  insertEnd(&head,line);
  display(head);
}

void write_out_file(FILE *outfile, board u){
//You may put code here
}

char next_player(board u){
//You may put code here
}

char current_winner(board u){
//You may put code here
}

struct move read_in_move(board u){
//You may put code here
  printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
//You may put code here
  printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
//You may put code here
}

int is_valid_move(struct move m, board u){
//You may put code here
}

char is_winning_move(struct move m, board u){
//You may put code here
}

void play_move(struct move m, board u){
//You may put code here
}

//You may put additional functions here if you wish.
void main(){
  FILE * infile = fopen("test_input1.txt","r");
  read_in_file(infile);

}