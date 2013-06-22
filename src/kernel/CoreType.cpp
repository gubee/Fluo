/*
 * CoreType.cpp
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#include "CoreType.h"

int propertyOffsetOf(const MetaClass& metaClass) {
    return metaClass.base ? metaClass.base->propertyOffset + metaClass.base->properties.size() : 0;
}

int methodOffsetOf(const MetaClass& metaClass) {
    return metaClass.base ? metaClass.base->methodOffset + metaClass.base->methods.size() : 0;
}
