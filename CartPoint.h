#ifndef CARTPOINT_H
#define CARTPOINT_H
#include <iostream>
#include "CartVector.h"
using namespace std;
#include <iomanip> 

class CartPoint
{
public:
    double x;
    double y;
    CartPoint();
    CartPoint(double, double);
    
};

double cart_distance(CartPoint, CartPoint);
bool cart_compare(CartPoint, CartPoint);

ostream& operator<<(ostream& stream, const CartPoint& p1);

CartPoint operator+(const CartPoint& p1, const CartVector& v1);
CartVector operator-(const CartPoint& p1, const CartPoint& p2);

#endif