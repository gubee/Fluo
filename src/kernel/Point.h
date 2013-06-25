/*
 * Point.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef POINT_H_
#define POINT_H_

#include <math.h>
#include "util.h"

struct Point {
    float x;
    float y;

    Point()
        : x(0), y(0)
    {
    }

    Point(const float& x, const float& y)
        : x(x), y(y)
    {
    }

    Point& reset(float x, float y) {
        this->x = x;
        this->y = y;
        return *this;
    }

    bool equals(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool notEquals(const Point& other) const {
        return x != other.y || y != other.y;
    }

    Point clone() const {
        return Point(x, y);
    }

    bool empty() const {
        return x == 0 || y == 0;
    }

    Point& add(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point added(const Point& other) const {
        return clone().add(other);
    }

    Point& subtract(const Point& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Point subtracted(const Point& other) const {
        return clone().subtract(other);
    }

    Point& multiply(float value) {
        x *= value;
        y *= value;
        return *this;
    }

    Point multiplied(float value) const {
        return clone().multiply(value);
    }

    Point& divide(float value) {
        x /= value;
        y /= value;
        return *this;
    }

    Point divided(float value) const {
        return clone().divide(value);
    }

    float dot(const Point& other) const {
        return x * other.x + y * other.y;
    }

    float manhattanLength() const {
        return abs(x) + abs(y);
    }

    bool compare(const Point& other) const {
        return fuzzyIsNull(x - other.x) &&
            fuzzyIsNull(y - other.y);
    }
};

#endif /* POINT_H_ */
