#include <stdio.h>
#define MAX_LEN 128
 
void printgmbr(FILE *fptr);
 
void printufo()
{
    char *filename = "ufoinvasion.txt"; //Art by Marcin Glinski
    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
 
    printgmbr(fptr);
 
    fclose(fptr);
 
    
}
 
void printufoPeace()
{
    char *filename = "peace.txt"; //Art by Marcin Glinski
    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
 
    printgmbr(fptr);
 
    fclose(fptr);
 
    
}
 
void printgmbr(FILE *fptr)
{
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}
