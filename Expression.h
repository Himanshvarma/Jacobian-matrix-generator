#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "AD.h"

class Expression
{
private:
    string infix_Expression, postfix_Expression;
    int varcount = 0;
    unordered_map<int, AD<double>> values;
    int values_count = 0;

public:
    Expression()
    {
        infix_Expression = "\0";
        postfix_Expression = "\0";
    };
    Expression(string Expression, int varcountvalue)
    {
        infix_Expression = Expression;
        varcount = varcountvalue;
        postfix_Expression = "\0";
    }
    int InStackPrecedence(char);
    int OutStackPrecedence(char);
    void infix_to_postfix();
    void convert();
    AD<double> evaluate(unordered_map<char, AD<double>> &);
};

int Expression::InStackPrecedence(char ch)
{
    if (ch == '(')
        return 0;
    else if (ch == '+' || ch == '-')
        return 2;
    else if (ch == '*' || ch == '/')
        return 4;
    else if (ch == '^')
        return 5;
    return -1;
}

int Expression::OutStackPrecedence(char ch)
{
    if (ch == '(')
        return 100;
    else if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 3;
    else if (ch == '^')
        return 6;
    return -1;
}

void Expression::infix_to_postfix()
{
    stack<char> st;
    int size = infix_Expression.size();
    for (int i = 0; i < size; i++)
    {
        if (isalnum(infix_Expression[i]))
            postfix_Expression.push_back(infix_Expression[i]);
        else
        {
            while (!st.empty() && InStackPrecedence(st.top()) > OutStackPrecedence(infix_Expression[i]))
            {
                if (postfix_Expression[postfix_Expression.size() - 1] != ' ')
                    postfix_Expression.push_back(' ');
                postfix_Expression.push_back(st.top());
                st.pop();
            }
            if (postfix_Expression[postfix_Expression.size() - 1] != ' ')
                postfix_Expression.push_back(' ');
            st.push(infix_Expression[i]);
        }
    }
    while (!st.empty())
    {
        if (postfix_Expression[postfix_Expression.size() - 1] != ' ')
            postfix_Expression.push_back(' ');
        postfix_Expression.push_back(st.top());
        st.pop();
    }
}

void Expression::convert()
{
    for (int i = 0; i < infix_Expression.size(); i++)
    {
        if (infix_Expression[i] == '!')
        {
            infix_Expression = infix_Expression.substr(0, i) + infix_Expression.substr(i + 1);
            while (infix_Expression[i] != '!')
                i++;
            infix_Expression = infix_Expression.substr(0, i) + infix_Expression.substr(i + 1);
        }
        if (isdigit(infix_Expression[i]))
        {
            int s = i;
            double num = 0;
            while (i < infix_Expression.size() && isdigit(infix_Expression[i]))
            {
                num *= 10;
                num += (int)(infix_Expression[i] - '0');
                i++;
            }
            if (i < infix_Expression.size() && infix_Expression[i] == '.')
            {
                i++;
                double dec = 10;
                while (i < infix_Expression.size() && isdigit(infix_Expression[i]))
                {
                    num += ((infix_Expression[i] - '0') / dec);
                    dec *= 10;
                    i++;
                }
            }
            AD<double> c(num, -1, varcount);
            values[values_count] = c;
            infix_Expression = infix_Expression.substr(0, s) + to_string(values_count) + infix_Expression.substr(i);
            i = s + to_string(values_count).size() - 1;
            values_count++;
        }
    }
}

AD<double> Expression::evaluate(unordered_map<char, AD<double>> &varvalues)
{
    for (int i = 0; i < infix_Expression.size(); i++)
    {
        if (infix_Expression[i] == '(')
        {
            string operation = "\0", operand = "\0";
            int s = i - 1, e = i + 1;
            while (s >= 0 && isalpha(infix_Expression[s]))
                operation = infix_Expression[s--] + operation;

            int count = 1;
            while (e < infix_Expression.size() && count)
            {
                if (infix_Expression[e] == '(')
                    count++;
                else if (infix_Expression[e] == ')')
                    count--;
                e++;
            }
            operand = infix_Expression.substr(i + 1, (e - i - 2));
            Expression newExpression(operand, varcount);

            if (operation == "\0")
                values[values_count] = newExpression.evaluate(varvalues);
            else if (operation == "sin")
                values[values_count] = Sin(newExpression.evaluate(varvalues));
            else if (operation == "cos")
                values[values_count] = Cos(newExpression.evaluate(varvalues));
            else if (operation == "tan")
                values[values_count] = Tan(newExpression.evaluate(varvalues));
            else if (operation == "cot")
                values[values_count] = cot(newExpression.evaluate(varvalues));
            else if (operation == "sec")
                values[values_count] = sec(newExpression.evaluate(varvalues));
            else if (operation == "cosec")
                values[values_count] = cosec(newExpression.evaluate(varvalues));
            else if (operation == "sinh")
                values[values_count] = Sinh(newExpression.evaluate(varvalues));
            else if (operation == "cosh")
                values[values_count] = Cosh(newExpression.evaluate(varvalues));
            else if (operation == "tanh")
                values[values_count] = Tanh(newExpression.evaluate(varvalues));
            else if (operation == "coth")
                values[values_count] = coth(newExpression.evaluate(varvalues));
            else if (operation == "sech")
                values[values_count] = sech(newExpression.evaluate(varvalues));
            else if (operation == "cosech")
                values[values_count] = cosech(newExpression.evaluate(varvalues));
            else if (operation == "arcsin")
                values[values_count] = arcsin(newExpression.evaluate(varvalues));
            else if (operation == "arccos")
                values[values_count] = arccos(newExpression.evaluate(varvalues));
            else if (operation == "arctan")
                values[values_count] = arctan(newExpression.evaluate(varvalues));
            else if (operation == "arccot")
                values[values_count] = arccot(newExpression.evaluate(varvalues));
            else if (operation == "arcsec")
                values[values_count] = arcsec(newExpression.evaluate(varvalues));
            else if (operation == "arccosec")
                values[values_count] = arccosec(newExpression.evaluate(varvalues));
            else if (operation == "exp")
                values[values_count] = Exp(newExpression.evaluate(varvalues));
            else if (operation == "log")
                values[values_count] = Log(newExpression.evaluate(varvalues));
            else if (operation == "abs")
                values[values_count] = Abs(newExpression.evaluate(varvalues));

            infix_Expression = infix_Expression.substr(0, s + 1) + "!" + to_string(values_count) + "!" + infix_Expression.substr(e);
            i = s + to_string(values_count).size() + 2;
            values_count++;
        }
    }

    convert();
    infix_to_postfix();
    stack<AD<double>> adst;
    int size = postfix_Expression.size();
    for (int i = 0; i < size; i++)
    {
        if (postfix_Expression[i] != ' ')
        {
            if (isdigit(postfix_Expression[i]))
            {
                int num = 0;
                while (i < size && isdigit(postfix_Expression[i]))
                {
                    num *= 10;
                    num += (int)(postfix_Expression[i] - '0');
                    i++;
                }
                i--;
                adst.push(values[num]);
            }
            else if (isalpha(postfix_Expression[i]))
                adst.push(varvalues[postfix_Expression[i]]);
            else
            {
                AD<double> a, b;
                b = adst.top();
                adst.pop();
                a = adst.top();
                adst.pop();
                switch (postfix_Expression[i])
                {
                case '*':
                    adst.push(a * b);
                    break;
                case '/':
                    adst.push(a / b);
                    break;
                case '+':
                    adst.push(a + b);
                    break;
                case '-':
                    adst.push(a - b);
                    break;
                case '^':
                    adst.push(a ^ b);
                    break;
                default:
                    break;
                }
            }
        }
    }
    return adst.top();
}

#endif
