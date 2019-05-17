#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    FILE* originfile,  *copyfile;

    if(argc!=3) {
        printf("Usage: \n");
        return 1;
    }

    originfile = fopen(argv[1], "r");

    if (originfile == NULL) {
        perror("fopen!\n");
        exit(EXIT_FAILURE);
    }

    copyfile = fopen(argv[2], "w");

    if (copyfile == NULL) {
        perror("fopen\n");
        exit(EXIT_FAILURE);
    }
    
    //option1: use fputc() and fgetc()
    // char c;
    // while(1) {
    //     c = fgetc(originfile);

    //     if(feof(originfile)) {
    //         break;
    //     }

    //     fputc(c, copyfile);
    // }




    //option2: use fputs() and fgets()
    char str[80];
    while(fgets(str, 80, originfile)!=NULL) {
        fputs(str, copyfile);
    }
     
    fclose (copyfile);
    fclose ( originfile );
    return 0;




}