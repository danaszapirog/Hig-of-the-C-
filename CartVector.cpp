#include "CartVector.h"

CartVector::CartVector()
{
    x=0.0;
    y=0.0;
}

CartVector::CartVector(double in_x, double in_y)
{
    x=in_x;
    y=in_y;
}

ostream& operator<<(ostream& stream, const CartVector& v1)
{
    stream<<"<"<<v1.x<<", "<<v1.y<<">";
    return stream;
}

CartVector operator*(const CartVector& v1, const int d)
{
    double resultx= v1.x*d;
    double resulty = v1.y*d;
    return CartVector(resultx,resulty);
}

CartVector operator/(const CartVector& v1, const int d)
{
    if (d==0)
    {
        return v1;
    }
    double resultx= v1.x/d;
    double resulty = v1.y/d;
    return CartVector(resultx,resulty);
}