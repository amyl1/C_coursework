#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


int compareFunc(const void *p1, const void *p2) {
    return strcmp(p1, p2);
}

int strcmpbynum(const char s1, const char s2) {
    if( s1 >= '0' && s1 <= '9'&& s2 >= '0' && s2 <= '9'){
        if(s1>s2){
        return 1;
        }
        else{
            return -1;
        }
    } 
    else{
        return (int)s1 - (int)s2;    
    }
}
static int compareNum(const void *p1, const void *p2) {
  char ps1 = atoi(p1);
  char ps2 = atoi(p2);
  return strcmpbynum(ps1,ps2);
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
    printf("Robustness is provided by checking that the input and output files exist.\n");
    printf("There is also other error checking.\n");

}
int main(int argc, char* argv[])
{
    char *fileExt=".txt";
    char *f_pres;
    FILE *fptr = stdin; 
    FILE *outptr = stdout; 
    int opt;
    char s[255][255];
    int n = 0;
    bool rev=false;
    bool out=false;
    bool num=false;
    for (opt = 1; opt < argc && argv[opt][0] == '-'; opt++) {
        switch (argv[opt][1]) { 
        case 'o' : 
            out=true;
            break; 
        case 'n' : 
            num=true; 
            break; 
        case 'r' : 
            rev=true;
            break;
        case 'h' : 
            displayHelp();
            return 0;
            break;
        default: printf("-%c Option not recognised.\n",argv[opt][1]); 
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
                    outptr = fopen(argv[i], "w");
                    if (outptr == NULL) {
                        fprintf(stderr, "cannot open %s\n", argv[i]);
                        return 1;
                    }
                }
                else if (filecount==2){
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
    if (num){
        qsort(s, n, sizeof(*s), compareNum);
    }
    else{
       qsort(s, n, sizeof(*s), compareFunc);
    }
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
