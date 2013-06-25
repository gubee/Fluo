/*
 * Size.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef SIZE_H_
#define SIZE_H_

struct Size {
    float width;
    float height;

    Size()
        : width(0), height(0)
    {
    }

    Size(const float& width, const float& height)
        : width(width), height(height)
    {
    }

    Size& reset(float width, float height) {
        this->width = width;
        this->height = height;
        return *this;
    }

    bool equals(const Size& other) const {
        return width == other.width && height == other.height;
    }

    bool notEquals(const Size& other) const {
        return width != other.width || height != other.height;
    }

    Size clone() const {
        return Size(width, height);
    }

    bool empty() const {
        return width == 0 || height == 0;
    }
};

#endif /* SIZE_H_ */
