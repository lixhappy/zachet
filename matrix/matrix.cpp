#include <iostream>
#include <string>
#include <cstdlib>
#include <utility>

#include "matrix.hpp"


using std::copy;

// explicit impl
template class Matrix<short>;
template class Matrix<int>;
template class Matrix<long>;
template class Matrix<long long>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long double>;

bool matrix_linked_test() {
    // std::cout << "matrix was linked" << std::endl;
    return true;
}


template <class T>
Matrix<T>::~Matrix() {
    for (size_t i = 0; i < height; i++) {
        free(body[i]);
    }
    free(body);
}

template <class T>
Matrix<T>::Matrix(size_t width_, size_t height_) 
: width{width_}, height{height_} {
    body = (T**) malloc(height * sizeof(T*));
    for (int row = 0; row < height; row++) {
        body[row] = (T*) malloc(width * sizeof(T*));
    }
}

template <class T>
Matrix<T>::Matrix(size_t height_, size_t width_, T** body_) 
: height{height_}, width{width_}, body{body_} {}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& matrix) 
: width{matrix.width}, height{matrix.height} {
    body = (T**) malloc(height * sizeof(T*));
    for (size_t row = 0; row < height; row++) {
        body[row] = (T*) malloc(width * sizeof(T));
        copy(matrix.body[row], matrix.body[row] + width, body[row]);
    }
}

template <class T>
T& Matrix<T>::get(size_t row, size_t col) {
    if (0 <= row && row < height && 0 <= col && col < width) {
        return body[row][col];
    }
    return body[0][0];
}

template <class T>
const T& Matrix<T>::get(size_t row, size_t col) const {
    if (0 <= row && row < height && 0 <= col && col < width) {
        return body[row][col];
    }
    return body[0][0];
}


template <class T>
bool Matrix<T>::operator== (const Matrix<T>& right) {
    if (right.width == width && right.height == height) {
        for (size_t row = 0; row < height; row++) {
            for (size_t col = 0; col < width; col++) {
                if (body[row][col] != right.body[row][col]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

template <class T> 
void Matrix<T>::swap_els(size_t r1, size_t c1, size_t r2, size_t c2) {
    if (0 <= r1 && r1 < height && 0 <= c1 && c1 < width 
        && 0 <= r2 && r2 < height && 0 <= c2 && c2 < width) {
            std::swap(body[r1][c1], body[r2][c2]);
        }
}

template <class T>
void Matrix<T>::swap_row(size_t r1, size_t r2) {
    std::swap(body[r1], body[r2]);
}


template <class T>
void Matrix<T>::swap_col(size_t c1, size_t c2) {
    for (size_t row = 0; row < height; row++) {
        std::swap(body[row][c1], body[row][c2]);
    }
}

template <class T>
void Matrix<T>::transpose() {
    if (width == height) {
        this->transpose_square();
    } else {
        this->transpose_not_square();
    }
}

template <class T>
void Matrix<T>::transpose_square() {
    for (size_t row = 0; row < height; row++) {
        for (size_t col = row + 1; col < width; col++) {
            std::swap(body[row][col], body[col][row]);
        }
    }
}

template <class T>
void Matrix<T>::transpose_not_square() {
    std::swap(width, height);
    T** body_trans = (T**) malloc(height * sizeof(T*));

    for (size_t row = 0; row < height; row++) {
        body_trans[row] = (T*) malloc(width * sizeof(T));
        for (size_t col = 0; col < width; col++) {
            body_trans[row][col] = body[col][row];
        }
    }
    std::swap(body, body_trans);
    free(body_trans);
}


template <class T>
void Matrix<T>::reflect_rows() {
    for (size_t row = 0; row < height / 2; row++) {
        swap_row(row, height - row - 1);
    }
}


template <class T>
void Matrix<T>::rotate() {
    transpose();
    reflect_rows();
}