/*
 * Rect.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef RECT_H_
#define RECT_H_

#include "Util.h"
#include "Point.h"

struct Rect {
    float x;
    float y;
    float width;
    float height;

    Rect()
        : x(0), y(0), width(0), height(0)
    {
    }

    Rect(const float& x, const float& y, const float& width, const float& height)
        : x(x), y(y), width(width), height(height)
    {
    }

    inline Rect clone() const;
    inline bool empty() const;

    inline float left() const;
    inline float right() const;
    inline float top() const;
    inline float bottom() const;

    inline Rect& adjust(float x1, float y1, float x2, float y2);
    inline Rect adjusted(float x1, float y1, float x2, float y2) const;

    bool intersects(const Rect& other) const;
    inline Rect intersected(const Rect& other) const;
    Rect& unite(const Rect& other);
    inline Rect united(const Rect& other) const;
    Rect& align();
    inline Rect aligned() const;
    Rect& normalize();
    inline Rect normalized() const;

    bool contains(const Rect& rect, bool proper = false);
    bool contains(const Point& point, bool proper = false);

    inline Rect& moveCenter(const Point& point);

    Rect operator|(const Rect& r) const;
    Rect operator&(const Rect& r) const;
    inline Rect& operator|=(const Rect& r);
    inline Rect& operator&=(const Rect& r);

    friend inline bool operator==(const Rect&, const Rect&);
    friend inline bool operator!=(const Rect&, const Rect&);
};

inline Rect Rect::clone() const {
    return Rect(x, y, width, height);
}

inline bool Rect::empty() const {
    return width == 0 || height == 0;
}

inline float Rect::left() const {
    return x;
}

inline float Rect::right() const {
    return x + width;
}

inline float Rect::top() const {
    return y;
}

inline float Rect::bottom() const {
    return y + height;
}

inline Rect Rect::adjusted(float x1, float y1, float x2, float y2) const {
    return clone().adjust(x1, y1, x2, y2);
}

inline Rect Rect::intersected(const Rect &r) const {
    return *this & r;
}

inline Rect Rect::aligned() const {
    return clone().align();
}

inline Rect Rect::united(const Rect& other) const {
    return clone().unite(other);
}

inline Rect Rect::normalized() const {
    return clone().normalize();
}

inline Rect& Rect::moveCenter(const Point& point) {
    x = point.x - width / 2;
    y = point.y - height / 2;
    return *this;
}

inline Rect& Rect::operator|=(const Rect &r)
{
    *this = *this | r;
    return *this;
}

inline Rect& Rect::operator&=(const Rect &r)
{
    *this = *this & r;
    return *this;
}

inline bool operator==(const Rect& r1, const Rect& r2) {
    return fuzzyCompare(r1.x, r2.x) && fuzzyCompare(r1.y, r2.y)
        && fuzzyCompare(r1.width, r2.width) && fuzzyCompare(r1.height, r2.height);
}

inline bool operator!=(const Rect& r1, const Rect& r2) {
    return !fuzzyCompare(r1.x, r2.x) || !fuzzyCompare(r1.y, r2.y)
        || !fuzzyCompare(r1.width, r2.width) || !fuzzyCompare(r1.height, r2.height);
}

#endif /* RECT_H_ */
