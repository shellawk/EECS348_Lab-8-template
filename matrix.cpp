#include "matrix.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

// Constructor that creates an NxN matrix initialized with zeros
Matrix::Matrix(size_t N) {
    data.resize(N, std::vector<int>(N, 0));
}

// Constructor that creates a matrix from a 2D vector
Matrix::Matrix(std::vector<std::vector<int>> nums) {
    // Verify the input is a square matrix
    size_t size = nums.size();
    for (const auto& row : nums) {
        if (row.size() != size) {
            throw std::invalid_argument("Input is not a square matrix");
        }
    }
    data = nums;
}

// Matrix addition operator
Matrix Matrix::operator+(const Matrix &rhs) const {
    if (data.size() != rhs.data.size()) {
        throw std::invalid_argument("Matrix sizes don't match for addition");
    }
    
    Matrix result(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data.size(); j++) {
            result.data[i][j] = data[i][j] + rhs.data[i][j];
        }
    }
    return result;
}

// Matrix multiplication operator
Matrix Matrix::operator*(const Matrix &rhs) const {
    if (data.size() != rhs.data.size()) {
        throw std::invalid_argument("Matrix sizes don't match for multiplication");
    }
    
    Matrix result(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data.size(); j++) {
            int sum = 0;
            for (size_t k = 0; k < data.size(); k++) {
                sum += data[i][k] * rhs.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

// Set value at specific position
void Matrix::set_value(std::size_t i, std::size_t j, int n) {
    if (i >= data.size() || j >= data.size()) {
        throw std::out_of_range("Index out of bounds in set_value");
    }
    data[i][j] = n;
}

// Get value at specific position
int Matrix::get_value(std::size_t i, std::size_t j) const {
    if (i >= data.size() || j >= data.size()) {
        throw std::out_of_range("Index out of bounds in get_value");
    }
    return data[i][j];
}

// Get matrix size (N for NxN matrix)
int Matrix::get_size() const {
    return static_cast<int>(data.size());
}

// Sum of main diagonal (top-left to bottom-right)
int Matrix::sum_diagonal_major() const {
    int sum = 0;
    for (size_t i = 0; i < data.size(); i++) {
        sum += data[i][i];
    }
    return sum;
}

// Sum of minor diagonal (top-right to bottom-left)
int Matrix::sum_diagonal_minor() const {
    int sum = 0;
    for (size_t i = 0; i < data.size(); i++) {
        sum += data[i][data.size() - 1 - i];
    }
    return sum;
}

// Swap two rows
void Matrix::swap_rows(std::size_t r1, std::size_t r2) {
    if (r1 >= data.size() || r2 >= data.size()) {
        throw std::out_of_range("Row index out of bounds in swap_rows");
    }
    std::swap(data[r1], data[r2]);
}

// Swap two columns
void Matrix::swap_cols(std::size_t c1, std::size_t c2) {
    if (c1 >= data.size() || c2 >= data.size()) {
        throw std::out_of_range("Column index out of bounds in swap_cols");
    }
    for (size_t i = 0; i < data.size(); i++) {
        std::swap(data[i][c1], data[i][c2]);
    }
}

// Print matrix with aligned columns
void Matrix::print_matrix() const {
    for (const auto &row : data) {
        for (int val : row) {
            std::cout << std::setw(4) << val << " ";
        }
        std::cout << std::endl;
    }
}