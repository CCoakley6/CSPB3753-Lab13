///////////////////////////////////////////////////////////////////////////////////////////////
// Name: Collin Coakley
// Date: 4-24-2024
///////////////////////////////////////////////////////////////////////////////////////////////
// Objectives:
// - Practice markov chain and discuss what the results mean
///////////////////////////////////////////////////////////////////////////////////////////////
// Markov Chain: Where M is the transition matrix of a Markov chain, M^k contains the probabilities
// of a transition after k-steps. In a Markov chain, the matrix M must be a square where each entry
// is non-negative, and the sum of each row must equal to 1, as it is a probability distribution
///////////////////////////////////////////////////////////////////////////////////////////////
// Lab Markov Q1: For any positive integer k, is M^k a Markov chain? If M is a transition matrix for a Markov chain, then M^k represents the transition probabilities after k-steps. Therefore, if M is a transition matrix, then M^k is also a Markov Chain, just viewed over k transitions
// Lab Markov Q2: What does the (i, j)-entry of M^k compute? When M is a transition matrix of a Markov chain, the (i,j)-entry of M^k is the probability of transition from i to j after k transitions occur.
///////////////////////////////////////////////////////////////////////////////////////////////
// The following code allocates memory for a transition matrix, initializes it with values I hardcoded
// then performs matrix multiplication k times, normalizing the values along the way to make sure the rows sum to 1.
// There are instances where the sum of the rows are off by .0001, which I consider to be an acceptable margin of error for this assignment
///////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>


// Function to allocate memory for a matrix
float** createMatrix(int size) {
    float **matrix = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (float *)malloc(size * sizeof(float));
    }
    return matrix;
}

// Function to free the allocated memory for a matrix
void freeMatrix(float **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to print a matrix
void printMatrix(float **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to initialize a Markov Chain matrix with fixed values for a 3x3 matrix
void initializeMarkovChain(float **matrix, int size) {
    matrix[0][0] = 0.1; matrix[0][1] = 0.6; matrix[0][2] = 0.3;
    matrix[1][0] = 0.4; matrix[1][1] = 0.2; matrix[1][2] = 0.4;
    matrix[2][0] = 0.3; matrix[2][1] = 0.5; matrix[2][2] = 0.2;
}

// Function to multiply two matrices and store the result in a third matrix
void matrixMultiply(float **A, float **B, float **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to copy matrix B to matrix A
void copyMatrix(float **A, float **B, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = B[i][j];
        }
    }
}

// Function to normalize each row of the matrix to sum to 1 (sometimes off by 0.0001, which is reasonably acceptable)
void normalizeMatrix(float **matrix, int size) {
    for (int i = 0; i < size; i++) {
        float sum = 0.0;
        for (int j = 0; j < size; j++) {
            sum += matrix[i][j];
        }
        float correctionFactor = 1.0 / sum;  // Calculate the factor by which to multiply each element
        for (int j = 0; j < size; j++) {
            matrix[i][j] *= correctionFactor;  // Apply the correction factor
        }
    }
}

int main() {
    int n = 3;  // Size of the Markov chain transition matrix
    int k = 5;  // Number of transitions to calculate M^k
    float **M = createMatrix(n);
    float **Result = createMatrix(n);
    float **Temp = createMatrix(n);

    // Initialize Markov chain with fixed probabilities
    initializeMarkovChain(M, n);
    printf("Initial Markov Chain Matrix M:\n");
    printMatrix(M, n);

    // Initialize Result as identity matrix for multiplication
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                Result[i][j] = 1.0f;
            }
            else {
                Result[i][j] = 0.0f;
            }
        }
    }

    // Compute M^k
    for (int step = 1; step <= k; step++) {
        matrixMultiply(Result, M, Temp, n);
        copyMatrix(Result, Temp, n);
        normalizeMatrix(Result, n);  // Normalize after each multiplication to maintain row sum = 1
        printf("\nMatrix M^%d (normalized):\n", step);
        printMatrix(Result, n);
    }

    // Free the allocated memory
    freeMatrix(M, n);
    freeMatrix(Result, n);
    freeMatrix(Temp, n);

    return 0;
}