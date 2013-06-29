/*
 * ClassRegistry.cpp
 *
 *  Created on: 2013. 6. 29.
 *      Author: gubee
 */

#include "ClassRegistry.h"
#include "CoreType.h"

ClassRegistry::ClassRegistry() {
}

ClassRegistry::~ClassRegistry() {
}

void ClassRegistry::registerClass(const MetaClass* metaClass) {
    m_registry.insert(std::make_pair(metaClass->name, metaClass));
}

const MetaClass* ClassRegistry::findClass(const char* name) const {
    Iterator i = m_registry.find(name);
    return (i != m_registry.end()) ? i->second : 0;
}

const ClassRegistry::Container& ClassRegistry::registeredClasses() const {
    return m_registry;
}

ClassRegistry& ClassRegistry::instance() {
    static ClassRegistry instance;
    return instance;
}

