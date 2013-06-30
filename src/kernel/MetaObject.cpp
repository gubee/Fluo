/*
 * MetaObject.cpp
 *
 *  Created on: 2013. 6. 24.
 *      Author: gubee
 */

#include "MetaObject.h"

namespace internals {
    void Method_define(MetaClass* metaClass, const char* name, Invoker* invoker) {
        MetaMethod* metaMethod = new MetaMethod();
        metaMethod->name = name;
        metaMethod->function = invoker;
        metaClass->methods.push_back(metaMethod);
    }

    void Property_define(MetaClass* metaClass, const char* name, Invoker* getter, Invoker* setter, Type type) {
        MetaProperty* metaProperty = new MetaProperty();
        metaProperty->name = name;
        metaProperty->getter = getter;
        metaProperty->setter = setter;
        metaProperty->type = type;
        metaClass->properties.push_back(metaProperty);
    }

    void Signal_define(MetaClass* metaClass, const char* name, SignalIndexer* indexer) {
        MetaSignal* metaSignal = new MetaSignal();
        metaSignal->name = name;
        metaSignal->indexer = indexer;
        metaClass->signals.push_back(metaSignal);
    }
}
