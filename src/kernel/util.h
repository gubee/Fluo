/*
 * util.h
 *
 *  Created on: 2013. 6. 25.
 *      Author: impaulkim
 */

#ifndef UTIL_H_
#define UTIL_H_


#define FUZZY_EPSILON 0.000001

bool fuzzyIsNull(float value) {
    return abs(value) <= FUZZY_EPSILON;
}

#endif /* UTIL_H_ */
