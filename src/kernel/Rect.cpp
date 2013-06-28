/*
 * Rect.cpp
 *
 *  Created on: 2013. 6. 27.
 *      Author: impaulkim
 */

#include "Rect.h"

#include <cmath>
#include <algorithm>
#include "point.h"



Rect& Rect::adjust(float x1, float y1, float x2, float y2) {
    x += x1;
    y += y1;
    width += (x2 - x1);
    height += (y2 - y1);
    return *this;
}


bool Rect::intersects(const Rect& other) const
{
    float left1 = x;
    float right1 = x;
    if (width < 0)
        left1 += width;
    else
        right1 += width;
    if (left1 == right1) // null rect
        return false;

    float left2 = other.x;
    float right2 = other.x;
    if (other.width < 0)
        left2 += other.width;
    else
        right2 += other.width;
    if (left2 == right2) // null rect
        return false;

    if (left1 >= right2 || left2 >= right1)
        return false;

    float top1 = y;
    float bottom1 = y;
    if (height < 0)
        top1 += height;
    else
        bottom1 += height;
    if (top1 == bottom1) // null rect
        return false;

    float top2 = other.y;
    float bottom2 = other.y;
    if (other.height < 0)
        top2 += other.height;
    else
        bottom2 += other.height;
    if (top2 == bottom2) // null rect
        return false;

    if (top1 >= bottom2 || top2 >= bottom1)
        return false;

    return true;
}

Rect& Rect::unite(const Rect& other) {
    if (empty()) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
        return *this;
    }

    if (other.empty()) {
        return *this;
    }

    float left = x, right = x;
    if (width < 0)
        left += width;
    else
        right += width;

    if (other.width < 0) {
        left = std::min(left, other.x + other.width);
        right = std::max(right, other.x);
    } else {
        left = std::min(left, other.x);
        right = std::max(right, other.x + other.width);
    }

    float top = y, bottom = y;
    if (height < 0)
        top += height;
    else
        bottom += height;

    if (other.height < 0) {
        top = std::min(top, other.y + other.height);
        bottom = std::max(bottom, other.y);
    } else {
        top = std::min(top, other.y);
        bottom = std::max(bottom, other.y + other.height);
    }

    x = left;
    y = top;
    width = right - left;
    height = bottom - top;
    return *this;
}

Rect& Rect::align() {
    float xmin = std::floor(x);
    float xmax = std::ceil(x + width);
    float ymin = std::floor(y);
    float ymax = std::ceil(y + height);
    x = xmin;
    y = ymin;
    width = xmax - xmin;
    height = ymax - ymin;
    return *this;
}

Rect& Rect::normalize() {
    if (width < 0) {
        x += width;
        width = -width;
    }
    if (height < 0) {
        y += height;
        height = -height;
    }
    return *this;
}

bool Rect::contains(const Point& point, bool proper = false) {
    float left = x, right = x;
    if (width < 0)
        left += width;
    else
        right += width;
    if (left == right) // null rect
        return false;

    if (point.x < left || point.x > right)
        return false;

    float top = y, bottom = y;
    if (height < 0)
        top += height;
    else
        bottom += height;
    if (top == bottom) // null rect
        return false;

    if (proper)
        return !(point.y <= top || point.y >= bottom);
    else
        return !(point.y < top || point.y > bottom);
}

bool Rect::contains(const Rect& rect, bool proper = false) {
    if (width == 0 || height == 0 || rect.empty())
        return false;

    float left1 = x, right1 = x;
    if (x + width - x + 1 < 0)
        left1 = x + width;
    else
        right1 = x + width;

    float left2 = rect.x, right2 = rect.x;
    if (rect.x + rect.width - rect.x + 1 < 0)
        left2 = rect.x + rect.width;
    else
        right2 = rect.x + rect.width;

    if (left2 < left1 || right2 > right1)
        return false;

    float top1 = y, bottom1 = y;
    if (y + height - y + 1 < 0)
        top1 = y + height;
    else
        bottom1 = y + height;

    float top2 = y, bottom2 = y;
    if (rect.y + rect.height - rect.y + 1 < 0)
        top2 = rect.y + rect.height;
    else
        bottom2 = rect.y + rect.height;

    if (proper)
        return !(top2 <= top1 || bottom2 >= bottom1);
    else
        return !(top2 < top1 || bottom2 > bottom1);
}

Rect Rect::operator|(const Rect& other) const
{
    float left = x;
    float right = x;
    if (width < 0)
        left += width;
    else
        right += width;
    if (other.width < 0) {
        left = std::min(left, other.x + other.width);
        right = std::max(right, other.x);
    } else {
        left = std::min(left, other.x);
        right = std::max(right, other.x + other.width);
    }
    float top = y;
    float bottom = y;
    if (height < 0)
        top += height;
    else
        bottom += height;
    if (other.height < 0) {
        top = std::min(top, other.y + other.height);
        bottom = std::max(bottom, other.y);
    } else {
        top = std::min(top, other.y);
        bottom = std::max(bottom, other.y + other.height);
    }
    return Rect(left, top, right - left, bottom - top);
}

Rect Rect::operator&(const Rect& other) const
{
    float left1 = x;
    float right1 = x;
    if (width < 0)
        left1 += width;
    else
        right1 += width;
    if (left1 == right1) // null rect
        return Rect();
    float left2 = other.x;
    float right2 = other.x;
    if (other.width < 0)
        left2 += other.width;
    else
        right2 += other.width;
    if (left2 == right2) // null rect
        return Rect();
    if (left1 >= right2 || left2 >= right1)
        return Rect();
    float top1 = y;
    float bottom1 = y;
    if (height < 0)
        top1 += height;
    else
        bottom1 += height;
    if (top1 == bottom1) // null rect
        return Rect();
    float top2 = other.y;
    float bottom2 = other.y;
    if (other.height < 0)
        top2 += other.height;
    else
        bottom2 += other.height;
    if (top2 == bottom2) // null rect
        return Rect();
    if (top1 >= bottom2 || top2 >= bottom1)
        return Rect();
    Rect tmp;
    tmp.x = std::max(left1, left2);
    tmp.y = std::max(top1, top2);
    tmp.width = std::min(right1, right2) - tmp.x;
    tmp.height = std::min(bottom1, bottom2) - tmp.y;
    return tmp;
}
