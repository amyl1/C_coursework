//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"connect4.h"

struct board_structure {
  struct node *array[512];
  int rowSize;
  int size;
  char currPlayer;
};

struct node{
  char data;
  struct node *next;
  struct node *prev;
};
void exit(int status);
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

board setup_board(){
  struct board_structure*newBoard=malloc(sizeof(struct board_structure*));
  if(newBoard==NULL){
    fprintf(stderr, "Malloc failed\n");
    exit(1);
  }
  newBoard->rowSize=0;
  struct node* array=malloc(512*sizeof(struct node));
  if(array==NULL){
    fprintf(stderr, "Malloc failed\n");
    exit(1);
  }
  return newBoard;
}
void cleanup_board(board u){
  for(int i=0; i<u->rowSize;i++){
    free(u->array[i]);
  }
}
int drop_down(struct move m, board u){
  int i;
  struct node *tmp = (struct node *)malloc(sizeof(struct node));
  for (i=0;i<u->size;i++){
    tmp=u->array[i];
    //tmp=head;
    for(int j=1;j<m.column;j++){
      tmp=tmp->next;
    }
    if (tmp->data!='.')
      break;
  }
  return i;
  free(tmp);
}

void rotate(board u, int r, struct move m){
  if(m.row<0){
      u->array[abs(r)-1]=u->array[abs(r)-1]->next;
  }
  else{
      u->array[abs(r)-1]=u->array[abs(r)-1]->prev;
  }
}
void swap (int *pa, int *pb){
  int temp=*pa;
  *pa=*pb;
  *pb=temp;
}
void drop_all(board u){
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    int positions[u->rowSize-1][u->size+1];
    for(int i=0; i<=u->size; i++){
      tmp=u->array[i];
      int j;
      for(j=0; j<=u->rowSize-2;j++){
        if(tmp->data=='o'||tmp->data=='O'){
          positions[j][i]=1;
        }
        else if(tmp->data=='x'||tmp->data=='X'){
          positions[j][i]=2;
        }
        else{
          
          positions[j][i]=0;
        }
        tmp=tmp->next;
      }
      if(tmp->data=='o'||tmp->data=='O'){
        positions[j+1][i]=1;
      }
      else if(tmp->data=='x'||tmp->data=='X'){
          positions[j+1][i]=2;
        }
      else{
          
          positions[j+1][i]=0;
        }
  }
  for(int y=0;y<u->rowSize;y++){
    for(int x=u->size;x>=0;x--){
        if(positions[y][x]!=0){
          continue;
        }
       else{
         int j=0;
         while(positions[y][x-j]==0&&x-j>0){
           j++;
         }
         swap(&positions[y][x],&positions[y][x-j]);
       }
    }
  }
  for(int x=0;x<=u->size;x++){
    tmp=u->array[x];
    for(int y=0;y<u->rowSize-1;y++){
      
      if(positions[y][x]==0)
      {
        tmp->data='.';
      }
      else if(positions[y][x]==1){
        tmp->data='o';
      }
      else
      {
        tmp->data='x';
      }
      tmp=tmp->next;
    }
  }
}
void play_move(struct move m, board u){
  int r=u->size+1;
  int absRow=abs(m.row);
  for (int i=1;i<absRow;i++){
    r--;
  }
  int row = drop_down(m,u);
  insertPos(&u->array[row-1],m.column,next_player(u));
  if(m.row!=0)
    rotate(u,r,m);
  drop_all(u);
  }

void read_in_file(FILE *infile, board u){
  if(infile == NULL)
   {
      fprintf(stderr, "Couldn't find input file\n");
      exit(1);            
   }
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
      if(j!=u->rowSize && u->rowSize!=0){
        fprintf(stderr, "Row sizes not consistent\n");
        exit(1);
      }
      if(j<4 && j>512){
        fprintf(stderr, "Board size out of bounds\n");
        exit(1);
      }
      u->rowSize=j;
      j=0;
    }
    else{
      if(c=='o'||c=='O'||c=='x'||c=='X'||c=='.'||c=='\n'){
        insertEnd(&head,c);
        j++;
      }
      else{
        fprintf(stderr, "Invalid character in file\n");
        exit(1);
      }
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
  current_winner(u);
  if(outfile == NULL)
   {
      fprintf(stderr, "Couldn't find output file\n");
      exit(1);            
   }
  struct node *tmp = (struct node *)malloc(sizeof(struct node));
  for(int j=0;j<=u->size;j++){
      
      tmp=u->array[j];
      for(int i=0;i<u->rowSize-2;i++){        
        fprintf(outfile,"%c",tmp->data);
        tmp=tmp->next;
      }
      
    fprintf(outfile,"%c",tmp->data);
    fprintf(outfile,"\n");
    
  }
}

char next_player(board u){
  int count_x=0;
  int count_o=0;
  for (int x=0;x<=u->size;x++) {
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp=u->array[x];    
    for (int i=0;i<u->rowSize-1;i++){      
        if(tmp->data=='x'||tmp->data=='X')
        {
          count_x++;
        }
        else if (tmp->data=='o'||tmp->data=='O'){
          count_o++;
        }
        tmp=tmp->next;
    }
  }
  if (count_x==count_o || count_o>count_x){
    u->currPlayer='x';
    return 'x';
  }
  else{
    u->currPlayer='o';
    return 'o';
  }
}

char current_winner(board u){
  char winners[2]="..";
  for (int row=0;row<=u->size;row++) {    
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp=u->array[row];
    char curr;
    for(int i=0;i<u->rowSize-1;i++){
      curr=tmp->data;
      if(tolower(curr)==tolower(tmp->next->data)&&tolower(curr)==tolower(tmp->next->next->data) && tolower(curr)==tolower(tmp->next->next->next->data)){
        if(curr=='x'||curr=='X'){
          winners[0]='x';
          tmp->data='X';
          tmp->next->data='X';
          tmp->next->next->data='X';
          tmp->next->next->next->data='X';
        }
        else if(curr=='o'||curr=='O'){
          winners[1]='o';
          tmp->data='O';
          tmp->next->data='O';
          tmp->next->next->data='O';
          tmp->next->next->next->data='O';
        }
        }
        if(row <=u->size - 3){
          //printf("check %d,%d,%d,%d",row,row+1,row+2,row+3);
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
          if(tolower(curr)==tolower(n1->data)&&tolower(curr)==tolower(n2->data)&&tolower(curr)==tolower(n3->data)){       
            if(curr=='x'||curr=='X'){
              winners[0]='x';
              tmp->data='X';
              n1->data='X';
              n2->data='X';
              n3->data='X';
            }
            else if(curr=='o'||curr=='O'){
              winners[1]='o';
              tmp->data='O';
              n1->data='O';
              n2->data='O';
              n3->data='O';
            }
          }
          //4 diagonal to right
          if(tolower(curr)==tolower(n1->next->data)&&tolower(curr)==tolower(n2->next->next->data)&&tolower(curr)==tolower(n3->next->next->next->data)){
            if(curr=='x'||curr=='X'){
              winners[0]='x';
              tmp->data='X';
              n1->next->data='X';
              n2->next->next->data='X';
              n3->next->next->next->data='X';
            }
            else if(curr=='o'||curr=='O'){
              winners[1]='o';
              tmp->data='O';
              n1->next->data='O';
              n2->next->next->data='O';
              n3->next->next->next->data='O';
            }
          }
          //4 diagonal to left
          if(tolower(curr)==tolower(n1->prev->data)&&tolower(curr)==tolower(n2->prev->prev->data)&&tolower(curr)==tolower(n3->prev->prev->prev->data)){
            if(curr=='x'||curr=='X'){
            winners[0]='x';
            tmp->data='O';
            n1->prev->data='O';
            n2->prev->prev->data='O';
            n3->prev->prev->prev->data='O';  
            }
              
            else if(curr=='o'||curr=='O'){
              winners[1]='o';
              tmp->data='O';
              n1->prev->data='O';
              n2->prev->prev->data='O';
              n3->prev->prev->prev->data='O';
            }
          }           
        }
        tmp=tmp->next;
    }      
  }
  if(winners[0]=='x'&&winners[1]=='o'){
    return 'd';
  }    
  else if(winners[1]=='o'){
    return 'o';
  }    
  else if(winners[0]=='x'){
    return 'x';
  }
  else
  {
    return'.';
  }
}

struct move read_in_move(board u){
  struct move newMove;
  int col;
  int Count;
  printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
  while ((Count = scanf("%d",&col)) != 1) {
  if (Count < 0) {
    exit(1);
  }
  scanf("%*c");
  printf("Input not valid. Please enter an integer.\n");
}
  newMove.column=col;
  int row;
  printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
  Count=0;
  while ((Count = scanf("%d",&row)) != 1) {
  if (Count < 0) { 
    exit(1); // No more input possible
  }
  scanf("%*c");
  printf("Input not valid. Please enter an integer.\n");
}
  //scanf("%d",&row);
  newMove.row=row;
  return newMove;
}

int is_valid_move(struct move m, board u){
  if(m.column>=u->rowSize){
    printf("not in range");
    return 0;
  }
  if(m.row>u->size+1){
    printf("not in range");
    return 0;
  }
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
  free(tmp);
  free(head);
}

char is_winning_move(struct move m, board u){
    char winner;
    int absRow=abs(m.row);
    int r=u->size+1;
    for (int i=1;i<absRow;i++){
      r--;
    }
    board v=setup_board();    
    v->size=u->size;
    v->rowSize=u->rowSize;
    v->currPlayer=u->currPlayer;
    for(int j=0;j<=u->size;j++){
      v->array[j]=NULL;
      struct node *tmp = (struct node *)malloc(sizeof(struct node));
      tmp=u->array[j];
      for(int k=0;k<u->rowSize-2;k++){        
        insertEnd(&v->array[j],tmp->data);
        tmp=tmp->next;
      }
      insertEnd(&v->array[j],tmp->data);
      struct node *tmpv = (struct node *)malloc(sizeof(struct node));
      tmpv=v->array[j];
      for(int x=0;x<v->rowSize-2;x++){
        tmpv=tmpv->next;
      }
      v->array[j]->prev=tmpv;
      tmpv->next=v->array[j];
      free(tmp);
      free(tmpv);
    }
      play_move(m,v);
      winner=current_winner(v);
      cleanup_board(v);
    return winner;
}
