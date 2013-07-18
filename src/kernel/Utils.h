/*
 * Utils.h
 *
 *  Created on: 2013. 6. 25.
 *      Author: impaulkim
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cmath>
#include <algorithm>

//----------------------------------------------------------------------------------------------
// Fuzzy functions
#define FUZZY_EPSILON 0.000001

bool inline fuzzyIsNull(float value) {
    return std::abs(value) <= FUZZY_EPSILON;
}

bool inline fuzzyCompare(float lhs, float rhs) {
    return (std::abs(lhs - rhs) <= 0.000000000001 * std::min(std::abs(lhs), std::abs(rhs)));
}

#endif /* UTILS_H_ */
