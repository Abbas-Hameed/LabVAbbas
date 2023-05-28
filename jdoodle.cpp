
#include <iostream>
#include <chrono>
#include <omp.h>

#define SIZE 1000

void parallelMatrixMultiplication(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void serialMatrixMultiplication(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[SIZE][SIZE]; // First matrix
    int B[SIZE][SIZE]; // Second matrix
    int C[SIZE][SIZE]; // Result matrix

   
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

   
    auto startParallel = std::chrono::high_resolution_clock::now();
    parallelMatrixMultiplication(A, B, C);
    auto endParallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> parallelTime = endParallel - startParallel;

    auto startSerial = std::chrono::high_resolution_clock::now();
    serialMatrixMultiplication(A, B, C);
    auto endSerial = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> serialTime = endSerial - startSerial;

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Parallel execution time: " << parallelTime.count() << " seconds" << std::endl;
    std::cout << "Serial execution time: " << serialTime.count() << " seconds" << std::endl;

    return 0;
}
