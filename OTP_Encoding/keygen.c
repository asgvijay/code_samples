// keygen.c
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
char convertToChar(int randNum);
#define DEBUG 0

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int i;
    
    if(argc<=1)
    {
        printf("Keygen: Bad Input");
        return(1);

    }

    else
    {

        if(atoi(argv[1]))
        {
             for(i=0; i< atoi(argv[1]); i++)  
                 printf("%c", convertToChar(rand()%27));
            
        }
       printf("\n");
    }

return (0);

}
       
char convertToChar(int randNum)
{
    
    if(randNum==0)
        return 32;
    else
        return (randNum + 64);
    
}