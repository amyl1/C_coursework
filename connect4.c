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
void insertPos(struct node** start, int pos, char data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node*));
    new_node->data = data;
    struct node *temp = *start; 
    pos--;
    while (pos>0){
      temp = temp->next;
      pos--;
    }
    temp->data=data;

}
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
void display(struct node * head,int size){
    struct node *tmp;
    if(head==NULL)
    {
      printf("Empty list");
    }
    else{
      tmp=head;
      for(int i=0;i<size;i++){
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
      int i;
      for (i=0;i<strlen(line);i++)
      {
          insertEndDouble(&head,line[i]);
      }
      struct rowStruct* newRow=(struct rowStruct*)malloc(sizeof(struct rowStruct*));
      newRow->head=head;
      currBoard->rows[j]=newRow;
      struct node *tmp=head;
      for(int j=0;j<i-1;j++){
        tmp=tmp->next;
      }
      head->prev=tmp->prev;
      tmp->next=head;
      display(head,i);
      j++;
    } 
  currBoard->size=j;
  /*
  char winner=current_winner(currBoard);
  printf("Winner: %c\n`",winner);
  
  char player=next_player(currBoard);
  printf("Next player: %c\n`",player);*/
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
  if (count_x==count_o || count_o>count_x){
    return 'x';
  }
  else{
    return 'o';
  }
  
}

char current_winner(board u){
  //check 4 in row
  for (int row=0;row<u->size;row++) {
    struct node *tmp;
    tmp=u->rows[row]->head;
    char curr;
    int count=1;
    for(int i=0;i<sizeof(u->rows[0]);i++){
        curr=tmp->data;
        //4 in row
          
          //change this for wrap around
          if(i<=sizeof(u->rows[0])-4&&curr==tmp->next->data&&curr==tmp->next->next->data && curr==tmp->next->next->next->data){
            if(curr!='.')
            return curr;
          }
          if(row <=u->size - 4){
            struct node *n1,*n2,*n3;
            n1=u->rows[row+1]->head;
            n2=u->rows[row+2]->head;
            n3=u->rows[row+3]->head;
            for (int j=0;j<i;j++){
              n1=n1->next;
              n2=n2->next;
              n3=n3->next;
            }
            //4 in a col
            if(curr==n1->data&&curr==n2->data&&curr==n3->data){
              if(curr!='.')
              return curr;
            }
            //4 diagonal to right
            if(i<=sizeof(u->rows[0])-4&&curr==n1->next->data&&curr==n2->next->next->data&&curr==n3->next->next->next->data){
              if(curr!='.')
              return curr;
            }
            //4 diagonal to left
            if(i>=3&&curr==n1->prev->data&&curr==n2->prev->prev->data&&curr==n3->prev->prev->prev->data){
              if(curr!='.')
              return curr;
            }
          }
          

            
         tmp=tmp->next;
        } 
        
    printf("\n");   
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