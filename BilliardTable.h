#ifndef BILLIARDTABLE_H
#define BILLIARDTABLE_H

#include <vector>
#include "Ball.h"

class BilliardTable
{
    public:
        /** Default constructor */
        BilliardTable();
        BilliardTable(float w, float h);
        /** Functions */
        bool initialize(char* fileName);
        void update();  // Update balls and check and resolve collisions.
        bool isCollision(Ball b1, Ball b2);
        void resolveCollision(Ball* b1, Ball* b2);
        /** Get Functions */
        float getWidth();
        float getHeight();
        int getNumBalls();
        int getNumActive();
        Ball getBall(int index);
        /** Default destructor */
        virtual ~BilliardTable();
    protected:
    private:
        float w, h; // Width and height of table.
        std::vector<Ball> balls;
        int numActive;  // Number of balls still moving.

};

#endif // BILLIARDTABLE_H
