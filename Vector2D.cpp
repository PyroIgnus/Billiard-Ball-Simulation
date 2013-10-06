#include "Vector2D.h"

Vector2D::Vector2D()
{
    position[0] = 0;
    position[1] = 0;
}

Vector2D::Vector2D(float x, float y) {
    position[0] = x;
    position[1] = y;
}

Vector2D& Vector2D::operator=(Vector2D rhs) {
    if (this == &rhs) {
        return *this;
    }
    // Copy data into this vector
    position[0] = rhs.getX();
    position[1] = rhs.getY();
    return *this;
}

Vector2D& Vector2D::operator+(Vector2D rhs) {
    // Add data to this vector
    position[0] += rhs.getX();
    position[1] += rhs.getY();
    return *this;
}

Vector2D Vector2D::operator*(float rhs) {
    // Multiply values into this vector
    Vector2D result = Vector2D(rhs * position[0], rhs * position[1]);
    return result;
}

Vector2D Vector2D::operator-() {
    Vector2D v;
    v.setX(-position[0]);
    v.setY(-position[1]);
    return v;
}

bool Vector2D::operator==(Vector2D rhs) {
    if (rhs.getX() == position[0] && rhs.getY() == position[1]) {
        return true;
    }
    return false;
}

Vector2D Vector2D::normalize() {
    float mag = getMagnitude();
    Vector2D result = Vector2D(position[0] / mag, position[1] / mag);
    return result;
}

float Vector2D::dotProduct(Vector2D other) {
    float value = position[0] * other.getX() + position[1] * other.getY();
    return value;
}

float Vector2D::getDist(Vector2D v2) {
    float result = sqrt((position[0] - v2.getX())*(position[0] - v2.getX()) + (position[1] - v2.getY())*(position[1] - v2.getY()));
    return result;
}

float Vector2D::getX() {
    return position[0];
}

float Vector2D::getY() {
    return position[1];
}

Vector2D Vector2D::getPerpendicular(int type) {
    // Swap x and y values and reverse one of them based on type parameter.
    float temp;
    Vector2D result = *this;
    if (type) {
        temp = -result.getX();
        result.setX(result.getY());
        result.setY(temp);
    }
    else {
        temp = -result.getY();
        result.setY(result.getX());
        result.setX(temp);
    }
    return result;
}

void Vector2D::setX(float x) {
    position[0] = x;
}

void Vector2D::setY(float y) {
    position[1] = y;
}

float Vector2D::getMagnitude() {
    return sqrt(position[0] * position[0] + position[1] * position[1]);
}

void Vector2D::printVector() {
    printf("X: %f\nY: %f\n", position[0], position[1]);
}

Vector2D::~Vector2D()
{
    //dtor
}
