#include "Ball.h"

Ball::Ball()
{
    radius = RADIUS;
    pos = Vector2D();
    speed = Vector2D();
}

Ball::Ball(float x, float y) {
    radius = RADIUS;
    pos = Vector2D(x, y);
    speed = Vector2D();
}

Ball::Ball(float x, float y, float vx, float vy) {
    radius = RADIUS;
    pos = Vector2D(x, y);
    speed = Vector2D(vx, vy);
}

void Ball::update(float w, float h) {
    // Update speed based on TIME_STEP.
    pos = pos + (speed * TIME_STEP);
    // Check for collisions with walls and reflect speed accordingly.
    if (pos.getX() + RADIUS > w || pos.getX() - RADIUS < 0) {
        speed.setX(-speed.getX());
        // Remember to "push" ball out of the wall as well.
        if (pos.getX() - RADIUS < 0) {
            pos.setX(RADIUS);
        }
        if (pos.getX() + RADIUS > w) {
            pos.setX(w - RADIUS);
        }
    }
    if (pos.getY() + RADIUS > h || pos.getY() - RADIUS < 0) {
        speed.setY((-speed.getY()));
        // Remember to "push" ball out of the wall as well.
        if (pos.getY() - RADIUS < 0) {
            pos.setY(RADIUS);
        }
        if (pos.getY() + RADIUS < w) {
            pos.setY(w - RADIUS);
        }
    }
}

void Ball::decelerate() {
    // Decrease speed based on DRAG factor and TIME_STEP.
    float change = DRAG * TIME_STEP;
    // If speed is low enough, then set to 0.  Else decrease speed.
    if (speed.getMagnitude() < 0.05) {
        speed.setX(0);
        speed.setY(0);
    }
    else {
        speed = speed * (1 - (change / speed.getMagnitude()));
    }
}

float Ball::distance(Ball b2) {
    float result = pos.getDist(b2.getPos());
    return result;
}

float Ball::getRadius() {
    return radius;
}

Vector2D Ball::getPos() {
    return pos;
}

Vector2D Ball::getSpeed() {
    return speed;
}

void Ball::setPos(Vector2D newPos) {
    pos = newPos;
}

void Ball::setSpeed(Vector2D newSpeed) {
    speed = newSpeed;
}

Ball::~Ball()
{
    //dtor
}
