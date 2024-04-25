///////////////////////////////////////////////////////////////////////////////////////////////
// Name: Collin Coakley
// Date: 4-24-2024
///////////////////////////////////////////////////////////////////////////////////////////////
// Objectives:
// - Practice adjacency matrix multiplication and discuss what the results mean
///////////////////////////////////////////////////////////////////////////////////////////////
// Matrix Multiplication: matrix multiplication, particularly in the context of multiplying
// an adjacency matrix by itself (A^2, A^3, ... A^k) provides the number of k-length paths from
// one vector to another. Specifically, given vector at position (i,j) tells you how many two-length
// paths from vector i to vector j. The value in the resulting matrix (matrix C in this code)
// is calculated by summing the products of row*column for a given (i,j).
///////////////////////////////////////////////////////////////////////////////////////////////
// Lab Matrix Q1: What does A^2 represent: It represents the number of 2-length paths from i (row idx) to j (column idx)
// Lab Matrix Q2: What does A^k represent: It represents the number of k-length paths from i (row idx) to j (column idx)
///////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// allocates memory to create a matrix of size rows*cols (this code only uses a square matrix, however)
int** createMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

// function to free the allocated memory for a matrix when finished
void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// helper function to multiply two matrices and store in result Matrix C, with detailed calculation output.
void matrixMultiply(int n, int **A, int **B, int **C) {
    
    // for each row i of matrix square matrix of shape n*n
    for (int i = 0; i < n; i++) {
        // for each column j
        for (int j = 0; j < n; j++) {
            
            // initialize results to 0
            C[i][j] = 0;  // Initialize the result cell to 0
            printf("Calculating C[%d][%d]:\n", i, j);
            // compute the dot product
            for (int k = 0; k < n; k++) {
                printf("  A[%d][%d] * B[%d][%d] = %d * %d = %d (Partial sum = %d)\n", i, k, k, j, A[i][k], B[k][j], A[i][k] * B[k][j], C[i][j] + A[i][k] * B[k][j]);
                C[i][j] += A[i][k] * B[k][j];
            }
            
            // print the result for result Matrix C[i][j]
            printf("  Final Sum for C[%d][%d] = %d\n", i, j, C[i][j]);
        }
    }
}

// function to compute A^k by iterative multiplication
void matrixPower(int n, int **A, int exponent, int **result) {
    int **temp = createMatrix(n, n);
    // Start with A as the initial result if k = 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j];
        }
    }

    // Multiply A k-1 more times
    for (int i = 1; i < exponent; i++) {
        matrixMultiply(n, result, A, temp);
        // Copy temp to result for the next iteration
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[j][k] = temp[j][k];
            }
        }
    }

    freeMatrix(temp, n); 
}

// function to print a matrix in its entirety
void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 3; // This creates an n,n-size matrix
    int k = 2; // Change this value for exponent

    // Create and fill the matrix A (n x n)
    int **A = createMatrix(n, n);
    
    // values I hardcoded for demonstration purposes
    A[0][0] = 0; A[0][1] = 1; A[0][2] = 1;
    A[1][0] = 1; A[1][1] = 0; A[1][2] = 1;
    A[2][0] = 1; A[2][1] = 1; A[2][2] = 0;

    // create a result matrix to populate with the results
    int **result = createMatrix(n, n);
    matrixPower(n, A, k, result);

    // Print the results
    printf("Final results of above incremental calculations:\n");
    printf("Matrix A:\n");
    printMatrix(A, n, n);
    printf("Matrix A^%d:\n", k);
    printMatrix(result, n, n);
    printf("To run this again with another exponent, recompile with a different value for k (exponent)\n");
    // Free the allocated memory
    freeMatrix(A, n);
    freeMatrix(result, n);

    return 0;
}