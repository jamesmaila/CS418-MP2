#include "vector.h"

using namespace std;

/*
 * Vector
 *     Inputs: None.
 *     Returns: None.
 *     Description: The default constructor for camera.
 *                  Sets X,Y,Z coordinates to (0,0,0).
 */
Vector::Vector()
{
    X = 0.0;
    Y = 0.0;
    Z = 0.0;
}

/*
 * Vector
 *     Inputs: x - X coordinate to apply.
 *             y - Y coordinate to apply.
 *             z - Z coordinate to apply.
 *     Returns: None.
 *     Description: The non-default constructor for camera.
 *                  Sets the vector's position to given coordinates.
 */
Vector::Vector(float x, float y, float z)
{
    X = x;
    Y = y;
    Z = z;
}

/*
 * Magnitude
 *     Inputs: None.
 *     Returns: The magnitude of the vector.
 *     Description: Finds the magnitude of the vector.
 */
float Vector::Magnitude()
{
    return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
}

/*
 * Normalize
 *     Inputs: None.
 *     Returns: None.
 *     Description: Normalizes the vector.
 */
void Vector::Normalize()
{
    float magnitude = Magnitude();

    X /= magnitude;
    Y /= magnitude;
    Z /= magnitude;
}

/*
 * Rotate
 *     Inputs: axis - Vector to rotate about.
 *             angle - Angle amount to rotate.
 *     Returns: The rotated vector.
 *     Description: This method rotates a vector a given amount about a given axis.
 *                  I obtained this formula was obtained from:
 *                      "http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation"
 *                  This is the main mechanism from which we move the camera.
 *                   
 */
Vector Vector::Rotate(Vector axis, float angle)
{
    float length = axis.Magnitude();
    float lengthSquared = pow(length, 2);
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);

    float x = (axis.X*((axis.X*X)+(axis.Y*Y)+(axis.Z*Z)))*(1-cosAngle) 
                + (lengthSquared*X*cosAngle) 
                + (length*(-axis.Z*Y+axis.Y*Z)*sinAngle);

    float y = (axis.Y*((axis.X*X)+(axis.Y*Y)+(axis.Z*Z)))*(1-cosAngle)
                + (lengthSquared*Y*cosAngle) 
                + (length*(axis.Z*X-axis.X*Z)*sinAngle);

    float z = (axis.Z*((axis.X*X)+(axis.Y*Y)+(axis.Z*Z)))*(1-cosAngle)
                + (lengthSquared*Z*cosAngle) 
                + (length*(-axis.Y*X+axis.X*Y)*sinAngle);

    x /= lengthSquared;
    y /= lengthSquared;
    z /= lengthSquared;
    
    return Vector(x, y, z);
}

/*
 * CrossProduct
 *     Inputs: b - Vector to cross product with.
 *     Returns: The resultant vector of this cross b.
 *     Description: Takes a cross product of two vectors.
 */
Vector Vector::CrossProduct(Vector b)
{
    float x = Y*b.Z - Z*b.Y;
    float y = -(X*b.Z - Z*b.X);
    float z = X*b.Y - Y*b.X;

    return Vector(x, y, z);
}

/*
 * Operator =
 *     Inputs: rhs - Vector to set this vector equal to.
 *     Returns: None.
 *     Description: Overloaded equals operator.
 */
Vector & Vector::operator = (Vector rhs)
{
    X = rhs.X;
    Y = rhs.Y;
    Z = rhs.Z;

    return *this;
}
