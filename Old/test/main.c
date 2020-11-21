#include <stdio.h>

void print_array(int size, int array[ ]);

int main(){

   int array[ ]={0,1,2,3,4,5};

   int size = (int) sizeof(array) / (int) sizeof(int);

   print_array(size, array);

   return 0;

}

void print_array(int size, int array[ ]){

   for (int i=0 ; i < size ; ++i){
      array[i] = 10.0;
      printf("array[%d] = %d\n", i, array[i]);
   }

}
