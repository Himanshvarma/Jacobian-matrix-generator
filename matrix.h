#ifndef MATRIX_H
#define MATRIX_H
#include <bits/stdc++.h>

using namespace std;

template <class T>
class matrix
{
private:
    T **M;
    int num_row, num_col;

public:
    matrix()
    {
        num_row = 0;
        num_col = 0;
    };
    matrix(int rows, int cols)
    {
        num_row = rows;
        num_col = cols;
        M = new T *[num_row];
        for (int i = 0; i < num_row; i++)
            M[i] = new T[num_col];
    };
    int getrow()
    {
        return num_row;
    };
    int getcol()
    {
        return num_col;
    };
    T minor(int I, int J)
    {
        matrix<T> mr(num_row - 1, num_col - 1);
        int k = 0, l = 0;
        for (int i = 0; i < num_row; i++)
        {
            if (i != I)
            {
                for (int j = 0; j < num_col; j++)
                {
                    if (j != J)
                    {
                        mr(k, l, M[i][j]);
                        l++;
                    }
                }
                k++;
                l = 0;
            }
        }
        return mr.det();
    };
    T cofactor(int I, int J)
    {
        return this->minor(I, J) * pow(-1, (I + J));
    };
    T det()
    {
        if (num_row != num_col)
        {
            cout << "Determinant calculation is not possible." << endl;
            exit(0);
        }

        if (num_row == 1 && num_col == 1)
            return M[0][0];

        T d = 0;
        for (int i = 0; i < num_col; i++)
            d += (M[0][i] * this->cofactor(0, i));
        return d;
    };
    matrix<T> cofactorMartix()
    {
        matrix<T> cm(num_row, num_col);
        for (int i = 0; i < num_row; i++)
            for (int j = 0; j < num_col; j++)
                cm(i, j, this->cofactor(i, j));
        return cm;
    };

    T operator()(int row, int col)
    {
        if (row < num_row && col < num_col)
            return M[row][col];
        else
        {
            cout << "ERROR: Out of bound" << endl;
            exit(0);
        }
    };
    void operator()(int row, int col, T val)
    {
        if (row < num_row && col < num_col)
            M[row][col] = val;
        else
        {
            cout << "ERROR: Out of bound" << endl;
            exit(0);
        }
    };

    template <class U>
    matrix<double> operator*(U val)
    {
        matrix<double> m(num_row, num_col);
        for (int i = 0; i < num_row; i++)
            for (int j = 0; j < num_col; j++)
                m(i, j, M[i][j] * val);
        return m;
    };

    template <class U>
    matrix<double> operator*(matrix<U> N)
    {
        if (num_col == N.getrow())
        {
            matrix<double> m(num_row, N.getcol());
            for (int i = 0; i < m.getrow(); i++)
            {
                for (int j = 0; j < m.getcol(); j++)
                {
                    double s = 0;
                    for (int k = 0; k < num_col; k++)
                        s += (M[i][k] * N(k, j));
                    m(i, j, s);
                }
            }
            return m;
        }
        else
        {
            cout << "Matrix multiplication error" << endl;
            exit(0);
        }
    };

    template <class U>
    matrix<double> operator+(matrix<U> N)
    {
        if (num_col == N.getcol() && num_row == N.getrow())
        {
            matrix<double> m(num_row, num_col);
            for (int i = 0; i < m.getrow(); i++)
                for (int j = 0; j < m.getcol(); j++)
                    m(i, j, (M[i][j] + N(i, j)));
            return m;
        }
        else
        {
            cout << "Matrix addition error" << endl;
            exit(0);
        }
    };

    template <class U>
    matrix<double> operator-(matrix<U> N)
    {
        if (num_col == N.getcol() && num_row == N.getrow())
        {
            matrix<double> m(num_row, num_col);
            for (int i = 0; i < m.getrow(); i++)
                for (int j = 0; j < m.getcol(); j++)
                    m(i, j, (M[i][j] - N(i, j)));
            return m;
        }
        else
        {
            cout << "Matrix subtraction error" << endl;
            exit(0);
        }
    };

    void print()
    {
        for (int i = 0; i < num_row; i++)
        {
            for (int j = 0; j < num_col; j++)
                cout << M[i][j] << " ";
            cout << endl;
        }
    };
};

#endif