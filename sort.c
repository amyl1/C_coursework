#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 200 
#define NUM 50 
int main(int argc, char* argv[])
{
 char line[NUM][SIZE];
	char fname[20];
    char *fileExt=".txt";
    char *f_pres;
    FILE *fptr = stdin; 
    size_t opt;
    int i = 0;
    int leng = 0;
    //extracts 'options'
    for (i=1; i<argc; i++) {
        f_pres=strstr(argv[i],fileExt);
        if (f_pres){
           fptr = fopen(argv[i], "r");
           if (fptr == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[2]);
            return 1;
            }
        }        
    }
    for (opt = 1; opt < argc && argv[opt][0] == '-'; opt++) {
        switch (argv[opt][1]) { 
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
    }  
    while(fgets(line[i], SIZE, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    leng = i; 
    for(i = 0; i < leng; ++i)
    {
        printf(" %s\n", line[i]);
    }
    printf("\n");
    return 0;
}