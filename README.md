# Jacobian-matrix-generator
 Input: Takes n dimension function and variables as input along with the point(vector) at which the jacobian is to be calculated.
 
 Output: outputs the jacobian matrix along with its determinant.

General form of the function:
 
 f:Rn->Rm
 
 f(x1, x2, x3, ..., xn) = (f1, f2, f3, ..., fm)
 
 n = dimension of domain
 
 m = dimension of co-domain
 
 variables = {x1, x2, x3, ..., xn}
 
 vector components = {f1, f2, f3, ..., fm}
 
 order of jacobian matrix = m * n

Jacobian matrix:

    | df1/dx1 df1/dx2 ... df1/dxn |
    | df2/dx1 df2/dx2 ... df2/dxn |
    | .       .       ... .       |
    | .       .       ... .       |
    | dfm/dx1 dfm/dx2 ... dfm/dxn | m * n
     
Example1:
 
 fuction: f(x) = sin(cos(x)*sin(x))+1
 
 Enter the dimension of the domain: 1
 
 Enter the dimension of the codomain: 1
 
 Enter the function: sin(sin(x)*cos(x))+1
 
 Enter the variables symbols: x
 
 Enter the point: 1
 
 Jacobian matrix:
 
    -0.373873
 
 Determinant of the Jacobian matrix: -0.373873
 
Example2:
 
 function: f(x, y) = (x^4+3*y^2*x, 5*y^2-2*x*y+1)
 
 Enter the dimension of the domain: 2
 
 Enter the dimension of the codomain: 2
 
 Enter the function f1: x^4+3*y^2*x
 
 Enter the function f2: 5*y^2-2*x*y+1
 
 Enter the variables symbols: x y
 
 Enter the point: 1 2
 
 Jacobian matrix:
 
    16 12 
    -4 18 
 
 Determinant of the Jacobian matrix: 336
