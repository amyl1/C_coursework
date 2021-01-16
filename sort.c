#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int compareFunc(const void *p1, const void *p2) {
    return strcmp(p1, p2);
}
void displayHelp(){
    printf("For this part of the coursework, there is the option to read in the content to be sorted from a file or command line \n");
    printf("Input is read until EOF is reached. \n");
    printf("-o was implemented to put the output into a file specified in a command line argument. \n");
    printf("If only one file is specified when using the -o option, the input is read from the command line. \n");
    printf("if two file arguments are provided when using the -o, the first is the output\n");
    printf("The second file then provides in the input.\n");
    printf("-n sorts numerically.\n");
    printf("-r reverses the sorted string.\n");
    printf("-h provides this explaination. \n");
    printf("robustness:\n");


}
int main(int argc, char* argv[])
{
    char *fileExt=".txt";
    char *f_pres;
    FILE *fptr = stdin; 
    FILE *outptr = stdout; 
    size_t opt;
    int leng = 0;
    char s[255][255];
    int n = 0;
    bool rev=false;
    bool out=false;
    for (opt = 1; opt < argc && argv[opt][0] == '-'; opt++) {
        switch (argv[opt][1]) { 
        case 'o' : 
            out=true;
            break; 
        case 'n' : 
            printf("n"); 
            break; 
        case 'r' : 
            rev=true;
            printf("r"); 
            break;
        case 'h' : 
            displayHelp();
            return 1;
            break;
        default: printf("Other.\n"); 
        }
    }
    for (int i=1; i<argc; i++) {
        f_pres=strstr(argv[i],fileExt);
        if (f_pres&&out==false){
           fptr = fopen(argv[i], "r");
           if (fptr == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[2]);
            return 1;
            }
            break;
        }
        else if(f_pres&&out==true){
            int filecount=0;
            for (int i=1; i<argc; i++) {
                f_pres=strstr(argv[i],fileExt);
                if(f_pres){
                    filecount++;
                }
                if(filecount==1){
                    printf("outfile %s",argv[i]);
                    outptr = fopen(argv[i], "w");
                    if (outptr == NULL) {
                        fprintf(stderr, "cannot open %s\n", argv[i]);
                        return 1;
                    }
                }
                else if (filecount==2){
                    printf("infile %s",argv[i]);
                    fptr = fopen(argv[i], "r"); 
                    if (fptr == NULL) {
                        fprintf(stderr, "cannot open %s\n", argv[i]);
                        return 1;
                    }
                }
        }        
    }
    }
    while (n < 255 && fscanf(fptr, "%254s", s[n]) == 1) {
        n++;
    }
    fclose(fptr);
    qsort(s, n, sizeof(*s), compareFunc);
    printf("\n");
    if(rev==false){
        for (int i = 0; i < n; i++) {
            fprintf(outptr,"%s\n",s[i]);
        }
    }
    else{
        for(int i=n-1;i>0;i--){
            fprintf(outptr,"%s\n",s[i]);
            
        }
    }
    fclose(outptr);
    return 0;
}