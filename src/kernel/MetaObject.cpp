/*
 * MetaObject.cpp
 *
 *  Created on: 2013. 6. 24.
 *      Author: gubee
 */

#include "MetaObject.h"

int methodOffsetOf(const MetaClass& metaClass) {
    return metaClass.base ? metaClass.base->methodOffset + metaClass.base->methods.size() : 0;
}

void addMetaMethod(MetaClass& metaClass, const char* name, MethodType type, Invoker* invoker) {
    MetaMethod* metaMethod = new MetaMethod();
    metaMethod->name = name;
    metaMethod->type = type;
    metaMethod->function = invoker;
    metaClass.methods.push_back(metaMethod);
}
