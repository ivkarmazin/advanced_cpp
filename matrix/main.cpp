#include <stdio.h>
#include <iostream>
#include "matrix.h"
using namespace std;

int main() {

    //2) возможность создания матрицы из векторов или чисел, вектора из чисел
    cout << "****** #2 ******\n\n";

    double arr[4][4] = {{1.1, 0.1, 0.2, 0.3},
                        {0,  1.1,  0.1, 0.2},
                        {0,  0,   1.1,  0.1},
                        {0,  0,   0,    1.1}};

    Matrix<4,4> a(arr);
    cout << a << endl;

    //1) обращение по индексам к элементам, извлечение диагонали, строки или столбца 
    cout << "****** #1 ******\n\n";

    cout << a(0,0) << "\n\n";
    cout << a.row(0) << endl;
    cout << a.column(3) << endl;
    cout << a.diagonal() << endl;

    //3) поэлементное сложение/вычитание/умножение объектов одинаковой размерности
    cout << "****** #3 ******\n\n";

    double arr2[4][4] = {{0.1, 0, 0,  0},
                        {0,  0.1, 0,  0},
                        {0.1, 0, 0.1, 0},
                        {0.2, 0.1, 0, 0.1}};

    Matrix<4,4> b(arr2);
    
    cout << (a + b) << endl;
    cout << (a - b) << endl;
    cout << (a ^ b) << endl; // поэлементное умножение 

    //4) умножение числа на матрицу, вектора на матрицу, матрицы на вектор и матрицы на матрицу
    cout << "****** #4 ******\n\n";

    double rowArr[1][4] = {{0, 1, 2, 3}};
    RowVector<4> row(rowArr);
    double colArr[4][1] = {{0},{1},{2},{3}};
    ColumnVector<4> col(colArr);
    
    cout << (3 * a) << endl;
    cout << row * a << endl;
    cout << a * col << endl;
    cout << (a * b) << endl;

    //5) суммирование/вычитание числа и вектора/матрицы, матрицы и вектора (по строкам/столбцам)
    cout << "****** #5 ******\n\n";

    cout << a + 0.1 << endl;
    cout << a - 0.1 << endl;
    cout << a.addRow(a.row(1)) << endl;
    cout << a.addRow(-1 * a.row(1)) << endl;
    cout << a.addCol(a.column(1)) << endl;
    cout << a.addCol(-1 * a.column(1)) << endl;

    //6) получение транспонированной и обратной матриц
    cout << "****** #6 ******\n\n";

    cout << a.transpose() << endl;
    cout << a.inverse() << endl;

    //7) подсчёт определителя матрицы
    cout << "****** #7 ******\n\n";

    cout << a.determinant() << "\n\n";

} 

// sources:
// github.com/akalicki/matrix/tree/master/dist
// geeksforgeeks.org/determinant-of-a-matrix/

/*to build and run:
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
./matrix
./tests/test_matrix
*/