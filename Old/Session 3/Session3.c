#include <stdio.h>
#include <math.h>
float vol_sph(float r);
int main(){
    printf("\n Menu\n"
           "\t 1. Calculate volume of a sphere\n"
           "\t 2. Calculate the volume of a cylinder\n"
           "\t 3. Calculate volume of a pyramid\n"
           "\t 0. Quit\n");
    int option;
    float r;
    scanf("%d", &option);
    switch (option){
    case 0:
        printf("Goodbye\n");
        return 0;

    case 1:
        printf("Input  radius of sphere");
        scanf("%g",&r);
        vol_sph(r);
        printf("%g\n",vol_sph);
    }
}
float vol_sph(float r){
    return 4/3*M_PI*pow(r,3);
}
