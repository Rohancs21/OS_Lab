#include <stdio.h>
#include<stdlib.h>

int add() {
  int r, c, a[100][100], b[100][100], sum[100][100], i, j;
  printf("Enter the number of rows: ");
  scanf("%d", &r);
  printf("Enter the number of columns: ");
  scanf("%d", &c);

  printf("\nEnter elements of 1st matrix:\n");
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j) {
      printf("Enter element a%d%d: ", i + 1, j + 1);
      scanf("%d", &a[i][j]);
    }

  printf("Enter elements of 2nd matrix:\n");
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j) {
      printf("Enter element b%d%d: ", i + 1, j + 1);
      scanf("%d", &b[i][j]);
    }

  
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j) {
      sum[i][j] = a[i][j] + b[i][j];
    }
  printf("\nSum of two matrices: \n");
  for (i = 0; i < r; ++i)
    for (j = 0; j < c; ++j) {
      printf("%d   ", sum[i][j]);
      if (j == c - 1) {
        printf("\n\n");
      }
    }

  return 0;
}

void getMatrixElements(int matrix[][10], int row, int column) {

   printf("\nEnter elements: \n");

   for (int i = 0; i < row; ++i) {
      for (int j = 0; j < column; ++j) {
         printf("Enter a%d%d: ", i + 1, j + 1);
         scanf("%d", &matrix[i][j]);
      }
   }
}

// function to multiply two matrices
void multiplyMatrices(int first[][10],
                      int second[][10],
                      int result[][10],
                      int r1, int c1, int r2, int c2) {

   // Initializing elements of matrix mult to 0.
   for (int i = 0; i < r1; ++i) {
      for (int j = 0; j < c2; ++j) {
         result[i][j] = 0;
      }
   }

   // Multiplying first and second matrices and storing it in result
   for (int i = 0; i < r1; ++i) {
      for (int j = 0; j < c2; ++j) {
         for (int k = 0; k < c1; ++k) {
            result[i][j] += first[i][k] * second[k][j];
         }
      }
   }
}

// function to display the matrix
void display(int result[][10], int row, int column) {

   printf("\nOutput Matrix:\n");
   for (int i = 0; i < row; ++i) {
      for (int j = 0; j < column; ++j) {
         printf("%d  ", result[i][j]);
         if (j == column - 1)
            printf("\n");
      }
   }
}

int multiply() {
   int first[10][10], second[10][10], result[10][10], r1, c1, r2, c2;
   printf("Enter rows and column for the first matrix: ");
   scanf("%d %d", &r1, &c1);
   printf("Enter rows and column for the second matrix: ");
   scanf("%d %d", &r2, &c2);

   // Taking input until
   // 1st matrix columns is not equal to 2nd matrix row
   while (c1 != r2) {
      printf("Error! Enter rows and columns again.\n");
      printf("Enter rows and columns for the first matrix: ");
      scanf("%d%d", &r1, &c1);
      printf("Enter rows and columns for the second matrix: ");
      scanf("%d%d", &r2, &c2);
   }

   // get elements of the first matrix
   getMatrixElements(first, r1, c1);

   // get elements of the second matrix
   getMatrixElements(second, r2, c2);

   // multiply two matrices.
   multiplyMatrices(first, second, result, r1, c1, r2, c2);

   // display the result
   display(result, r1, c2);

   return 0;
}

int symmetric()
{
  int i, j, r,c, a[100][100], b[100][100], d = 1;
  
  printf("\nEnter the number of rows and columns  :  ");
  scanf("%d %d", &r, &c);
 
  printf("\nEnter the matrix elements \n");
  for(i = 0; i<r; i++)
   {
    for(j = 0;j<c;j++)
     {
       scanf("%d", &a[i][j]);
     }
   }
    //Finding out the Transpose of matrix 
  for(i=0; i<r; i++)
   {
    for(j=0;j<c; j++)
     {
       b[j][i] = a[i][j];
     }
   }
     
  for(i=0; i<r; i++)
   {
    for(j = 0; j<c; j++)
     {
     if(a[i][j] != b[i][j])
     {
     d++;  
break;   
}
      }
   }
   if(d == 1)
   {
   printf("\n The Matrix is a Symmetric Matrix. ");
}
else
{
printf("\n The Matrix is Not a Symmetric Matrix. ");
} 
  return 0;
}

int diag()
{
    int M,N,principal = 0, secondary=0,i,j, a[100][100];
    printf("Enter the number of rows and columns: ");
    scanf("%d", &M);
    M=N;
    printf("\nEnter elements of matrix:\n");
    for (i = 0; i < M; i++){
    for (j = 0; j < N; j++) {
      printf("Enter element a%d%d: ", i + 1, j + 1);
      scanf("%d", &a[i][j]);
    }
}
    for (int i = 0; i < N; i++)
    {
        principal += a[i][i];
        secondary += a[i][N - i - 1];       
    }
 
    printf("%s","Principal Diagonal:");
    printf("%d\n", principal);
    printf("%s", "Secondary Diagonal:");
    printf("%d\n", secondary);
}


void main() {
    int choice;
    printf("Enter the operation to be performed:\n");
    printf("1.Addition\n2.Multiplication\n3.Check for Symmetric Matrix\n4.Sum of principle and non-principle diagonal\n5.Sum of every row and every column\n6.Transpose of a Matrix\n");
    scanf("%d",&choice);
    
    switch(choice)
    {
        case 1:
        add();
        break;
        
        case 2:
        multiply();
        break;
        
        case 3:
        symmetric();
        break;
        
        case 4:
        diag();
        break;
    }
}
