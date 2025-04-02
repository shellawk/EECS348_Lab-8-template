#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

// Function to read matrices from file
std::pair<Matrix, Matrix> read_matrices_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    size_t N;
    file >> N;
    if (N == 0) {
        throw std::runtime_error("Matrix size must be positive");
    }

    std::vector<std::vector<int>> mat1(N, std::vector<int>(N));
    std::vector<std::vector<int>> mat2(N, std::vector<int>(N));

    // Read first matrix
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (!(file >> mat1[i][j])) {
                throw std::runtime_error("Invalid matrix data in file");
            }
        }
    }

    // Read second matrix
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (!(file >> mat2[i][j])) {
                throw std::runtime_error("Invalid matrix data in file");
            }
        }
    }

    return {Matrix(mat1), Matrix(mat2)};
}

void print_operation_result(const std::string& operation, const Matrix& result) {
    std::cout << "\n" << operation << ":\n";
    result.print_matrix();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    try {
        // Read matrices from file
        auto [A, B] = read_matrices_from_file(argv[1]);

        // Print original matrices
        std::cout << "Matrix A:\n";
        A.print_matrix();
        std::cout << "\nMatrix B:\n";
        B.print_matrix();

        // Perform and display operations
        print_operation_result("A + B", A + B);
        print_operation_result("A * B", A * B);

        std::cout << "\nDiagonal sums for matrix A:\n";
        std::cout << "Major diagonal sum: " << A.sum_diagonal_major() << "\n";
        std::cout << "Minor diagonal sum: " << A.sum_diagonal_minor() << "\n";

        // Demonstrate row and column swapping
        Matrix A_copy = A;
        A_copy.swap_rows(0, 1);
        print_operation_result("A with rows 0 and 1 swapped", A_copy);

        A_copy = A;
        A_copy.swap_cols(0, 1);
        print_operation_result("A with columns 0 and 1 swapped", A_copy);

        // Demonstrate element modification
        A_copy = A;
        A_copy.set_value(0, 0, 100);
        print_operation_result("A with element (0,0) set to 100", A_copy);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}