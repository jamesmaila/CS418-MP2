#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vector
{
    public:
        double X;
        double Y;
        double Z;

        Vector();
        Vector(double x, double y, double z);

        double Magnitude();
        void Normalize();
        Vector Rotate(Vector axis, double angle);
        double DotProduct(Vector b);
        Vector CrossProduct(Vector b);

        Vector & operator = (Vector rhs);
        Vector operator + (Vector rhs);
        Vector & operator += (Vector rhs);
        Vector operator - (Vector rhs);
        Vector & operator -= (Vector rhs);
};

#endif
