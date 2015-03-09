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
Vector::Vector(double x, double y, double z)
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
double Vector::Magnitude()
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
    double magnitude = Magnitude();

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
Vector Vector::Rotate(Vector axis, double angle)
{
    double length = axis.Magnitude();
    double lengthSquared = pow(length, 2);
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    double x = (axis.X*((axis.X*X)+(axis.Y*Y)+(axis.Z*Z)))*(1-cosAngle) 
                + (lengthSquared*X*cosAngle) 
                + (length*(-axis.Z*Y+axis.Y*Z)*sinAngle);

    double y = (axis.Y*((axis.X*X)+(axis.Y*Y)+(axis.Z*Z)))*(1-cosAngle)
                + (lengthSquared*Y*cosAngle) 
                + (length*(axis.Z*X-axis.X*Z)*sinAngle);

    double z = (axis.Z*((axis.X*X)+(axis.Y*Y)+(axis.Z*Z)))*(1-cosAngle)
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
    double x = Y*b.Z - Z*b.Y;
    double y = -(X*b.Z - Z*b.X);
    double z = X*b.Y - Y*b.X;

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

/*
 * Operator +
 *     Inputs: rhs - Vector to add.
 *     Returns: None.
 *     Description: Overloaded addition operator.
 */
Vector Vector::operator + (Vector rhs)
{
	Vector result;

	result.X = X + rhs.X;
	result.Y = Y + rhs.Y;
	result.Z = Z + rhs.Z;

	return result;
}

/*
 * Operator +=
 *     Inputs: rhs - Vector to add to self.
 *     Returns: None.
 *     Description: Overloaded plus equal operator.
 */
Vector & Vector::operator += (Vector rhs)
{
    X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;

    return *this;
}


Vector Vector::operator - (Vector rhs)
{
    Vector result;

    result.X = X - rhs.X;
    result.Y = Y - rhs.Y;
    result.Z = Z - rhs.Z;

    return result;
}


Vector & Vector::operator -= (Vector rhs)
{
    X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;

    return *this;
}