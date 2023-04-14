#ifndef AD_H
#define AD_H
#include "matrix.h"

using namespace std;

template <class T>
class AD
{
private:
    T f;
    vector<T> df;
    int id;
    int varcount;

public:
    AD()
    {
        f = 0;
        varcount = 0;
        id = -1;
    };
    AD(T fvalue, int idvalue, int varcountvalue)
    {
        f = fvalue;
        id = idvalue;
        varcount = varcountvalue;
        setdf();
    };
    AD(T fvalue, vector<T> dfvalue, int idvalue)
    {
        f = fvalue;
        id = idvalue;
        df = dfvalue;
    };
    void setdf()
    {
        for (int i = 0; i < varcount; i++)
        {
            if (i == id)
                df.push_back(1);
            else
                df.push_back(0);
        }
    };
    T getf()
    {
        return f;
    }
    vector<T> getdf()
    {
        return df;
    };
    T getDf(int index)
    {
        return df[index];
    }
    int getId()
    {
        return id;
    }

    AD<T> operator+(AD<T> g)
    {
        AD<T> h;
        h.f = f + g.f;
        for (int i = 0; i < df.size(); i++)
            h.df.push_back(df[i] + g.df[i]);
        return h;
    }
    AD<T> operator-(AD<T> g)
    {
        AD<T> h;
        h.f = f - g.f;
        for (int i = 0; i < df.size(); i++)
            h.df.push_back(df[i] - g.df[i]);
        return h;
    }
    AD<T> operator*(AD<T> g)
    {
        AD<T> h;
        h.f = f * g.f;
        for (int i = 0; i < df.size(); i++)
            h.df.push_back(f * g.df[i] + g.f * df[i]);
        return h;
    }

    AD<T> operator/(AD<T> g)
    {
        AD<T> h;
        h.f = f / g.f;
        for (int i = 0; i < df.size(); i++)
            h.df.push_back((g.f * df[i] - f * g.df[i]) / (g.f * g.f));
        return h;
    }

    AD<T> operator^(AD<T> g)
    {
        AD<T> h, H(f, df, id);
        H = g * Log(H);
        h.f = pow(f, g.f);
        for (int i = 0; i < df.size(); i++)
            h.df.push_back(h.f * H.df[i]);
        return h;
    }

    template <class U>
    friend AD<U> Sin(AD<U> g)
    {
        AD<U> h;
        h.f = sin(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(cos(g.f) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> Cos(AD<U> g)
    {
        AD<U> h;
        h.f = cos(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * sin(g.f) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> Tan(AD<U> g)
    {
        AD<U> h;
        h.f = tan(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back((1 / cos(g.f)) * (1 / cos(g.f)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> cot(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / tan(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * (1 / sin(g.f)) * (1 / sin(g.f)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> sec(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / cos(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(h.f * tan(g.f) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> cosec(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / sin(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * h.f * (1 / tan(g.f)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> arcsin(AD<U> g)
    {
        AD<U> h;
        h.f = asin(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back((1 / pow((1 - pow(g.f, 2)), 0.5)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> arccos(AD<U> g)
    {
        AD<U> h;
        h.f = acos(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * (1 / pow((1 - pow(g.f, 2)), 0.5)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> arctan(AD<U> g)
    {
        AD<U> h;
        h.f = atan(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back((1 / (pow(g.f, 2) + 1)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> arccot(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / atan(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * (1 / (pow(g.f, 2) + 1)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> arcsec(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / acos(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back((1 / (abs(g.f) * pow((pow(g.f, 2) - 1), 0.5))) * g.df[i]);
        return h;
    };
    ;
    template <class U>
    friend AD<U> arccosec(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / asin(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * (1 / (abs(g.f) * pow((pow(g.f, 2) - 1), 0.5))) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> Sinh(AD<U> g)
    {
        AD<U> h;
        h.f = sinh(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(cosh(g.f) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> Cosh(AD<U> g)
    {
        AD<U> h;
        h.f = cosh(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(sinh(g.f) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> Tanh(AD<U> g)
    {
        AD<U> h;
        h.f = tanh(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back((pow(1 / cosh(g.f), 2)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> coth(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / tanh(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * (pow(1 / sinh(g.f), 2)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> sech(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / cosh(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * h.f * tanh(g.f) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> cosech(AD<U> g)
    {
        AD<U> h;
        h.f = 1 / sinh(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(-1 * h.f * (1 / tanh(g.f)) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<T> Log(AD<U> g)
    {
        AD<T> h;
        h.f = log(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back((1 / g.f) * g.df[i]);
        return h;
    };
    template <class U>
    friend AD<U> Abs(AD<U> g)
    {
        AD<U> h;
        h.f = abs(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(abs(g.df[i]));
        return h;
    };
    template <class U>
    friend AD<U> Exp(AD<U> g)
    {
        AD<U> h;
        h.f = exp(g.f);
        for (int i = 0; i < g.df.size(); i++)
            h.df.push_back(h.f * g.df[i]);
        return h;
    };
    template <class U>
    friend matrix<U> getJacobian(vector<AD<U>> funList, int varcount)
    {
        int n = funList.size(), m = varcount;
        matrix<U> M(n, m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                AD<U> f = funList[i];
                M(i, j, f.getDf(j));
            }
        }
        return M;
    };
};

#endif