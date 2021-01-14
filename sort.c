
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[]){
    char *str = argv[1];
    int i=0;
    int j=0;
    FILE *fp;
    if (argc > 2) {
        fp = fopen(argv[2], "r");
        if (fp == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[2]);
            return 1;
        }
        else{
            printf("file opened");
        }
    } else {
        fp = stdin; /* read from standard input if no argument on the command line */
        printf("reading from command line");
    }
   for(i=0; str[i]!='\0'; ++i)
    {
        while (!((str[i]>='a'&&str[i]<='z') || (str[i]>='A'&&str[i]<='Z' || str[i]=='\0')))
        {
            for(j=i;str[j]!='\0';++j)
            {
                str[j]=str[j+1];
            }
            str[j]='\0';
        }
    }
    char option = str[0];
   switch (option) { 
    case 'o' : 
        printf("o"); 
        break; 
    case 'n' : 
        printf("n"); 
        break; 
    case 'r' : 
        printf("r"); 
        break;
    case 'h' : 
        printf("h"); 
        break;
    default: printf("Other.\n"); 
    }

    return 0;
}