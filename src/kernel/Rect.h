/*
 * Rect.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef RECT_H_
#define RECT_H_

#include <cmath>
#include <algorithm>
#include "point.h"

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

    Rect& reset(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        return *this;
    }

    bool equals(const Rect& other) const {
        return x == other.x && y == other.y &&
            width == other.width && height == other.height;
    }

    bool notEquals(const Rect& other) const {
        return x != other.x || y != other.y ||
            width != other.width || height != other.height;
    }

    Rect clone() const {
        return Rect(x, y, width, height);
    }

    bool empty() const {
        return width == 0 || height == 0;
    }

    Rect& clear() {
        x = y = width = height = 0;
        return *this;
    }

    float left() const {
        return x;
    }

    float right() const {
        return x + width;
    }

    float top() const {
        return y;
    }

    float bottom() const {
        return y + height;
    }

    Rect& adjust(float x1, float y1, float x2, float y2) {
        x += x1;
        y += y1;
        width += (x2 - x1);
        height += (y2 - y1);
        return *this;
    }

    Rect adjusted(float x1, float y1, float x2, float y2) const {
        return clone().adjust(x1, y1, x2, y2);
    }

    Rect intersected(const Rect& other) const {
        Rect result;

        float left1 = x, right1 = x;
        if (width < 0)
            left1 += width;
        else
            right1 += width;
        if (left1 == right1) // null rect
            return result;

        float left2 = other.x, right2 = other.x;
        if (other.width < 0)
            left2 += other.width;
        else
            right2 += other.width;
        if (left2 == right2) // null rect
            return result;

        if (left1 >= right2 || left2 >= right1)
            return result;

        float top1 = y, bottom1 = y;
        if (height < 0)
            top1 += height;
        else
            bottom1 += height;
        if (top1 == bottom1) // null rect
            return result;

        float top2 = other.y, bottom2 = other.y;
        if (other.height < 0)
            top2 += other.height;
        else
            bottom2 += other.height;
        if (top2 == bottom2) // null rect
            return result;

        if (top1 >= bottom2 || top2 >= bottom1)
            return result;

        result.x = std::max(left1, left2);
        result.y = std::max(top1, top2);
        result.width = std::min(right1, right2) - result.x;
        result.height = std::min(bottom1, bottom2) - result.y;
        return result;
    }

    bool intersects(const Rect& other) {
        return !intersected(other).empty();
    }

    Rect& unite(const Rect& other) {
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

    Rect united(const Rect& other) const {
        return clone().unite(other);
    }

    Rect& align() {
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

    Rect aligned() const {
        return clone().align();
    }

    Rect& normalize() {
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

    Rect normalized() const {
        return clone().normalize();
    }

    bool contains(const Rect& rect, bool proper = false) {
        return containsRect(rect, proper);
    }

    bool contains(const Point& point, bool proper = false) {
        return containsPoint(point, proper);
    }

    bool containsPoint(const Point& point, bool proper = false) {
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

    bool containsRect(const Rect& rect, bool proper = false) {
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

    Rect& moveCenter(const Point& point) {
        x = point.x - width / 2;
        y = point.y - height / 2;
        return *this;
    }
};

#endif /* RECT_H_ */
