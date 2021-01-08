//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"connect4.h"

struct board_structure {
  struct node *array[512];
  int rowSize;
  int size;
};

struct node{
  char data;
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
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp = *start; 
    pos--;
    while (pos>0){
      temp = temp->next;
      pos--;
    }
   temp->data=value;
}

void display(struct node *current,int size){
    for(int i=0;i<size-1;i++){
        printf("%c",current->data);
        current=current->next;
    }
}
board setup_board(){
  struct board_structure*newBoard=malloc(sizeof(struct board_structure*));
  newBoard->array==malloc(512*sizeof(struct node));
  return newBoard;
}
void cleanup_board(board u){
//You may put code here
}
int drop_down(struct move m, board u){
  int i;
  for (i=0;i<u->size;i++){
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head=u->array[i];
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp=head;
    for(int j=1;j<m.column;j++){
      tmp=tmp->next;
    }
    if (tmp->data!='.')
      break;
  }
  return i;
}

void rotate(board u, int r, struct move m){
  if(m.row<0){
      u->array[abs(r)-1]=u->array[abs(r)-1]->next;
      printf("hello");
  }
  else{
      u->array[abs(r)-1]=u->array[abs(r)-1]->prev;
  }
}

void drop_all(board u){
  
}
void play_move(struct move m, board u){
  int r=u->size+1;
  int absRow=abs(m.row);
  for (int i=1;i<absRow;i++){
    r--;
  }
  int row = drop_down(m,u);
  int x=0;
  insertPos(&u->array[row-1],m.column,'a');
  if(m.row!=0)
    rotate(u,r,m);
  //drop_all(u);
  }

void read_in_file(FILE *infile, board u){
  struct node *head = (struct node *)malloc(sizeof(struct node));
  head =NULL;
  int c=0;
  int i=0;
  int j=0;
  c = fgetc(infile);
  while(c != EOF){
    if(c=='\n'){
      u->array[i]=head;
      i++;
      j++;
      struct node *tmp = (struct node *)malloc(sizeof(struct node));
      tmp=head;
      for(int x=0;x<j-2;x++){
        tmp=tmp->next;
      }
      head->prev=tmp;
      tmp->next=head;
      head =NULL;
      u->rowSize=j;
      j=0;
    }
    else{
      insertEnd(&head,c);
      j++;
    }
    c=fgetc(infile);
   }
  
  u->array[i]=head;
  struct node *tmp = (struct node *)malloc(sizeof(struct node));
  tmp=head;
  for(int x=0;x<u->rowSize-2;x++){
    tmp=tmp->next;
  }
  head->prev=tmp;
  tmp->next=head;
  u->size=i;
  }

void write_out_file(FILE *outfile, board u){
//You may put code here
}

char next_player(board u){
  int count_x=0;
  int count_o=0;
  for (int x=0;x<=u->size;x++) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp=u->array[x];    
    for (int i=0;i<u->rowSize-1;i++){      
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
  if (count_x==count_o || count_o>count_x){
    return 'x';
  }
}
char current_winner(board u){
  char winners[2]="..";
  for (int row=0;row<u->size+1;row++) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp=u->array[row];
    char curr;
    int count=1;
    for(int i=0;i<u->rowSize-1;i++){
      curr=tmp->data;
      if(curr==tmp->next->data&&curr==tmp->next->next->data && curr==tmp->next->next->next->data){
        if(curr=='x')
          winners[0]='x';
        else if(curr=='o')
          winners[1]='o';
        }
        if(row <u->size - 4){
          struct node *n1,*n2,*n3 = (struct node *)malloc(sizeof(struct node));
          n1=u->array[row+1];
          n2=u->array[row+2];
          n3=u->array[row+3];
          for (int j=0;j<i;j++){
            n1=n1->next;
            n2=n2->next;
            n3=n3->next;
          }
          //4 in a col
          if(curr==n1->data&&curr==n2->data&&curr==n3->data){           
            if(curr=='x')
              winners[0]='x';
            else if(curr=='o')
              winners[1]='o';
          }
          //4 diagonal to right
          if(curr==n1->next->data&&curr==n2->next->next->data&&curr==n3->next->next->next->data){
            if(curr=='x')
              winners[0]='x';
            else if(curr=='o')
              winners[1]='o';
          }
          //4 diagonal to left
          if(curr==n1->prev->data&&curr==n2->prev->prev->data&&curr==n3->prev->prev->prev->data){
            if(curr=='x')
              winners[0]='x';
            else if(curr=='o')
              winners[1]='o';
          }
        }
         tmp=tmp->next;
    }  
  }
  if(winners[0]=='x'&&winners[1]=='o'){
    return 'd';
  }    
  else if(winners[0]=='.'&&winners[1]=='.'){
    return '.';
  }    
  else if(winners[0]=='x'&&winners[1]=='.'){
    return 'x';
  }
  else
  {
    return'o';
  }
}

struct move read_in_move(board u){
  struct move newMove;
  printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
  int col;
  scanf("%d",&col);
  newMove.column=col;
  printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
  int row;
  scanf("%d",&row);
  newMove.row=row;
  return newMove;
}

int is_valid_move(struct move m, board u){
  //check if col in bound
  if(m.column>=u->rowSize){
    return 0;
  }
  //check if row in bound
  if(m.row>u->size+1){
    return 0;
  }
  //check if column is full
  struct node *head = (struct node *)malloc(sizeof(struct node));
  head=u->array[0];
  struct node *tmp = (struct node *)malloc(sizeof(struct node));
  tmp=head;
  for(int j=1;j<m.column;j++){
      tmp=tmp->next;
    }
  if (tmp->data!='.')
    return 0;
  return 1; 
}

char is_winning_move(struct move m, board u){
  return 'x';
}

int main(){
  FILE *infile;
  board my_board=setup_board();
  infile=fopen("test_input1.txt","r");
  read_in_file(infile,my_board);
  fclose(infile);

  struct move my_move=read_in_move(my_board);
  //int x=drop_down(my_move,my_board);
  //int x=is_valid_move(my_move,my_board);

  for (int i=0;i<=my_board->size;i++){
    struct node *head;
    display(my_board->array[i],my_board->rowSize);
    printf("\n");
  }
  play_move(my_move,my_board);
  
  for (int i=0;i<=my_board->size;i++){
    struct node *head;
    display(my_board->array[i],my_board->rowSize);
    printf("\n");
  }
  return 0;
}