/*
 * Object.cpp
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#include "CoreObject.h"

//----------------------------------------------------------------------------------------------
// class Object
Object::Object() {
}

Object::~Object() {
}

std::string Object::objectName() const {
    return m_objectName;
}

void Object::setObjectName(const std::string& value) {
    m_objectName = value;
}

void Object::none() {
}

//----------------------------------------------------------------------------------------------
// class DynamicObject
DynamicObject::DynamicObject(const MetaClass* metaClass)
    : m_metaClass(metaClass) {
}

DynamicObject::~DynamicObject() {
}

const MetaClass* DynamicObject::metaClass() const {
    return m_metaClass;
}

Object* DynamicObject::create(const MetaClass* metaClass) {
    return new DynamicObject(metaClass);
}
