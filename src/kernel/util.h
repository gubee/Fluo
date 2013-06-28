/*
 * util.h
 *
 *  Created on: 2013. 6. 25.
 *      Author: impaulkim
 */

#ifndef UTIL_H_
#define UTIL_H_

#define FUZZY_EPSILON 0.000001

bool inline fuzzyIsNull(float value) {
    return abs(value) <= FUZZY_EPSILON;
}

bool inline fuzzyCompare(float lhs, float rhs) {
    return (abs(lhs - rhs) <= 0.000000000001 * std::min(abs(lhs), abs(rhs)));
}

#endif /* UTIL_H_ */
