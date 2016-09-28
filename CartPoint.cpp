#include "CartPoint.h"
#include <cmath>

CartPoint::CartPoint()
{
    x=0;
    y=0;
}

CartPoint::CartPoint(double in_x, double in_y)
{
    x=in_x;
    y=in_y;
}


ostream& operator<<(ostream& stream, const CartPoint& p1)
{
    stream<<"("<<p1.x<<", "<<p1.y<<")";
    return stream;
}

CartPoint operator+(const CartPoint& p1, const CartVector& v1)
{
    double resultx=p1.x+v1.x;
    double resulty=p1.y+v1.y;
    return CartPoint(resultx,resulty);
    
}

CartVector operator-(const CartPoint& p1, const CartPoint& p2)
{
    double resultx=p1.x-p2.x;
    double resulty=p1.y-p2.y;
    return CartVector(resultx,resulty);
    
}

double cart_distance(CartPoint p1, CartPoint p2)
{
    double distx= p1.x-p2.x;
    double disty=p1.y-p2.y;
    double dist=sqrt(pow(distx,2)+pow(disty,2));
    return dist;
}

bool cart_compare(CartPoint p1, CartPoint p2)
{
    if (p1.x==p2.x && p1.y==p2.y)
    {
        return true; 
    }
    else
        return false;
}