#include <gtest/gtest.h>
#include "matrix.h"

//2) возможность создания матрицы из векторов или чисел, вектора из чисел

double arrA[4][4] = {{1.1, 0.1, 0.2, 0.3},
                    {0,  1.1,  0.1, 0.2},
                    {0,  0,   1.1,  0.1},
                    {0,  0,   0,    1.1}};
double arrB[4][4] = {{0.1, 0, 0,  0},
                    {0,  0.1, 0,  0},
                    {0.1, 0, 0.1, 0},
                    {0.2, 0.1, 0, 0.1}};

Matrix<4,4> a(arrA), b(arrB);

TEST(Matrix, Test2) {
    EXPECT_EQ(a.cols_, 4);
    EXPECT_EQ(a.rows_, 4);
    EXPECT_DOUBLE_EQ(a.p[0][0], 1.1);
    EXPECT_DOUBLE_EQ(a.p[0][1], 0.1);
    EXPECT_DOUBLE_EQ(a.p[1][0], 0);
    EXPECT_DOUBLE_EQ(a.p[1][1], 1.1);
    // etc.
}

//1) обращение по индексам к элементам, извлечение диагонали, строки или столбца 

TEST(Matrix, Test1) {
    double arrRow0[1][4] = {{1.1, 0.1, 0.2, 0.3}};
    double arrColumn3[4][1] = {{0.3}, {0.2}, {0.1}, {1.1}};
    double arrDiagonal[1][4] = {{1.1, 1.1, 1.1, 1.1}};
    Matrix<1,4> row0(arrRow0), diagonal(arrDiagonal);
    Matrix<4,1> column3(arrColumn3);

    EXPECT_DOUBLE_EQ(a(0,0), 1.1);
    EXPECT_EQ(a.row(0), row0);
    EXPECT_EQ(a.column(3), column3);
    EXPECT_EQ(a.diagonal(), diagonal);
}

//3) поэлементное сложение/вычитание/умножение объектов одинаковой размерности

TEST(Matrix, Test3) {
    double arrSum[4][4] = { {1.2, 0.1, 0.2, 0.3}, 
                            {0, 1.2, 0.1, 0.2}, 
                            {0.1, 0, 1.2, 0.1}, 
                            {0.2, 0.1, 0, 1.2}};
    double arrDiff[4][4] = {{1., 0.1, 0.2, 0.3}, 
                            {0, 1., 0.1, 0.2}, 
                            {-0.1, 0, 1., 0.1}, 
                            {-0.2, -0.1, 0, 1.}};
    double arrProd[4][4] = {{0.11, 0., 0., 0.}, 
                            {0, 0.11, 0., 0.}, 
                            {0., 0, 0.11, 0.}, 
                            {0., 0., 0, 0.11}};

    Matrix<4,4> sum(arrSum), diff(arrDiff), prod(arrProd);
    
    EXPECT_EQ(a + b, sum);
    EXPECT_EQ(a - b, diff);
    EXPECT_EQ(a ^ b, prod); // поэлементное умножение 
}

//4) умножение числа на матрицу, вектора на матрицу, матрицы на вектор и матрицы на матрицу

TEST(Matrix, Test4) {
    double rowArr[1][4] = {{0, 1, 2, 3}};
    double colArr[4][1] = {{0},{1},{2},{3}};

    double arrRes1[4][4] = {{3.3, 0.3, 0.6, 0.9}, 
                            {0, 3.3, 0.3, 0.6}, 
                            {0, 0, 3.3, 0.3}, 
                            {0, 0, 0, 3.3}};
    double arrRes2[1][4] = {{0, 1.1, 2.3, 3.7}};
    double arrRes3[4][1] = {{1.4}, {1.9}, {2.5}, {3.3}};
    double arrRes4[4][4] = {{0.19, 0.04, 0.02, 0.03}, 
                            {0.05, 0.13, 0.01, 0.02}, 
                            {0.13, 0.01, 0.11, 0.01}, 
                            {0.22, 0.11, 0, 0.11}};

    RowVector<4> row(rowArr), res2(arrRes2);
    ColumnVector<4> col(colArr), res3(arrRes3);
    Matrix<4,4> res1(arrRes1), res4(arrRes4);

    EXPECT_EQ(3 * a, res1);
    EXPECT_EQ(row * a, res2);
    EXPECT_EQ(a * col, res3);
    EXPECT_EQ(a * b, res4);
}

//5) суммирование/вычитание числа и вектора/матрицы, матрицы и вектора (по строкам/столбцам)

TEST(Matrix, Test5) {
    double arrRes1[4][4] = {{1.2, 0.2, 0.3, 0.4}, 
                            {0.1, 1.2, 0.2, 0.3}, 
                            {0.1, 0.1, 1.2, 0.2}, 
                            {0.1, 0.1, 0.1, 1.2}};
    double arrRes2[4][4] = {{1., 0., 0.1, 0.2}, 
                            {-0.1, 1., 0., 0.1}, 
                            {-0.1, -0.1, 1., 0.}, 
                            {-0.1, -0.1, -0.1, 1.}};
    double arrRes3[4][4] = {{1.1, 1.2, 0.3, 0.5}, 
                            {0, 2.2, 0.2, 0.4}, 
                            {0, 1.1, 1.2, 0.3}, 
                            {0, 1.1, 0.1, 1.3}};
    double arrRes4[4][4] = {{1.2, 0.2, 0.3, 0.4}, 
                            {1.1, 2.2, 1.2, 1.3}, 
                            {0, 0, 1.1, 0.1}, 
                            {0, 0, 0, 1.1}};

    Matrix<4,4> res1(arrRes1), res2(arrRes2), res3(arrRes3), res4(arrRes4);

    EXPECT_EQ(a + 0.1, res1);
    EXPECT_EQ(a - 0.1, res2);
    EXPECT_EQ(a.addRow(a.row(1)), res3);
    EXPECT_EQ(a.addCol(a.column(1)), res4);
}

//6) получение транспонированной и обратной матриц

double transArr[4][4] = {{1.1, 0,  0,   0},
                        {0.1, 1.1, 0,   0},
                        {0.2, 0.1, 1.1, 0},
                        {0.3, 0.2, 0.1, 1.1}};
double invArr[4][4] = { {0.909091, -0.0826446, -0.157776, -0.218564},
                        {0,         0.909091, -0.0826446, -0.157776},
                        {0,         0,         0.909091, -0.0826446},
                        {0,         0,         0,         0.909091}};

Matrix<4,4> invA(invArr), transA(transArr);

TEST(Matrix, Test6) {
    EXPECT_EQ(a.transpose(), transA);
}

//7) подсчёт определителя матрицы

TEST(Matrix, Test7) {
    EXPECT_DOUBLE_EQ(a.determinant(), 1.4641);
}