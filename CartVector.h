#ifndef CARTVECTOR_H
#define CARTVECTOR_H
#include <iostream>
using namespace std;
#include <iomanip> 

class CartVector
{
public:
    double x; 
    double y;
    CartVector();
    CartVector(double, double);
};

CartVector operator*(const CartVector& v1, const int d);
CartVector operator/(const CartVector& v1, const int d);
ostream& operator<<(ostream& stream, const CartVector& v1);
#endif