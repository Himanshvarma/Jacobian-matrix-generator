#include "Expression.h"

int main()
{
    int domain_dim, codomain_dim;
    cout << "Enter the dimension of the domain: ";
    cin >> domain_dim;
    cout << "Enter the dimension of the codomain: ";
    cin >> codomain_dim;

    Expression expression[codomain_dim];
    for (int i = 0; i < codomain_dim; i++)
    {
        codomain_dim == 1 ? cout << "Enter the function: " : cout << "Enter the function f" << i + 1 << ": ";
        string s;
        cin >> s;
        expression[i] = Expression(s, domain_dim);
    }

    char var[domain_dim];
    cout << "Enter the variables symbols: ";
    for (int i = 0; i < domain_dim; i++)
        cin >> var[i];

    vector<AD<double>> point;
    cout << "Enter the point: ";
    for (int i = 0; i < domain_dim; i++)
    {
        int val;
        cin >> val;
        AD<double> x(val, i, domain_dim);
        point.push_back(x);
    }
    unordered_map<char, AD<double>> varvalues;
    for (int i = 0; i < domain_dim; i++)
        varvalues[var[i]] = point[i];

    vector<AD<double>> funList;
    for (int i = 0; i < codomain_dim; i++)
        funList.push_back(expression[i].evaluate(varvalues));

    matrix<double> Jacobian = getJacobian(funList, domain_dim);
    cout << "Jacobian matrix:" << endl;
    Jacobian.print();
    cout << "Determinant of the Jacobian matrix: ";
    cout << Jacobian.det() << endl;
    return 0;
}