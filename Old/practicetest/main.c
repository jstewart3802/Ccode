#include <stdio.h>
#include <stdlib.h>

int main(){

    //1
    /*
    char name[20];
    scanf("%s", name);
    printf("%s", name);
    */

    int numbers[4], i;
    printf("input 4 numbers to find mean and standard deviation\n");
    for(i=0;i<=3;i++){
        scanf("%d", &numbers[i]);
    }
    for(i=0;i<=3;i++){
        printf("%d ", numbers[i]);
    }







    return 0;
}

