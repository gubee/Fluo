/*
 * Point.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#include "util.h"

struct Point {
    float x;
    float y;

    Point();
    Point(float x, float y);
    Point(const Point& p);

    inline float manhattanLength() const;
};

inline Point::Point() : x(0.0f), y(0.0f) { }

inline Point::Point(float x, float y) : x(x), y(y) { }

inline Point::Point(const Point& p) : x(p.x), y(p.y) { }

inline float Point::manhattanLength() const
{
    return std::abs(x) + std::abs(y);
}

#endif /* POINT_H_ */
