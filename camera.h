#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "vector.h"

#define LEFT 0
#define RIGHT 1
#define DOWN 2
#define UP 3

class Camera
{
    public:
        Vector Eye;
        Vector Center;
        Vector Up;

        bool Paused;
        float Velocity;
        float PitchAngle;
        float RollAngle;
        float YawAngle;

        Camera();
        void Update();
        void SpeedUp();
        void SlowDown();
        void Roll(int direction);
        void Pitch(int direction);
        void Yaw(int direction);
};

#endif
