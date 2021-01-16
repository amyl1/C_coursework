#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareFunc(const void *p1, const void *p2) {
    return strcmp(p1, p2);
}
int main(int argc, char* argv[])
{
    char *fileExt=".txt";
    char *f_pres;
    FILE *fptr = stdin; 
    size_t opt;
    int leng = 0;
    char s[255][255];
    int n = 0;
    for (int i=1; i<argc; i++) {
        f_pres=strstr(argv[i],fileExt);
        if (f_pres){
           fptr = fopen(argv[i], "r");
           if (fptr == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[2]);
            return 1;
            }
        }        
    }
    
    while (n < 255 && fscanf(fptr, "%254s", s[n]) == 1) {
        n++;
    }
    fclose(fptr);

    qsort(s, n, sizeof(*s), compareFunc);

    for (int i = 0; i < n; i++) {
        printf("%s ", s[i]);
    }
    printf("\n");
    
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
    printf("\n");
    return 0;
}