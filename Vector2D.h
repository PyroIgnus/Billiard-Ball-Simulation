#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#include "utils.h"

class Vector2D
{
    public:
        /** Default constructor */
        Vector2D();
        Vector2D(float x, float y);
        /** Operators */
        Vector2D& operator=(Vector2D rhs);
        Vector2D& operator+(Vector2D rhs);
        Vector2D operator*(float rhs);
        Vector2D operator-();
        bool operator==(Vector2D rhs);
        /** Mathematical functions */
        Vector2D normalize();
        float dotProduct(Vector2D other);
        float getDist(Vector2D v2);
        /** Get functions */
        float getX();
        float getY();
        float getMagnitude();
        Vector2D getPerpendicular(int type);
        /** Set functions */
        void setX(float x);
        void setY(float y);
        /** Miscellaneous Functions */
        void printVector();
        /** Default destructor */
        virtual ~Vector2D();
    protected:
    private:
        float position[2];
};

#endif // VECTOR2D_H
