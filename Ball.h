#ifndef BALL_H
#define BALL_H

#include <stdio.h>
#include "utils.h"
#include "Vector2D.h"

class Ball
{
    public:
        /** Default constructor */
        Ball();
        Ball(float x, float y);
        Ball(float x, float y, float vx, float vy);
        /** Functions */
        void update(float w, float h);
        void decelerate();
        float distance(Ball b2);
        /** Get Functions */
        float getRadius();
        Vector2D getPos();
        Vector2D getSpeed();
        /** Set Functions */
        void setPos(Vector2D newPos);
        void setSpeed(Vector2D newSpeed);
        /** Default destructor */
        virtual ~Ball();
    protected:
    private:
        float radius;
        Vector2D pos;
        Vector2D speed;   // X and Y components of the speed.
};

#endif // BALL_H
