#include "camera.h"
#include "vector.h"

using namespace std;

/*
 * Camera
 *     Inputs: None.
 *     Returns: None.
 *     Description: The default constructor for camera.
 *                  Applies initial settings for the object.
 */
Camera::Camera()
{
    Eye = Vector(0.0, 0.0, 0.25);
    Center = Vector(0.5, 0.5, 0.0);
    Up = Vector(0.0, 0.0, 1.0);

    Paused = false;
    Velocity = 0.003;
    PitchAngle = 0.02;
    RollAngle = 0.03;
    YawAngle = 0.03;
}

/*
 * Update
 *     Inputs: None.
 *     Returns: None.
 *     Description: Moves the camera forward.
 */
void Camera::Update()
{
    Eye.X += Velocity * Center.X;
    Eye.Y += Velocity * Center.Y;
    Eye.Z += Velocity * Center.Z;
}

/*
 * SpeedUp
 *     Inputs: None.
 *     Returns: None.
 *     Description: Increases the velocity member of the camera.
 *                  Resultantly speeding up the camera propogation.
 */
void Camera::SpeedUp()
{
    Velocity += 0.001;
}

/*
 * SlowDown
 *     Inputs: None.
 *     Returns: None.
 *     Description: Decreases the velocity member of the camera.
 *                  Resultantly slows down the camera propogation.
 *                  This method does allow velocity to become negative,
 *                  in which the camera will move in reverse.
 */
void Camera::SlowDown()
{
    Velocity -= 0.001;
}

/*
 * Roll
 *     Inputs: direction - Direction to roll, supports rolling left and right.
 *     Returns: None.
 *     Description: Rolls the camera by rotating the normal (Up) vector about the center axis.
 */
void Camera::Roll(int direction)
{
    if (direction == LEFT)
    {
        Up = Up.Rotate(Center, -RollAngle);
    }
    else if (direction == RIGHT)
    {
        Up = Up.Rotate(Center, RollAngle);
    }
}

/*
 * Pitch
 *     Inputs: direction - Direction to roll, supports pitching up and down.
 *     Returns: None.
 *     Description: Pitches the camera by modifying the center and normal (Up) vectors.
 *                  We need to adjust two vectors because unlike rolling, the center vector
 *                  changes in addition to the normal vector.
 */
void Camera::Pitch(int direction)
{
    if (direction == UP)
    {
        Center = Center.Rotate(Center.CrossProduct(Up), -PitchAngle);
        Up = Up.Rotate(Center.CrossProduct(Up), -PitchAngle);
    }
    else if (direction == DOWN)
    {
        Center = Center.Rotate(Center.CrossProduct(Up), PitchAngle);
        Up = Up.Rotate(Center.CrossProduct(Up), PitchAngle);
    }
}

/*
 * Yaw
 *     Inputs: direction - Direction to yaw, supports yaw left and right.
 *     Returns: None.
 *     Description: Steers the camera by rotating the center vector about the normal axis.
 */
void Camera::Yaw(int direction)
{
    if (direction == LEFT)
    {
        Center = Center.Rotate(Up, YawAngle);
    }
    else if (direction == RIGHT)
    {
        Center = Center.Rotate(Up, -YawAngle);
    }
}
