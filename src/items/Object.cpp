/*
 * Object.cpp
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#include "Object.h"

Object::Object() {
    // TODO Auto-generated constructor stub
}

Object::~Object() {
    // TODO Auto-generated destructor stub
}

std::string Object::objectName() const {
    return m_objectName;
}

void Object::setObjectName(const std::string& value) {
    m_objectName = value;
}
