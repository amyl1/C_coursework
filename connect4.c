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
  char data;
  struct node *next;
  struct node *prev;
};
struct rowStruct
{
  struct node *head;
};

struct board_structure {
  struct rowStruct *rows[512];
  int size;
};

void insertEndDouble(struct node** header,char data) {
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

board setup_board(){
  struct board_structure*newBoard=(struct board_structure*)malloc(sizeof(struct board_structure*));
  return newBoard;
}

void cleanup_board(board u){
//You may put code here
}
void display(struct node * head){
    struct node *tmp;
    if(head==NULL)
    {
      printf("Empty list");
    }
    else{
      tmp=head;
      while (tmp!=NULL){
        printf("%c",tmp->data);
        tmp=tmp->next;
      }
    }
}

void read_in_file(FILE *infile){
  char line[100];
  int j=0;
  struct board_structure *currBoard=setup_board();
  while ( fgets( line, 100, infile ) != NULL ) 
    { 
      struct node *head = NULL;
      for (int i=0;i<strlen(line);i++)
      {
          insertEndDouble(&head,line[i]);
      }
      struct rowStruct* newRow=(struct rowStruct*)malloc(sizeof(struct rowStruct*));
      newRow->head=head;
      currBoard->rows[j]=newRow;
      j++;
    } 
  currBoard->size=j;
  char winner=current_winner(currBoard);
  printf("%c\n",winner);
}

void write_out_file(FILE *outfile, board u){
//You may put code here
}

char next_player(board u){
  int count_x=0;
  int count_o=0;
  for (int x=0;x<u->size;x++) {
    struct node *tmp;
    tmp=u->rows[x]->head;
    while (tmp!=NULL){
        if(tmp->data=='x')
        {
          count_x++;
        }
        else if (tmp->data=='o'){
          count_o++;
        }
        tmp=tmp->next;
    }
  }
  if (count_x==count_o){
    return 'x';
  }
  else{
    return 'o';
  }
  
}

char current_winner(board u){
  for (int x=0;x<u->size;x++) {
    struct node *tmp;
    tmp=u->rows[x]->head;
    char curr;
    char next;
    int count=0;
    for(int i=0;i<sizeof(u->rows[0])-1;i++){
        curr=tmp->data;
        next=tmp->next->data;
        //printf("%c\n",next);
        if(curr==next&&curr!='.'){
          count++;
        }
        else{
          count=0;
        }
        if (count==4)
        {
          return curr;
        }
        tmp=tmp->next;
    }
  }
  return 'n';
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
  FILE * infile = fopen("test_input2.txt","r");
  read_in_file(infile);
}