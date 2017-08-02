//
// Created by advanced on 17-5-31.
//

#ifndef MPI_MOPSO_MATRIX_H
#define MPI_MOPSO_MATRIX_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include "structDef.h"

template <typename _MD>
class Matrix{
protected:
    size_t n_rows;
    size_t n_cols;
    std::vector<std::vector<_MD> > data;
    class RowProxy {
    private:
        std::vector<_MD> &row;                                   //***** & quote, give a variable another name
    public:
        RowProxy(std::vector<_MD> &_row) : row(_row) {}         // ***** &
        _MD &operator[](const size_t &pos){
            return row[pos];
        }
    };
    class ConstRowProxy {
    private:
        const std::vector<_MD> &row;
    public:
        ConstRowProxy(const std::vector<_MD> &_row) : row(_row) {}
        const _MD &operator[](const size_t &pos) const {
            return row[pos];
        }
    };

public:
    Matrix() {};
    Matrix(const size_t &_n_rows, const size_t &_n_cols)
            : n_rows(_n_rows), n_cols(_n_cols), data(std::vector<std::vector<_MD> >(_n_rows, std::vector<_MD>(n_cols))) {}
    Matrix(const size_t &_n_rows, const size_t &_n_cols, _MD fillValue)
            : n_rows(_n_rows), n_cols(_n_cols), data(std::vector<std::vector<_MD> >(_n_rows, std::vector<_MD>(_n_cols, fillValue))) {}
    Matrix(const Matrix<_MD> &mat)
            : n_rows(mat.n_rows), n_cols(mat.n_cols), data(mat.data) {}
//    Matrix(Matrix<_MD> &&mat) noexcept
//            : n_rows(mat.n_rows), n_cols(mat.n_cols), data(mat.data) {}
    Matrix<_MD> & operator=(const Matrix<_MD> &mat){
        n_rows = mat.n_rows;
        n_cols = mat.n_cols;
        data = mat.data;
        return *this;
    }
//    Matrix<_MD> &operator=(Matrix<_MD> &&mat){
//        n_rows = mat.n_rows;
//        n_cols = mat.n_cols;
//        data = mat.data;
//        return *this;
//    }
    inline const size_t & RowSize() const {
        return n_rows;
    }
    inline const size_t & ColSize() const {
        return n_cols;
    }
    RowProxy operator[](const size_t &Kth){
        return RowProxy(data[Kth]);
    }

    const ConstRowProxy operator[](const size_t &Kth) const {
        return ConstRowProxy(data[Kth]);
    }

    /*
 * w(i,2:i+1) = tmp1 + tmp2;
 */
    Matrix<_MD> matRowChange(const int &row, const int &startCol,
                             const int &endCol, const Matrix<_MD> &x);
    ~Matrix() {};
};



/*
 * Matrix function
 */
/*
     * Sum of two Matrix
     */
template <typename _MD>
Matrix<_MD> operator+(const Matrix<_MD> &a, const Matrix<_MD> &b);

template <typename _MD>
Matrix<_MD> operator+(const Matrix<_MD> &a, const _MD &b);

template <typename _MD>
Matrix<_MD> operator-(const Matrix<_MD> &a, const Matrix<_MD> &b);

Matrix<double> operator-(const Matrix<double> &a, const Matrix<int> &b);

Matrix<double> operator-(const Matrix<int> &a, const Matrix<double> &b);

Matrix<double> operator-(const Matrix<int> &y, const double d);

Matrix<double> operator-(const Matrix<double> &y, const int d);

Matrix<double> operator-(const double d, const Matrix<int> &y);

Matrix<double> operator-(const int d, const Matrix<double> &y);

template <typename _MD>
Matrix<_MD> operator-(const Matrix<_MD> &y, const _MD d);

template <typename _MD>
Matrix<_MD> operator-(const _MD d, const Matrix<_MD> &y);

template <typename _MD>
bool operator==(const Matrix<_MD> &a, const Matrix<_MD> &b);

template <typename _MD>
Matrix<_MD> operator-(const Matrix<_MD> &a);

/*template <typename _MD>
Matrix<_MD> operator-(Matrix<_MD> &&a);*/
/*
 * multiplication of two matrix
 */
template <typename _MD>
Matrix<_MD> operator*(const Matrix<_MD> &a, const Matrix<_MD> &b);
/*
 * matrix multiply a number
 */
template <typename _MD>
Matrix<_MD> operator*(const Matrix<_MD> &a, const _MD &b);

template <typename _MD>
Matrix<_MD> operator*(const _MD &b, const Matrix<_MD> &a);

template <typename _MD>
Matrix<_MD> operator/(const Matrix<_MD> &a, const _MD &b);

Matrix<double> operator/(const Matrix<double> &a, const int &b);

Matrix<double> operator/(const Matrix<int> &a, const double &b);

/*
 * if a[i][j] > b[i][j], c[i][j] = 1, or c[i][j] = 0
 */
template <typename _MD>
Matrix<int> operator>(const Matrix<_MD> &a, const Matrix<_MD> &b);


/*
 * if a[i][j] <= b[i][j], c[i][j] = 1, or c[i][j] = 0
 */
template <typename _MD>
Matrix<int> operator<=(const Matrix<_MD> &a, const Matrix<_MD> &b);

/*   .*   规模相同的矩阵对应位置数相乘    mulCorNum(M,M)  //  multiply corresponding number
     ./  				             divCorNum(M,M)  //  two matrix with the same size
     .^				                 powCorNum(M,D)  */
template <typename _MD>
Matrix<_MD> mulCorNum(const Matrix<_MD> &a, const Matrix<_MD> &b);

Matrix<double> mulCorNum(const Matrix<double> &a, const Matrix<int> &b);

Matrix<double> mulCorNum(const Matrix<int> &a, const Matrix<double> &b);

template <typename _MD>
Matrix<_MD> divCorNum(const Matrix<_MD> &a, const Matrix<_MD> &b);

Matrix<double> divCorNum(const Matrix<double> &a, const Matrix<int> &b);

Matrix<double> divCorNum(const Matrix<int> &a, const Matrix<double> &b);

template <typename _MD>
Matrix<_MD> powCorNum(const Matrix<_MD> &a, const int &p);

/*
 * y = [1,2,3;4,5,6;7,8,9];
 * y(1,1:3) = [5,6];
 */
template <typename _MD>
Matrix<_MD> getArrayFromMatrix(const Matrix<_MD> &y, const int refRow, const size_t fromCol, const size_t endCol);

Matrix<int> initArray(const int &startNum, const int &delta, const int &endNum);

template <typename _MD>         // repmat(MATRIX, n, m) /  repmat(double, n, m)
Matrix<_MD> repmat(const Matrix<_MD> &y, int n, int m);

// repmat(MATRIX, n, m) /  repmat(double, n, m)
Matrix<double> repmat(const double d, int n, int m);

Matrix<int> repmat(const int d, int n, int m);

template <typename _MD>
Matrix<_MD> transpose(const Matrix<_MD> &a);

//  unit MATRIX
template <typename _MD>
Matrix<_MD> I(const size_t &n);

template <typename _MD>
Matrix<_MD> matPow(Matrix<_MD> mat, int b);

/*
 * Matrix mat;
 * mat^(1/2)
 */
template <typename _MD>
Matrix<_MD> matRoot(const Matrix<_MD> &mat, double p);

/*  matrixSort : sort by column
 *  [ig,p] = sort(rp);    p : the same size with rp, p[i][j] : p[i][j]是rp矩阵j列的第几个
 */
template <typename _MD>
Matrix<int> matrixColSort(const Matrix<_MD> y);

template <typename _MD>
void colSort(int l, int r, commonStruct<_MD> *a);

/*
 * MATRIX x, MATRIX y , z = x(y)
 * the same size with y, z[i][j] is the y[i][j](th) number in x Matrix(column first)
 */
template <typename _MD>
Matrix<_MD> matBracket(const Matrix<_MD> &x, const Matrix<int> &y);

/*
 * t = [1,2,3; 4,5,6];  j = [2,2,2];
 * t(0,j) = [3,3,3];
 * t(1,j) = [6,6,6]
 * this function is to obtain t(i,j); when j is a matrix
 */
template <typename _MD>
Matrix<_MD> matRowBracket(const Matrix<_MD> &x, const int &i, const Matrix<int> &y);

template <typename _MD>
_MD getKthNumber(const Matrix<_MD> &mat, int k);

Matrix<double> randMatrix(const int n, const int m);

/*
 * change 1 to 0 / 0 to 1
 */
template <typename _MD>
Matrix<_MD> NOT(const Matrix<_MD> &y);

template <typename _MD>
std::ostream &operator<<(std::ostream &os, const Matrix<_MD> &mat);

template <typename _MD>
Matrix<_MD> inputMatrix(const size_t &n, const size_t &m, const _MD &type);

/*
 * randFixedSum
 */
template <typename _XD>
Matrix<double> randFixedSum(int n, int m, _XD S, _XD a, _XD b);

#endif //MPI_MOPSO_MATRIX_H
