#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vector
{
    public:
        float X;
        float Y;
        float Z;

        Vector();
        Vector(float x, float y, float z);

        float Magnitude();
        void Normalize();
        Vector Rotate(Vector axis, float angle);
        float DotProduct(Vector b);
        Vector CrossProduct(Vector b);

        Vector & operator = (Vector rhs);
};

#endif
