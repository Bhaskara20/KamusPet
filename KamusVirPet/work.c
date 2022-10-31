#include <stdio.h>
#define MAX_LEN 128
 
void printimage(FILE *fptr);
 
void printwork()
{
    char *filename = "work.txt"; //Art by Marcin Glinski
    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
 
    printimage(fptr);
 
    fclose(fptr);
 
    
}
 
void printimage(FILE *fptr)
{
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}
