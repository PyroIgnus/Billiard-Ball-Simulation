#include "BilliardTable.h"

BilliardTable::BilliardTable()
{
    w = 0;
    h = 0;
    numActive = 0;
}

BilliardTable::BilliardTable(float w, float h) {
    this->w = w;
    this->h = h;
    // Apply default test initialization of table.
    numActive = 2;
    Ball b1 = *new Ball(1, 1, -5.0, 0);
    Ball b2 = *new Ball(8.0, 1, -5.0, 0);
    balls.push_back(b1);
    balls.push_back(b2);
}

bool BilliardTable::initialize(char* fileName) {
    FILE* file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        return false;
    }
    else {
        // Read values and initialize table values.
        char buff[100];
        int numArgs = 0;
        // First line contains width and height
        fgets(buff, 100, file);
        numArgs = sscanf(buff, "%f %f", &w, &h);
        if (numArgs != 2) {
            return false;
        }
        // Count and initialize the balls in this scenario.
        balls.clear();
        int numBalls = 0;
        while (fgets(buff, 100, file) != NULL) {
            float temp[4];
            numArgs = sscanf(buff, "%f %f %f %f", &temp[0], &temp[1], &temp[2], &temp[3]);
            // Extra arguments are ignored.
            if (numArgs != 4) {
                return false;
            }
            float temp2[4];
            for (int i = 0; i < 4; i++) {
                temp2[i] = temp[i];
            }
            Ball b = *new Ball(temp2[0], temp2[1], temp2[2], temp2[3]);
            balls.push_back(b);
            numBalls += 1;
        }
        numActive = numBalls;
        fclose(file);
        return true;
    }

    return false;
}

void BilliardTable::update() {
    // Iterate through combinations of existing balls and check for collisions.  Resolve if necessary.
    for (int i = 0; i < balls.size() - 1; i++) {
        for (int j = i + 1; j < balls.size(); j++) {
            if (isCollision(balls[i], balls[j])) {
                resolveCollision(&balls[i], &balls[j]);
            }
        }
    }
    // Iterate through all balls and update their positions based on their speeds.
    // Apply deceleration to balls as well.
    // Count number of currently active balls.
    int ballCounter = 0;
    for (int i = 0; i < balls.size(); i++) {
        balls[i].update(w, h);
        balls[i].decelerate();
        if (balls[i].getSpeed().getMagnitude() >= 0.05) {
            ballCounter += 1;
        }
    }

    // Update number of active balls.
    numActive = ballCounter;

}

bool BilliardTable::isCollision(Ball b1, Ball b2) {
    // Look for overlap of the two balls by performing a simple distance calculation.
    if (b1.distance(b2) < 2 * b1.getRadius()) {
        return true;
    }
    return false;
}

void BilliardTable::resolveCollision(Ball* b1, Ball* b2) {
    // Conversion/Separation of ball velocities into relative collision coordinates.
    // Normalized vectors of the collision axis and tangent axis.
    Vector2D axisColl = (b1->getPos() + (-b2->getPos())).normalize();
    Vector2D axisTang = axisColl;
    axisTang = axisTang.getPerpendicular(0);    // Tangent is perpendicular to collision axis.
    // Tangent components of the velocities.
    Vector2D compTang1 = axisTang * b1->getSpeed().dotProduct(axisTang); // Velocity of ball 1
    Vector2D compTang2 = axisTang * b2->getSpeed().dotProduct(axisTang); // Velocity of ball 2
    // Components of the velocities on the collision axis.
    // Since masses of the balls are equal, velocities are swapped.
    Vector2D compColl2 = axisColl * b1->getSpeed().dotProduct(axisColl); // Velocity of ball 2
    Vector2D compColl1 = axisColl * b2->getSpeed().dotProduct(axisColl); // Velocity of ball 1

    // Convert velocities back into the billiard table coordinate system (Cartesian).
    // Simply add the vectors back together, since they are already in the right coordinate system, but split into two components.
    Vector2D newSpeed1 = compTang1 + compColl1;
    b1->setSpeed(newSpeed1);
    Vector2D newSpeed2 = compTang2 + compColl2;
    b2->setSpeed(newSpeed2);

    // Separate balls to avoid any overlap.
    // Push ball 1 out of ball 2 for simplicity's sake.
    float separationDist = (2 * b1->getRadius()) - b1->distance(*b2);
    b1->setPos(b1->getPos() + axisColl * separationDist * 1.01);
}

float BilliardTable::getWidth() {
    return w;
}

float BilliardTable::getHeight() {
    return h;
}

int BilliardTable::getNumBalls() {
    return balls.size();
}

int BilliardTable::getNumActive() {
    return numActive;
}

Ball BilliardTable::getBall(int index) {
    return balls[index];
}

BilliardTable::~BilliardTable()
{
    //dtor
}
