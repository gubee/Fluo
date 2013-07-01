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

const MetaSignal* Object::signal(const char* name) const {
    typedef std::vector<MetaSignal*>::const_iterator Iterator;

    const MetaClass* metaClass = this->metaClass();
    while (metaClass) {
        Iterator i(metaClass->signals.begin());
        Iterator e(metaClass->signals.end());
        for (; i != e; ++i) {
            if (!std::strcmp((*i)->name, name))
                return *i;
        }

        metaClass = metaClass->base;
    }
    return 0;
}

const MetaProperty* Object::property(const char* name) const {
    typedef std::vector<MetaProperty*>::const_iterator Iterator;

    const MetaClass* metaClass = this->metaClass();
    while (metaClass) {
        Iterator i(metaClass->properties.begin());
        Iterator e(metaClass->properties.end());
        for (; i != e; ++i) {
            if (!std::strcmp((*i)->name, name))
                return *i;
        }

        metaClass = metaClass->base;
    }
    return 0;
}

const MetaMethod* Object::method(const char* name) const {
    typedef std::vector<MetaMethod*>::const_iterator Iterator;

    const MetaClass* metaClass = this->metaClass();
    while (metaClass) {
        Iterator i(metaClass->methods.begin());
        Iterator e(metaClass->methods.end());
        for (; i != e; ++i) {
            if (!std::strcmp((*i)->name, name))
                return *i;
        }

        metaClass = metaClass->base;
    }
    return 0;
}

none* Object::none() {
    return 0;
}

void Object::emit(const Signal& signal) const {
    if (signal.empty())
        return;

    internals::StackFrame_push();
    internals::StackFrame_set((Object*)0);
    signal.notify(this);
    internals::StackFrame_pop();
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
