/*
	Title:   Matrix calculator
	Author:  James A. Stewart
	Address: Dept of Physics, University of Exeter, UK
	Licence: Public Domain
*/
static const char * VERSION  = "1.0.0";
static const char * REV_DATE = "05-Nov-20120";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Code takes input from random matrix generator and performs matrix calculations
on the read in matices depending on the users command line arguments.

Invoke in the form;
./mat_test -x filename.txt filename2.txt

where x is the letter corresponding to the calculation to be carried out,
and where fileanme2.txt is only needed in the case of multiplication.
-f = frobenius norm
-t = transpose
-m = multiplication
-d = determinant
-a = adjoint
-i = inverse
*/

int get_size(char *filename, int *size);
void get_matrix(char *filename, int *size, long double *matrix);
long double frobenius(long double *matrix1, int *size);
void transpose(long double *matrix1, long double *tranmatrix, int *size);
void multiply(long double *matrix1, long double *matrix2, long double *multiplied, int *size1, int *size2);
long double determinant(long double *matrix, unsigned int rank);
void adjoint(long double *matrix, long double *adjoint_mat, unsigned int rank);
void inverse(long double *matrix, long double *inverse_mat, unsigned int rank);
void print_file(long double *matrix, int *size, char *output_file, int argc, char **argv);

/*
Main function gets the arguments from command line and calls the appropriate
functions to carry out the matrix calculations required.
It then calls a function with the appropriate arguments to print the results
to a file, when a matrix is produced.
*/
int main(int argc,char *argv[]){
	int size1[2] = {0,0};/*size of matrix1 rows x cols*/
	char *output_file = {"output.txt"};/*name the output file here*/

	if(argc < 3 || argc >4){
		printf("please enter valid number of arguments\n");
		return 0;
	}

	char* filename1 = argv[2]; /*retrieve filename from command line arguments*/

	get_size(filename1, size1);

	/*Limited to 12 but could be edited easily enough to add more, but rank 12
	already takes a long time, so more could take a very long time*/
	if(size1[0] > 12 || size1[1] > 12){
		printf("Please make matrix only up to 12 rows/columns");
		return 0;
	}
	/*
	create array to store amtrix from file in of appropriatesize=
	access with elementij = matrix1[cols*i+j];
	*/
	long double *matrix1 = malloc(size1[0]*size1[1]*sizeof(long double));

	get_matrix(filename1, size1, matrix1);

	/*check that only used two file names when multiplying*/
	if(argc == 4){
		if(strcmp(argv[1], "-m") != 0){
			printf("Please input function to be used and then filename 1 and filename 2 only if using multiplication.\n");
			return 0;
		}
	}

	/*If frobenius norm chosen run this*/
	if(strcmp(argv[1], "-f") == 0){
		long double frob_norm = frobenius(matrix1, size1);
		printf("Frobenius norm of matrix1 = %LF", frob_norm);
	}

	/*If transpose chosen run this*/
	if(strcmp(argv[1], "-t") == 0){
		/*allocate array for the transpose matrix to be stored in*/
		long double *tranmatrix = malloc(size1[1]*size1[0]*sizeof(long double));
		transpose(matrix1, tranmatrix, size1);

		/*print matrix in terminal, comment out if not required*/
		printf("Transpose of matrix is;\n");
		for(int x = 0; x < size1[1]; x++){
			for(int y = 0; y < size1[0]; y++){
				printf("%LF	", tranmatrix[size1[0]*x+y]);
			}
			printf("\n");
		}
		/*print to file, tell print_file the size of matrix*/
		int sizet[2] = {size1[1], size1[0]};
		print_file(tranmatrix, sizet, output_file, argc, argv);
		free(tranmatrix);
	}

	/*If multiply chosen run this*/
	if(strcmp(argv[1], "-m") == 0){
		char *filename2 = argv[3];/*get name of second file*/
		int size2[2] = {0,0};/*size of matrix2 rows x cols*/
		get_size(filename2, size2);

		/*check that the calculation is possible*/
		if(size1[1] != size2[0]){
			printf("Number of columns of the first matrix must equal the number of rows of the second\n");
			return 0;
		}

		/*
		limit size up to 11, but could edit code to be able to scan in more
		*/
		if(size2[0] > 11 || size2[1] > 11){
			printf("Please make matrix only up to 11 rows/columns");
		return 0;
		}
		/*alloctate space for the second matrix*/
		long double *matrix2 = malloc(size2[0]*size2[1]*sizeof(long double));
		get_matrix(filename2, size2, matrix2);
		/*allocate matrix of coorect size for result of multiplication*/
		long double *multiplied = malloc(size2[1]*size1[0]*sizeof(long double));
		multiply(matrix1, matrix2, multiplied, size1, size2);

		/*print matrix in terminal, comment out if not required*/
		printf("Matrix1 multiplied by matrix2 is;\n");
		for(int i = 0; i < size1[0]; i++){
			for(int j = 0; j < size2[1]; j++){
				printf("%LF	", multiplied[size2[1]*i+j]);
			}
			printf("\n");
		}
		/*print to file, tell print_file the size of matrix*/
		int sizem[2] = {size2[1],size1[0]};
		print_file(multiplied, sizem, output_file, argc, argv);
		free(matrix2);
		free(multiplied);
	}

	/*If determinant chosen run this*/
	if(strcmp(argv[1], "-d") == 0){
		if(size1[0] != size1[1]){
			/*check that a square matrix is input as will not work with others*/
			printf("Matrix must be square");
			return 0;
		}
		/*make variable that is rank of square matrix*/
		int rank = size1[0];
		long double det = determinant(matrix1, rank);
		printf("determinant is %LF", det);
	}

	/*If adjoint chosen run this*/
	if(strcmp(argv[1], "-a") == 0){
		/*check that a square matrix is input as will not work with others*/
		if(size1[0] != size1[1]){
			printf("Matrix must be square");
			return 0;
		}
		/*make variable that is rank of square matrix*/
		int rank = size1[0];
		/*alloctate space for the adjoint matrix*/
		long double *adjoint_mat = malloc((rank)*(rank)*sizeof(long double));
		adjoint(matrix1, adjoint_mat, rank);

		/*print matrix in terminal, comment out if not required*/
		printf("Adjoint matrix is\n");
		for(int i = 0; i < rank; i++){
			for(int j = 0; j < rank; j++){
				printf("%LF	", adjoint_mat[rank*i+j]);
			}
			printf("\n");
		}

		/*print to file*/
		print_file(adjoint_mat, size1, output_file, argc, argv);
		free(adjoint_mat);
	}

	/*If inverse chosen run this*/
	if(strcmp(argv[1], "-i") == 0){
		/*check that a square matrix is input as will not work with others*/
		if(size1[0] != size1[1]){
			printf("Matrix must be square");
			return 0;
		}
		/*make variable that is rank of square matrix*/
		int rank = size1[0];
		/*alloctate space for the inverse matrix*/
		long double *inverse_mat = malloc((rank)*(rank)*sizeof(long double));
		inverse(matrix1, inverse_mat, rank);
		/*print matrix in terminal, comment out if not required*/
		for(int i = 0; i < rank; i++){
			for(int j = 0; j < rank; j++){
				printf("%LF	", inverse_mat[rank*i+j]);
			}
			printf("\n");
		}
		/*print to file*/
		print_file(inverse_mat, size1, output_file, argc, argv);
	}

	free(matrix1);
	return 0;
}

/*
======================================================================================================
*/



/*Function to open file and read line 3 to get the size of the matrix within the file*/
int get_size(char *filename, int *size){
	FILE *fp;
	int i = 0;
	char buffer[200];
	fp = fopen(filename, "r");
	/*print error if file can't open*/
	if (fp == NULL){
		printf("File could not open %s\n",filename);
		return 0;
	}
	/*copies size from line 3 and prints the size of matrix to terminal*/
	do{i++;
		if(fgets(buffer, 200 ,fp) != NULL){
			if(i == 3){
				sscanf(buffer, "matrix %d %d",&size[0] , &size[1]);
				printf("%s contains matrix of %d by %d\n",filename, size[0],size[1]);
			}
		}
	}while(!feof(fp)&& i <= 3);
	fclose(fp);
}

/*Function extracts the matrix from the file and stores it in the size array*/
void get_matrix(char *filename, int *size, long double *matrix){
	FILE *fp;
	fp = fopen(filename, "r");
	int i = 0;
	char buffer[200];
	/*
	Goes to line 4 onward and scans the matrix into memory,
	This could definitely be better but could not figure out how to get it
	working in limited time, so this works up to 12 columns,
	could edit to add more, but calcculations will be very slow.
	*/

	do{i++;
		if(fgets(buffer, 200 ,fp) != NULL){
			if(i >= 4 && i <= size[0]+3){
				sscanf(buffer,"%LF %LF %LF %LF %LF %LF %LF %LF %LF %LF %LF %LF",
				&matrix[size[1]*(i-4)+0],&matrix[size[1]*(i-4)+1],&matrix[size[1]*(i-4)+2],
				&matrix[size[1]*(i-4)+3],&matrix[size[1]*(i-4)+4],&matrix[size[1]*(i-4)+5],
				&matrix[size[1]*(i-4)+6],&matrix[size[1]*(i-4)+7],&matrix[size[1]*(i-4)+8],
				&matrix[size[1]*(i-4)+9],&matrix[size[1]*(i-4)+10],&matrix[size[1]*(i-4)+11] );
			}
		}
	}while(!feof(fp));

	/*print matrix to terminal to check it is correct*/
	for(int x = 0; x < size[0]; x++){
		for(int y = 0; y < size[1]; y++){
			printf("%LF ", matrix[size[1]*x+y]);
		}
		printf("\n");
	}
	printf("\n");
	fclose(fp);
}

/*
Function takes the matrix and size and calculates the frobenius norm from it
by squaring each element of the matrix and adding them together
*/
long double frobenius(long double* matrix1, int *size){
	int sum_squares = 0;
	for(int i = 0; i < size[0]; i++){
		for(int j = 0; j < size[1]; j++){
			sum_squares += pow(matrix1[size[1]*i+j], 2);
		}
	}
	long double norm = sqrt(sum_squares);
	return norm;

}

/*
Function takes matrix read from file and transposes it into second matrix
by mapping i to j and vice versa in a for loop
*/
void transpose(long double* matrix1, long double *tranmatrix, int *size){
	for(int i = 0; i < size[1]; i++){
		for(int j = 0; j < size[0]; j++){
			tranmatrix[size[0]*i+j] = matrix1[size[1]*j+i];
		}
	}
}

/*Function takes 2 matrices and multiplies them, iterates over elements
multiplying and adding appropriately and placing in new array.*/
void multiply(long double *matrix1, long double *matrix2, long double *multiplied, int *size1, int *size2){
	for(int i = 0; i < size1[0]; i++){
		for(int j = 0; j < size2[1]; j++){
			for(int k = 0; k < size1[1]; k++){
				multiplied[size2[1]*i+j] += matrix1[size1[1]*i+k] * matrix2[size2[1]*k+j];
			}
		}
	}
}

/*Function calculates the determinant of an input matrix (recursivelly if rank > 2) and returns it*/
long double determinant(long double *matrix, unsigned int rank){
	long double det = 0.0;
	/*1x1 matrix just return value*/
	if(rank == 1){
		det = matrix[0];
	}
	/*Calculation for a 2x2 matrix, final step in recursive calls*/
	if(rank == 2){
		det = matrix[rank*0+0] * matrix[rank*1+1] - matrix[rank*1+0] * matrix[rank*0+1];
	}
	/*Calls itself recursively until rank is 2*/
	if(rank > 2){
		long double *cofactor = malloc((rank-1)*(rank-1)*sizeof(long double));
		/*iterate over j from 1 to rank to leave out j=0,
		keep k 0 so that the first row is removed*/
		for(int i = 0; i < rank; i++){
			for(int j = 1; j < rank; j++){
				int k = 0;
				for(int l = 0; l < rank; l++){
					if(l == i)continue;/*if l is the same as i skip putting it in cofactor matrix*/
					cofactor[(rank-1)*(j-1)+k] = matrix[rank*j+l];
					k++;
				}
			}
			det += pow(-1, i)*matrix[rank*0+i]*determinant(cofactor,rank-1);/*-1 to the power of i as k kept at 0*/
		}
		free(cofactor);
	}
	return det;
}

/*Find the adjoint of input matrix and return passed array*/
void adjoint(long double *matrix, long double *adjoint_mat, unsigned int rank){
	if(rank == 1){
		adjoint_mat[rank*0+0] = 1.0;

	}else if(rank > 1){
		long double *cofactor = malloc((rank-1)*(rank-1)*sizeof(long double));
		/*cycle through input matrix*/
		for(int i = 0; i < rank; i++){
			for(int j = 0; j < rank; j++){
				/*increase x when at end of row and y after each column*/
				int x = 0, y = 0;
				for(int k = 0; k < rank; k++){
					for(int l = 0; l < rank; l++){
						if(k != i && l != j){/*fill cofactor leaving ot row and column currently in*/
							cofactor[(rank-1)*x+y] = matrix[rank*k+l];
							y++;
							if(x == rank-1){/*reset y to zero at end of each row*/
								y = 0;
								x++;
							}
						}
					}
				}

				adjoint_mat[(rank)*j+i] = pow(-1, i+j)*determinant(cofactor, rank-1);

			}
		}
		free(cofactor);
	}
}

/*
Function takes in matrix, finds determinan tand adjoint matrix,
then multiplies 1/determinant * adjoint to find inverse
*/
void inverse(long double *matrix, long double *inverse_mat, unsigned int rank){
	long double det = determinant(matrix, rank);
	long double *adjoint_mat = malloc((rank)*(rank)*sizeof(long double));
	adjoint(matrix, adjoint_mat, rank);
	for(int i = 0; i < rank; i++){
		for(int j = 0; j < rank; j++){
			inverse_mat[rank*i+j] = 1/det*adjoint_mat[rank*i+j];
		}
	}
	free(adjoint_mat);
}

/*Function to print a file of the result matrix in the same format as imput*/
void print_file(long double *matrix, int *size, char *output_file, int argc, char **argv){
	FILE *fp;
	fp = fopen(output_file,"w");
	fprintf(fp, "# ");
	for(int i = 0; i < argc; i++){
		fprintf(fp, "%s ", argv[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp, "# Version = %s, Revision date = %s\n", VERSION, REV_DATE);
	fprintf(fp, "matrix %d %d\n", size[0], size[1]);
	for(int j = 0; j < size[0]; j++){
		for(int k = 0; k < size[1]; k++){
			fprintf(fp, "%LF	", matrix[size[1]*j+k]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "end\n");

	fclose(fp);
}
