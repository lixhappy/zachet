#ifndef tests
#define tests

#include <vector>
#include <algorithm>

#include "gtest/gtest.h"
#include "../polynomial/poly.hpp"
#include "../matrix/matrix.hpp"
#include "quick_sort.hpp"

// func for test
int foo(int a, int b) {
    return a + b;
}

// testing tests
TEST(TEST_TEST, testing_test) {
    EXPECT_EQ(foo(1, 3), 4);
}

TEST(SortTest, quicksort) {
    std::vector<int> arr = {};
    for (int _i = 0; _i < 100; _i++) {
        arr.push_back(rand() % 1000);
    }
    quick_sort(arr, 0, arr.size() - 1);
    EXPECT_TRUE(std::is_sorted(begin(arr), end(arr)));

}






// Matrix tests


Matrix<int> test_matrix(size_t n) {
    int** a = (int**) malloc(n * sizeof(int*));
    for (size_t row = 0; row < n; row++) {
        a[row] = (int*) malloc(n * sizeof(int));

        for (int col = 0; col < n; col++) {
            a[row][col] = n * row + col + 1;
        }
    }
    return Matrix<int>(n, n, a);
}

Matrix<int> test_not_sq_matrix(size_t n, size_t m) {
    int** a = (int**) malloc(n * sizeof(int*));
    for (size_t row = 0; row < n; row++) {
        a[row] = (int*) malloc(m * sizeof(int));

        for (int col = 0; col < m; col++) {
            a[row][col] = m * row + col + 1;
        }
    }
    return Matrix<int>(n, m, a);
}







TEST(MATRIX, linked_test) {
    EXPECT_TRUE(matrix_linked_test());
}

TEST(MATRIX, equal) {

    Matrix<int> A = test_matrix(3);
    Matrix<int> B(A);

    EXPECT_TRUE(A == B);

    A.get(0, 0) = 0;
    B.get(0, 0) = 0;

    EXPECT_TRUE(A == B);

    A.get(2, 2) = 0;
    
    EXPECT_FALSE(A == B);
}



TEST(MATRIX, get_el) {

    Matrix<int> A = test_matrix(3);

    //     |1 2 3|
    // A = |4 5 6|
    //     |7 8 9|

    EXPECT_EQ(A.get(0, 0), 1);
    EXPECT_EQ(A.get(0, 1), 2);
    EXPECT_EQ(A.get(0, 2), 3);
    EXPECT_EQ(A.get(1, 0), 4);
    EXPECT_EQ(A.get(1, 1), 5);
    EXPECT_EQ(A.get(1, 2), 6);
    EXPECT_EQ(A.get(2, 0), 7);
    EXPECT_EQ(A.get(2, 1), 8);
    EXPECT_EQ(A.get(2, 2), 9);
    
    A.get(0, 0) = 0;
    
    EXPECT_EQ(A.get(0, 0), 0);
}

TEST(MATRIX, swap_col) {

    Matrix<int> A = test_matrix(3);
    A.swap_col(0, 2);

    // |1 2 3|    |3 2 1|
    // |4 5 6| -> |6 5 4|
    // |7 8 9|    |9 8 7|

    EXPECT_EQ(A.get(0, 0), 3);
    EXPECT_EQ(A.get(0, 1), 2);
    EXPECT_EQ(A.get(0, 2), 1);
    EXPECT_EQ(A.get(1, 0), 6);
    EXPECT_EQ(A.get(1, 1), 5);
    EXPECT_EQ(A.get(1, 2), 4);
    EXPECT_EQ(A.get(2, 0), 9);
    EXPECT_EQ(A.get(2, 1), 8);
    EXPECT_EQ(A.get(2, 2), 7);
}

TEST(MATRIX, swap_row) {

    Matrix<int> A = test_matrix(3);
    A.swap_row(0, 2);

    // |1 2 3|    |7 8 9|
    // |4 5 6| -> |4 5 6|
    // |7 8 9|    |1 2 3|

    EXPECT_EQ(A.get(0, 0), 7);
    EXPECT_EQ(A.get(0, 1), 8);
    EXPECT_EQ(A.get(0, 2), 9);
    EXPECT_EQ(A.get(1, 0), 4);
    EXPECT_EQ(A.get(1, 1), 5);
    EXPECT_EQ(A.get(1, 2), 6);
    EXPECT_EQ(A.get(2, 0), 1);
    EXPECT_EQ(A.get(2, 1), 2);
    EXPECT_EQ(A.get(2, 2), 3);
}

TEST(MATRIX, transpose_square) {
        
    Matrix<int> A = test_matrix(3);
    A.transpose();
    
    // |1 2 3|    |1 4 7|
    // |4 5 6| -> |2 5 8|
    // |7 8 9|    |3 6 9|

    EXPECT_EQ(A.get(0, 0), 1);
    EXPECT_EQ(A.get(0, 1), 4);
    EXPECT_EQ(A.get(0, 2), 7);
    EXPECT_EQ(A.get(1, 0), 2);
    EXPECT_EQ(A.get(1, 1), 5);
    EXPECT_EQ(A.get(1, 2), 8);
    EXPECT_EQ(A.get(2, 0), 3);
    EXPECT_EQ(A.get(2, 1), 6);
    EXPECT_EQ(A.get(2, 2), 9);
}


TEST(MATRIX, transpose_not_square) {
        
    Matrix<int> A = test_not_sq_matrix(3, 4);
    A.transpose();
    
    // |1 2  3  4 |    |1 5 9 |
    // |5 6  7  8 | -> |2 6 10|
    // |9 10 11 12|    |3 7 11|
    //                 |4 8 12|

    EXPECT_EQ(A.get(0, 0), 1);
    EXPECT_EQ(A.get(0, 1), 5);
    EXPECT_EQ(A.get(0, 2), 9);
    EXPECT_EQ(A.get(1, 0), 2);
    EXPECT_EQ(A.get(1, 1), 6);
    EXPECT_EQ(A.get(1, 2), 10);
    EXPECT_EQ(A.get(2, 0), 3);
    EXPECT_EQ(A.get(2, 1), 7);
    EXPECT_EQ(A.get(2, 2), 11);
    EXPECT_EQ(A.get(3, 0), 4);
    EXPECT_EQ(A.get(3, 1), 8);
    EXPECT_EQ(A.get(3, 2), 12);
}


TEST(MATRIX, rotate_square) {
    
    Matrix<int> A = test_matrix(3);
    A.rotate();
    
    // |1 2 3|    |3 6 9|
    // |4 5 6| -> |2 5 8|
    // |7 8 9|    |1 4 7|

    EXPECT_EQ(A.get(0, 0), 3);
    EXPECT_EQ(A.get(0, 1), 6);
    EXPECT_EQ(A.get(0, 2), 9);
    EXPECT_EQ(A.get(1, 0), 2);
    EXPECT_EQ(A.get(1, 1), 5);
    EXPECT_EQ(A.get(1, 2), 8);
    EXPECT_EQ(A.get(2, 0), 1);
    EXPECT_EQ(A.get(2, 1), 4);
    EXPECT_EQ(A.get(2, 2), 7);
    
}

TEST(MATRIX, rotate_not_square) {

    Matrix<int> A = test_not_sq_matrix(3, 4);
    A.rotate();
    
    // |1 2  3  4 |    |4 8 12|
    // |5 6  7  8 | -> |3 7 11|
    // |9 10 11 12|    |2 6 10|
    //                 |1 5 9 |

    EXPECT_EQ(A.get(0, 0), 4);
    EXPECT_EQ(A.get(0, 1), 8);
    EXPECT_EQ(A.get(0, 2), 12);
    EXPECT_EQ(A.get(1, 0), 3);
    EXPECT_EQ(A.get(1, 1), 7);
    EXPECT_EQ(A.get(1, 2), 11);
    EXPECT_EQ(A.get(2, 0), 2);
    EXPECT_EQ(A.get(2, 1), 6);
    EXPECT_EQ(A.get(2, 2), 10);
    EXPECT_EQ(A.get(3, 0), 1);
    EXPECT_EQ(A.get(3, 1), 5);
    EXPECT_EQ(A.get(3, 2), 9);
    
}


// TEST(MATRIX, _) {}










// Polynomial tests
TEST(POLY, linked_test) {
    EXPECT_TRUE(poly_linked_test());
}

TEST(POLY, push) {
    Poly<int> a;
    a.push(0);
    a.push(1);
    Poly<int> b(1);

    EXPECT_TRUE(a == b);
}

TEST(POLY, sum) {
    Poly<int> a(2);
    Poly<int> b(3);
    int tmp[4] = {0, 0, 1, 1};
    Poly<int> c(3, tmp);

    EXPECT_TRUE(c == (a + b));
}

TEST(POLY, add) {
    Poly<int> a(2);
    Poly<int> b(3);
    int tmp[4] = {0, 0, 1, 1};
    Poly<int> c(3, tmp);
    a += b;

    EXPECT_TRUE(c == a);
}

TEST(POLY, diff) {
    Poly<int> a(2);
    Poly<int> b(3);
    int tmp[4] = {0, 0, 1, 1};
    Poly<int> c(3, tmp);

    EXPECT_TRUE((c - b) == a);
}

TEST(POLY, sub) {
    Poly<int> a(2);
    Poly<int> b(3);
    int tmp[4] = {0, 0, 1, 1};
    Poly<int> c(3, tmp);
    c -= b;

    EXPECT_TRUE(c == a);
}

TEST(POLY, factor) {
    int tmp1[2] = {1, 1};
    Poly<int> a(1, tmp1);
    int tmp2[4] = {1, 3, 3, 1};
    Poly<int> a_cub(3, tmp2);

    EXPECT_TRUE((a * a * a) == a_cub);
}

TEST(POLY, mul) {
    int tmp1[2] = {1, 1};
    Poly<int> a(1, tmp1);
    int tmp2[4] = {1, 3, 3, 1};
    Poly<int> a_cub(3, tmp2);

    a *= a * a;

    EXPECT_TRUE(a == a_cub);
}

TEST(POLY, quot) {
        int tmp1[2] = {1, 1};
        Poly<int> a(1, tmp1);
        int tmp2[4] = {1, 3, 3, 1};
        Poly<int> a_cub(3, tmp2);

        EXPECT_TRUE(a_cub / a == a * a);

}

TEST(POLY, rem_and_mod) {
    {
        int tmp1[2] = {1, 1};
        Poly<int> a(1, tmp1);
        int tmp2[4] = {1, 3, 3, 1};
        Poly<int> a_cub(3, tmp2);
        Poly<int> c(a_cub);
        c %= a; 

        EXPECT_TRUE(a_cub % a == Poly<int>());
        EXPECT_TRUE(c == Poly<int>());
    }
    {
        int tmp1[2] = {0, 1};
        Poly<int> a(1, tmp1);
        int tmp2[4] = {1, 3, 3, 1};
        Poly<int> a_cub(3, tmp2);
        Poly<int> c(a_cub);
        c %= a; 

        EXPECT_TRUE(a_cub % a == Poly<int>(0));
        EXPECT_TRUE(c == Poly<int>(0));
    }



}

TEST(POLY, div) {
        int tmp1[2] = {1, 1};
        Poly<int> a(1, tmp1);
        int tmp2[4] = {1, 3, 3, 1};
        Poly<int> a_cub(3, tmp2);
        a_cub /= a;

        EXPECT_TRUE(a_cub == a * a);
}

// TEST(POLY, _) {}




#endif