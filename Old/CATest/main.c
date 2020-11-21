/*
 *CATest for PHY2027
 *Date: 01-11-2018
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solve();
void swap(int iarray1[], int iarray2[], int size);

int main(){

    //Question1

    char word[11];
    printf("Please type the sentence Tihuaenukas\n");
    scanf("%s",word);
    for(int i=0;i<11;i=i+2){
        printf("%c", word[i]);
    }



    //Question 2

    int x=0, y=0, z=0, w=0;
    printf("\n\nplease type 3 positive integers\n");
    scanf("%d %d %d", &x, &y, &z);

    //check to make sure users enter positive integers
    while(x<0||y<0||z<0){
        printf("Please enter positive integers\n");
        scanf("%d %d %d", &x, &y, &z);
    }

    if(x>=y&&x>=z){
        w=z;
    }else
    if(y>=x&&y>=z){
        w=y;
    }else
    if(z>=x&&z>=y){
        w=z;
    }
    printf("biggest number=%d\n",w);




    //Question3

    solve();




    //Question4

    int iarray1[ ]={1,2,3,4}, iarray2[ ]={4,5,6,7};
    int size = (int) sizeof(iarray1) / (int) sizeof(int);
    //calculates size of arrays for use in function
    swap(iarray1, iarray2, size);



    return 0;
}


//solves the equation and prints the 2 possible answers after displaying the original equation
void solve(){
    float a=1.0, b=4.0, c=1.0, x1=0, x2=0;
    x1=(-b+sqrt(pow(b,2)-4*a*c))/(2*a);
    x2=(-b-sqrt(pow(b,2)-4*a*c))/(2*a);
    printf("\nfor %gx^2+%gx+%g=0\n",a,b,c);
    printf("x = %f or %f\n",x1, x2);
}


//swaps the values of two arrays and prints the results
void swap(int iarray1[], int iarray2[], int size){
int temp=0;
for(int i=0;i<size;i++){
    temp=iarray1[i];
    iarray1[i]=iarray2[i];
    iarray2[i]=temp;
}
printf("\nSwapped arrays are;\n");
printf("iarray1=");
for(int i=0;i<size;i++){
    printf("%d",iarray1[i]);
}
printf("\niarray2=");
for(int i=0;i<size;i++){
    printf("%d",iarray2[i]);
}
}

/*  Results

Please type the sentence Tihuaenukas
Tihuaenukas
Thanks

please type 3 positive integers
56 34 79
biggest number=79

for 1x^2+4x+1=0
x = -0.267949 or -3.732051

Swapped arrays are;
iarray1=4567
iarray2=1234
Process returned 0 (0x0)   execution time : 10.299 s
Press any key to continue.






*/
