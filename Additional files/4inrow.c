  //check 4 in row
  /*
  for (int x=0;x<u->size;x++) {
    struct node *tmp;
    tmp=u->rows[x]->head;
    char curr;
    char next;
    int count=1;
    for(int i=0;i<sizeof(u->rows[0])-1;i++){
        curr=tmp->data;
        next=tmp->next->data;
        //printf("%c\n",next);
        if(curr==next&&curr!='.'){
          count++;
        }
        else{
          count=1;
        }
        if (count==4)
        {
          return curr;
        }
        tmp=tmp->next;
    }
  }

  for(int i=0;i<sizeof(u->rows[0]);i++){
    printf("%d",i);
    int count=1;
    char currData;
    char nextData;
    //fix this
    int j=i;
    for (int x=0;x<u->size-1;x++) {
      struct node *curr=u->rows[x]->head; 
      struct node *next=u->rows[x+1]->head; 
      j++;
      printf("%d",j);
      while (j>0){
        j--;
        curr=curr->next;
        next=next->next;
        
      }
      currData=curr->data;
      nextData=next->data;
      printf("%c",currData);
      if(currData==nextData&&currData!='.'){
          count++;
        }
        else{
          count=1;
        }
        if (count==4)
        {
          return currData;
        }
    }
    printf("\n");
    
  }
  return 'n';
  */