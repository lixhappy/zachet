#ifdef tests
bool matrix_linked_test();
#endif

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <string>
#include <cstdlib>

template <class T>
class Matrix {
    private:
        size_t height;
        size_t width;
        T** body;

        void swap_els(size_t , size_t, size_t, size_t);
        void transpose_square();
        void transpose_not_square();
        void reflect_rows();

    public:

        Matrix(size_t, size_t);
        Matrix(size_t, size_t, T**);
        Matrix(const Matrix<T>&);
        ~Matrix();
        T& get(size_t, size_t);
        const T& get(size_t, size_t) const;
        void swap_row(size_t, size_t);
        void swap_col(size_t, size_t);
        void transpose();
        void rotate();
        bool operator== (const Matrix<T>&);
};



#endif