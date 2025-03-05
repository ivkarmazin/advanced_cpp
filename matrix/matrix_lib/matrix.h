// DRAFT FOR TEMPLATES

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <algorithm>
#include <math.h>

#define EPS 1e-10
#define INF 999999

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

template <size_t N, size_t M>
class Matrix {
    public:
        Matrix();
        Matrix(double a[N][M]);
        Matrix(const Matrix<N,M>&);
        ~Matrix();

        template<size_t N2, size_t M2>
        bool operator==(const Matrix<N2, M2>& m) const;

        inline double& operator()(int x, int y) { return p[x][y]; }

        Matrix<N,M>& operator+=(const Matrix<N,M>&);
        Matrix<N,M>& operator+=(const double&);
        Matrix<N,M>& operator-=(const Matrix<N,M>&);
        Matrix<N,M>& operator-=(const double&);
        Matrix<N,M>& operator*=(double);
        Matrix<N,M>& operator/=(double);

        template<size_t N2, size_t M2>
        friend std::ostream& operator<<(std::ostream&, const Matrix<N2,M2>& m);
    
        void swapRows(int, int);
        Matrix<M,N> transpose();
        double determinant();

        static Matrix<N,N> createIdentity();

        // functions on vectors
        template<size_t N2, size_t M2>
        static double dotProduct(Matrix<N,M>, Matrix<N2,M2>);
        Matrix<1,M> row(int);
        Matrix<N,1> column(int);
        Matrix<1,N> diagonal();
        Matrix<N,M> addRow(const Matrix<1,M>&);
        Matrix<N,M> addCol(const Matrix<N,1>&);

        // functions on augmented matrices
        static Matrix<N, 2 * M> augment(Matrix<N,M>, Matrix<N,M>);
        Matrix<N,M> gaussianEliminate();
        Matrix<N,M> rowReduceFromGaussian();
        Matrix<N,M> inverse();
        
        int rows_ = N, cols_ = M;
        double p[N][M];

        private:
        void allocSpace();
};

template <size_t N, size_t M>
Matrix<N,M> operator+(const Matrix<N,M>&, const Matrix<N,M>&);
template <size_t N, size_t M>
Matrix<N,M> operator+(const Matrix<N,M>&, const double&);
template <size_t N, size_t M>
Matrix<N,M> operator-(const Matrix<N,M>&, const Matrix<N,M>&);
template <size_t N, size_t M>
Matrix<N,M> operator-(const Matrix<N,M>&, const double&);
template <size_t N, size_t M>
Matrix<N,M> operator^(const Matrix<N,M>&, const Matrix<N,M>&);
template <size_t N, size_t M, size_t K>
Matrix<N,K> operator*(const Matrix<N,M>&, const Matrix<M,K>&);
template <size_t N, size_t M>
Matrix<N,M> operator*(const Matrix<N,M>&, double);
template <size_t N, size_t M>
Matrix<N,M> operator*(double, const Matrix<N,M> &);
template <size_t N, size_t M>
Matrix<N,M>  operator/(const Matrix<N,M>&, double);

template <size_t M>
using RowVector = Matrix<1, M>;

template <size_t N>
using ColumnVector = Matrix<N, 1>;

template <size_t N, size_t M>
Matrix<N,M>::Matrix()
{
    //allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = 0;
        }
    }
}

template <size_t N, size_t M>
Matrix<N,M>::Matrix(double a[N][M])
{
    //allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = a[i][j];
        }
    }
}

template <size_t N, size_t M>
Matrix<N,M>::Matrix(const Matrix<N,M>& m)
{
    //allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
}

template <size_t N, size_t M>
Matrix<N,M>::~Matrix()
{}

template <size_t N, size_t M>
template <size_t N2, size_t M2>
bool Matrix<N,M>::operator==(const Matrix<N2,M2>& m) const
{
    bool answer = false;
    if (rows_ == m.rows_ || cols_ == m.cols_) {
        answer = true;
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (p[i][j] - m.p[i][j] > EPS || p[i][j] - m.p[i][j] < -EPS)
                    answer = false;
            }
        }
    }
    return answer;
}

template <size_t N, size_t M>
Matrix<N,M>& Matrix<N,M>::operator+=(const Matrix<N,M>& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}

template <size_t N, size_t M>
Matrix<N,M>& Matrix<N,M>::operator+=(const double& num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] += num;
        }
    }
    return *this;
}

template <size_t N, size_t M>
Matrix<N,M>& Matrix<N,M>::operator-=(const Matrix<N,M>& m)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}

template <size_t N, size_t M>
Matrix<N,M>& Matrix<N,M>::operator-=(const double& num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] -= num;
        }
    }
    return *this;
}

template <size_t N, size_t M>
Matrix<N,M>& Matrix<N,M>::operator*=(double num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] *= num;
        }
    }
    return *this;
}

template <size_t N, size_t M>
Matrix<N,M>& Matrix<N,M>::operator/=(double num)
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] /= num;
        }
    }
    return *this;
}

template <size_t N, size_t M>
void Matrix<N,M>::swapRows(int r1, int r2)
{
    /*double temp[M] = p[r1];
    p[r1] = p[r2];
    p[r2] = temp;*/
    std::swap(p[r1], p[r2]);
}

template <size_t N, size_t M>
Matrix<M,N> Matrix<N,M>::transpose()
{
    Matrix<M,N> ret;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            ret.p[j][i] = p[i][j];
        }
    }
    return ret;
}

template<size_t N, size_t M>
double Matrix<N,M>::determinant(){
    int num1, num2, index, n = N; 
    double det = 1, total = 1, tmp;
    double temp[n + 1];
 
    for (int i = 0; i < n; i++)
    {
        index = i;
        while (p[index][i] == 0 && index < n)
        {
            index++;
        }
        if (index == n)
        {
            continue;
        }
        if (index != i)
        {
            for (int j = 0; j < n; j++)
            {
                tmp = p[index][j];
                p[index][j] = p[i][j];
                p[i][j] = tmp;
            }
            det = det * pow(-1, index - i);
        }
        for (int j = 0; j < n; j++)
        {
            temp[j] = p[i][j];
        }
        for (int j = i + 1; j < n; j++)
        {
            num1 = temp[i]; 
            num2 = p[j][i];
            for (int k = 0; k < n; k++)
            {
                p[j][k]
                    = (num1 * p[j][k]) - (num2 * temp[k]);
            }
            total = total * num1; // Det(kA)=kDet(A);
        }
    }
    for (int i = 0; i < n; i++)
    {
        det = det * p[i][i];
    }
    return (det / total); // Det(kA)/k=Det(A);
}

/* STATIC CLASS FUNCTIONS
 ********************************/
template<size_t N, size_t M>
Matrix<N,N> Matrix<N,M>::createIdentity()
{
    Matrix<N,N> temp;
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            if (i == j) {
                temp.p[i][j] = 1;
            } else {
                temp.p[i][j] = 0;
            }
        }
    }
    return temp;
}

// functions on VECTORS
template<size_t N, size_t M>
template<size_t N2, size_t M2>
double Matrix<N,M>::dotProduct(Matrix<N,M> a, Matrix<N2,M2> b)
{
    double sum = 0;
    for (int i = 0; i < a.cols_; ++i) {
        sum += (a(0, i) * b(i, 0));
    }
    return sum;
}

template<size_t N, size_t M>
Matrix<1,M> Matrix<N,M>::row(int i)
{   
    Matrix<1,M> temp;
    for (int j = 0; j < M; ++j)
        temp.p[0][j] = p[i][j];
    return temp;
}

template<size_t N, size_t M>
Matrix<N,1> Matrix<N,M>::column(int j)
{
    Matrix<N,1> temp;
    for (int i = 0; i < N; ++i)
        temp.p[i][0] = p[i][j];
    return temp;
}

template<size_t N, size_t M>
Matrix<1,N> Matrix<N,M>::diagonal()
{
    Matrix<1,N> temp;
    for (int i = 0; i < N; ++i)
        temp.p[0][i] = p[i][i];
    return temp;
}

template<size_t N, size_t M>
Matrix<N,M> Matrix<N,M>::addRow(const Matrix<1,M>& row)
{
    Matrix<N, M> result;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            result.p[i][j] = p[i][j] + row.p[0][j];
        }
    }
    return result;
}

template<size_t N, size_t M>
Matrix<N,M> Matrix<N,M>::addCol(const Matrix<N,1>& col)
{
    Matrix<N, M> result;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            result.p[i][j] = p[i][j] +  col.p[i][0];
        }
    }
    return result;
}

// functions on AUGMENTED matrices
template<size_t N, size_t M>
Matrix<N,2 * M> Matrix<N,M>::augment(Matrix<N,M> A, Matrix<N,M> B)
{
    Matrix<N, 2*M> AB;
    for (int i = 0; i < AB.rows_; ++i) {
        for (int j = 0; j < AB.cols_; ++j) {
            if (j < A.cols_)
                AB(i, j) = A(i, j);
            else
                AB(i, j) = B(i, j - B.cols_);
        }
    }
    return AB;
}

template<size_t N, size_t M>
Matrix<N,M> Matrix<N,M>::gaussianEliminate()
{
    Matrix Ab(*this);
    int rows = Ab.rows_;
    int cols = Ab.cols_;
    int Acols = cols - 1;

    int i = 0; // row tracker
    int j = 0; // column tracker

    // iterate through the rows
    while (i < rows)
    {
        // find a pivot for the row
        bool pivot_found = false;
        while (j < Acols && !pivot_found)
        {
            if (Ab(i, j) != 0) { // pivot not equal to 0
                pivot_found = true;
            } else { // check for a possible swap
                int max_row = i;
                double max_val = 0;
                for (int k = i + 1; k < rows; ++k)
                {
                    double cur_abs = Ab(k, j) >= 0 ? Ab(k, j) : -1 * Ab(k, j);
                    if (cur_abs > max_val)
                    {
                        max_row = k;
                        max_val = cur_abs;
                    }
                }
                if (max_row != i) {
                    Ab.swapRows(max_row, i);
                    pivot_found = true;
                } else {
                    j++;
                }
            }
        }

        // perform elimination as normal if pivot was found
        if (pivot_found)
        {
            for (int t = i + 1; t < rows; ++t) {
                for (int s = j + 1; s < cols; ++s) {
                    Ab(t, s) = Ab(t, s) - Ab(i, s) * (Ab(t, j) / Ab(i, j));
                    if (Ab(t, s) < EPS && Ab(t, s) > -1*EPS)
                        Ab(t, s) = 0;
                }
                Ab(t, j) = 0;
            }
        }

        i++;
        j++;
    }

    return Ab;
}

template<size_t N, size_t M>
Matrix<N,M> Matrix<N,M>::rowReduceFromGaussian()
{
    Matrix R(*this);
    int rows = R.rows_;
    int cols = R.cols_;

    int i = rows - 1; // row tracker
    int j = cols - 2; // column tracker

    // iterate through every row
    while (i >= 0)
    {
        // find the pivot column
        int k = j - 1;
        while (k >= 0) {
            if (R(i, k) != 0)
                j = k;
            k--;
        }

        // zero out elements above pivots if pivot not 0
        if (R(i, j) != 0) {
       
            for (int t = i - 1; t >= 0; --t) {
                for (int s = 0; s < cols; ++s) {
                    if (s != j) {
                        R(t, s) = R(t, s) - R(i, s) * (R(t, j) / R(i, j));
                        if (R(t, s) < EPS && R(t, s) > -1*EPS)
                            R(t, s) = 0;
                    }
                }
                R(t, j) = 0;
            }

            // divide row by pivot
            for (int k = j + 1; k < cols; ++k) {
                R(i, k) = R(i, k) / R(i, j);
                if (R(i, k) < EPS && R(i, k) > -1*EPS)
                    R(i, k) = 0;
            }
            R(i, j) = 1;

        }

        i--;
        j--;
    }

    return R;
}

template<size_t N, size_t M>
Matrix<N,M> Matrix<N,M>::inverse()
{
    Matrix<N,M> I = Matrix<N,M>::createIdentity();
    double det = this->determinant();
    if (det < EPS && det > -EPS){
        return INF * I;
    }
    Matrix<N, 2 * M> AI = Matrix<N,M>::augment(*this, I);
    //std::cout << AI;
    Matrix<N, 2 * M> U = AI.gaussianEliminate();
    //std::cout << U;
    Matrix<N, 2 * M>  IAInverse = U.rowReduceFromGaussian();
    //std::cout << IAInverse;
    Matrix<N,M> AInverse;
    for (int i = 0; i < AInverse.rows_; ++i) {
        for (int j = 0; j < AInverse.cols_; ++j) {
            AInverse(i, j) = IAInverse(i, j + cols_);
        }
    }
    return AInverse;
}

/* PRIVATE HELPER FUNCTIONS
 ********************************/

template <size_t N, size_t M>
void Matrix<N,M>::allocSpace()
{
    p = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        p[i] = new double[cols_];
    }
}

/* NON-MEMBER FUNCTIONS
 ********************************/

template <size_t N, size_t M>
Matrix<N,M> operator+(const Matrix<N,M> & m1, const Matrix<N,M> & m2)
{
    Matrix<N,M> temp(m1);
    return (temp += m2);
}

template <size_t N, size_t M>
Matrix<N,M> operator+(const Matrix<N,M> & m1, const double& num)
{
    Matrix<N,M> temp(m1);
    return (temp += num);
}

template <size_t N, size_t M>
Matrix<N,M> operator-(const Matrix<N,M>& m1, const Matrix<N,M>& m2)
{
    Matrix<N,M> temp(m1);
    return (temp -= m2);
}

template <size_t N, size_t M>
Matrix<N,M> operator-(const Matrix<N,M> & m1, const double& num)
{
    Matrix<N,M> temp(m1);
    return (temp -= num);
}

template <size_t N, size_t M>
Matrix<N,M> operator^(const Matrix<N,M>& m1, const Matrix<N,M>& m2)
{
    Matrix<N,M> temp(m1);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            temp.p[i][j] *= m2.p[i][j];
        }
    }
    return temp;
}

template <size_t N, size_t M, size_t K>
Matrix<N,K> operator*(const Matrix<N,M>& m1, const Matrix<M,K>& m2)
{
    Matrix<N,K> temp;
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            for (int k = 0; k < m1.cols_; ++k) {
                temp.p[i][j] += (m1.p[i][k] * m2.p[k][j]);
            }
        }
    }
    return temp;
}

template <size_t N, size_t M>
Matrix<N,M> operator*(const Matrix<N,M>& m, double num)
{
    Matrix<N,M> temp(m);
    return (temp *= num);
}

template <size_t N, size_t M>
Matrix<N,M> operator*(double num, const Matrix<N,M>& m)
{
    return (m * num);
}

template <size_t N, size_t M>
Matrix<N,M> operator/(const Matrix<N,M>& m, double num)
{
    Matrix<N,M> temp(m);
    return (temp /= num);
}

template <size_t N2, size_t M2>
ostream& operator<<(ostream& os, const Matrix<N2,M2>& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        os << m.p[i][0];
        for (int j = 1; j < m.cols_; ++j) {
            os << " " << m.p[i][j];
        }
        os << endl;
    }
    return os;
}

#endif // MATRIX_H