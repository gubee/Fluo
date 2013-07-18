/*
 * JavaScriptCore.cpp
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#if defined(F_RUNTIME_JAVASCRIPTCORE)

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSObjectRef.h>
namespace JSC {
    using ::JSGlobalContextCreate;
    using ::JSGlobalContextRelease;
    using ::JSContextGetGlobalObject;
    using ::JSObjectMakeFunctionWithCallback;
    using ::JSEvaluateScript;
    using ::JSObjectSetProperty;
}

#include <cstring>
#include "kernel/CoreObject.h"
#include "kernel/ClassRegistry.h"
#include "kernel/StackFrame.h"
#include "kernel/Iterator.h"
#include "kernel/Runtime.h"
#include "runtime/API.h"

//----------------------------------------------------------------------------------------------
// StackFrame APIs
JSC::JSValueRef StackFrame_top(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    return JSC::JSValueMakeNumber(context, asHandle(internals::StackFrame_top()));
}

JSC::JSValueRef StackFrame_push(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    return JSC::JSValueMakeNumber(context, asHandle(internals::StackFrame_push()));
}

JSC::JSValueRef StackFrame_pop(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    internals::StackFrame_pop();
    return JSC::JSValueMakeUndefined(context);
}

//----------------------------------------------------------------------------------------------
// Iterator APIs
JSC::JSValueRef Iterator_delete(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Iterator* iterator = cast(Iterator, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    delete iterator;
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Iterator_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Iterator* iterator = cast(Iterator, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSStringCreateWithUTF8CString(iterator->name());
    JSC::JSValueRef result = JSC::JSValueMakeString(context, data);
    JSC::JSStringRelease(data);
    return result;
}

JSC::JSValueRef Iterator_value(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Iterator* iterator = cast(Iterator, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return iterator->value();
}

JSC::JSValueRef Iterator_next(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Iterator* iterator = cast(Iterator, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeBoolean(context, iterator->next());
}

//----------------------------------------------------------------------------------------------
// List APIs
JSC::JSValueRef List_new(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    List* list = List::newInstance((Type)JSC::JSValueToNumber(context, arguments[0], 0));
    return JSC::JSValueMakeNumber(context, asHandle(list));
}

JSC::JSValueRef List_delete(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    List* list = cast(List, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    delete list;
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef List_append(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    List* list = cast(List, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    list->append(arguments[1]);
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef List_remove(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    List* list = cast(List, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    list->remove(arguments[1], argumentCount > 2 ? JSC::JSValueToBoolean(context, arguments[2]) : false);
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef List_removeAt(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    List* list = cast(List, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    list->removeAt(asInteger(JSC::JSValueToNumber(context, arguments[1], 0)));
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef List_count(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const List* list = cast(List, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, list->count());
}

JSC::JSValueRef List_indexOf(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const List* list = cast(List, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, list->indexOf(arguments[1]));
}

JSC::JSValueRef List_at(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const List* list = cast(List, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return list->at(asInteger(JSC::JSValueToNumber(context, arguments[1], 0)));
}

JSC::JSValueRef List_setAt(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    List* list = cast(List, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    list->setAt(asInteger(JSC::JSValueToNumber(context, arguments[1], 0)), arguments[2]);
    return JSC::JSValueMakeUndefined(context);
}

//----------------------------------------------------------------------------------------------
// Map APIs
JSC::JSValueRef Map_new(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Map* map = Map::newInstance((Type)asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, asHandle(map));
}

JSC::JSValueRef Map_delete(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Map* map = cast(Map, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    delete map;
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Map_insert(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Map* map = cast(Map, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSValueToStringCopy(context, arguments[1], 0);
    size_t size = JSC::JSStringGetMaximumUTF8CStringSize(data);

    Runtime::Arena name(size);
    size = JSC::JSStringGetUTF8CString(data, *name, size);
    (*name)[size] = 0;
    JSC::JSStringRelease(data);
    map->insert(*name, arguments[2]);
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Map_remove(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Map* map = cast(Map, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSValueToStringCopy(context, arguments[1], 0);
    size_t size = JSC::JSStringGetMaximumUTF8CStringSize(data);

    Runtime::Arena name(size);
    size = JSC::JSStringGetUTF8CString(data, *name, size);
    (*name)[size] = 0;
    JSC::JSStringRelease(data);
    map->remove(*name);
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Map_count(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const Map* map = cast(Map, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, map->count());
}

JSC::JSValueRef Map_names(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const Map* map = cast(Map, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, asHandle(map->names()));
}

JSC::JSValueRef Map_value(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const Map* map = cast(Map, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSValueToStringCopy(context, arguments[1], 0);
    size_t size = JSC::JSStringGetMaximumUTF8CStringSize(data);

    Runtime::Arena name(size);
    size = JSC::JSStringGetUTF8CString(data, *name, size);
    (*name)[size] = 0;
    JSC::JSStringRelease(data);
    return map->value(*name);
}

//----------------------------------------------------------------------------------------------
// Class APIs
JSC::JSValueRef Class_new(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    JSC::JSStringRef data = JSC::JSValueToStringCopy(context, arguments[0], 0);
    size_t size = JSC::JSStringGetMaximumUTF8CStringSize(data);

    Runtime::Arena name(size);
    size = JSC::JSStringGetUTF8CString(data, *name, size);
    (*name)[size] = 0;
    JSC::JSStringRelease(data);

    char* className = new char[size + 1];
    std::strcpy(className, *name);
    MetaClass* baseClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[1], 0)));

    MetaClass* metaClass = new MetaClass;
    metaClass->type = DynamicClass;
    metaClass->name = className;
    metaClass->base = baseClass;
    metaClass->create = &DynamicObject::create;
    return JSC::JSValueMakeNumber(context, asHandle(metaClass));
}

JSC::JSValueRef Class_defineMethod(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    // TODO:
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Class_defineProperty(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    // TODO:
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Class_defineSignal(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    // TODO:
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Class_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSStringCreateWithUTF8CString(metaClass->name);
    JSC::JSValueRef result = JSC::JSValueMakeString(context, data);
    JSC::JSStringRelease(data);
    return result;
}

JSC::JSValueRef Class_base(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, asHandle(metaClass->base));
}

JSC::JSValueRef Class_enumCount(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, metaClass->enums.size());
}

JSC::JSValueRef Class_enum(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    std::size_t index = asInteger(JSC::JSValueToNumber(context, arguments[1], 0));
    return JSC::JSValueMakeNumber(context, asHandle(metaClass->enums[index]));
}

JSC::JSValueRef Class_methodCount(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, metaClass->methods.size());
}

JSC::JSValueRef Class_method(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    std::size_t index = asInteger(JSC::JSValueToNumber(context, arguments[1], 0));
    return JSC::JSValueMakeNumber(context, asHandle(metaClass->methods[index]));
}

JSC::JSValueRef Class_propertyCount(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, metaClass->properties.size());
}

JSC::JSValueRef Class_property(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    std::size_t index = asInteger(JSC::JSValueToNumber(context, arguments[1], 0));
    return JSC::JSValueMakeNumber(context, asHandle(metaClass->properties[index]));
}

JSC::JSValueRef Class_signalCount(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, metaClass->signals.size());
}

JSC::JSValueRef Class_signal(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    std::size_t index = asInteger(JSC::JSValueToNumber(context, arguments[1], 0));
    return JSC::JSValueMakeNumber(context, asHandle(metaClass->signals[index]));
}

//----------------------------------------------------------------------------------------------
// Enum APIs
JSC::JSValueRef Enum_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaEnum* metaEnum = cast(MetaEnum, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSStringCreateWithUTF8CString(metaEnum->name);
    JSC::JSValueRef result = JSC::JSValueMakeString(context, data);
    JSC::JSStringRelease(data);
    return result;
}

JSC::JSValueRef Enum_values(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaEnum* metaEnum = cast(MetaEnum, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    Iterator* iterator = newIterator(metaEnum->values);
    return JSC::JSValueMakeNumber(context, asHandle(iterator));
}

//----------------------------------------------------------------------------------------------
// Method APIs
JSC::JSValueRef Method_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaMethod* metaMethod = cast(MetaMethod, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSStringCreateWithUTF8CString(metaMethod->name);
    JSC::JSValueRef result = JSC::JSValueMakeString(context, data);
    JSC::JSStringRelease(data);
    return result;
}

JSC::JSValueRef Method_call(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaMethod* metaMethod = cast(MetaMethod, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    metaMethod->function->invoke();
    return JSC::JSValueMakeUndefined(context);
}

//----------------------------------------------------------------------------------------------
// Property APIs
JSC::JSValueRef Property_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaProperty* metaProperty = cast(MetaProperty, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSStringCreateWithUTF8CString(metaProperty->name);
    JSC::JSValueRef result = JSC::JSValueMakeString(context, data);
    JSC::JSStringRelease(data);
    return result;
}

JSC::JSValueRef Property_type(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaProperty* metaProperty = cast(MetaProperty, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, metaProperty->type);
}

JSC::JSValueRef Property_isReadOnly(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaProperty* metaProperty = cast(MetaProperty, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeBoolean(context, metaProperty->setter != 0);
}

JSC::JSValueRef Property_read(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaProperty* metaProperty = cast(MetaProperty, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    metaProperty->getter->invoke();
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Property_write(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaProperty* metaProperty = cast(MetaProperty, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    if (!metaProperty->setter) {
        // TODO: read-only property calling error
        return JSC::JSValueMakeUndefined(context);
    }
    metaProperty->setter->invoke();
    return JSC::JSValueMakeUndefined(context);
}

//----------------------------------------------------------------------------------------------
// Signal APIs
JSC::JSValueRef Signal_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaSignal* metaSignal = cast(MetaSignal, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    JSC::JSStringRef data = JSC::JSStringCreateWithUTF8CString(metaSignal->name);
    JSC::JSValueRef result = JSC::JSValueMakeString(context, data);
    JSC::JSStringRelease(data);
    return result;
}

JSC::JSValueRef Signal_connect(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaSignal* metaSignal = cast(MetaSignal, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    Object* sender = cast(Object, asInteger(JSC::JSValueToNumber(context, arguments[1], 0)));
    Object* receiver = cast(Object, asInteger(JSC::JSValueToNumber(context, arguments[2], 0)));
    const MetaMethod* metaMethod = cast(MetaMethod, asInteger(JSC::JSValueToNumber(context, arguments[3], 0)));
    internals::Signal_connect(metaSignal->indexer, sender, receiver, metaMethod);
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Signal_disconnect(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaSignal* metaSignal = cast(MetaSignal, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    Object* sender = cast(Object, asInteger(JSC::JSValueToNumber(context, arguments[1], 0)));
    Object* receiver = cast(Object, asInteger(JSC::JSValueToNumber(context, arguments[2], 0)));
    const MetaMethod* metaMethod = cast(MetaMethod, asInteger(JSC::JSValueToNumber(context, arguments[3], 0)));
    internals::Signal_disconnect(metaSignal->indexer, sender, receiver, metaMethod);
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Signal_emit(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaSignal* metaSignal = cast(MetaSignal, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    Object* sender = cast(Object, asInteger(JSC::JSValueToNumber(context, arguments[1], 0)));
    internals::Signal_emit(metaSignal->indexer, sender);
    return JSC::JSValueMakeUndefined(context);
}

//----------------------------------------------------------------------------------------------
// Object APIs
JSC::JSValueRef Object_new(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    Object* object = metaClass->create(metaClass);
    return JSC::JSValueMakeNumber(context, asHandle(object));
}

JSC::JSValueRef Object_delete(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const Object* object = cast(Object, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    delete object;
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef Object_class(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const Object* object = cast(Object, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    return JSC::JSValueMakeNumber(context, asHandle(object->metaClass()));
}

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
JSC::JSValueRef ClassRegistry_register(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    const MetaClass* metaClass = cast(MetaClass, asInteger(JSC::JSValueToNumber(context, arguments[0], 0)));
    ClassRegistry::instance().registerClass(metaClass);
    return JSC::JSValueMakeUndefined(context);
}

JSC::JSValueRef ClassRegistry_class(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    JSC::JSStringRef data = JSC::JSValueToStringCopy(context, arguments[0], 0);
    size_t size = JSC::JSStringGetMaximumUTF8CStringSize(data);

    Runtime::Arena name(size);
    size = JSC::JSStringGetUTF8CString(data, *name, size);
    (*name)[size] = 0;
    JSC::JSStringRelease(data);

    const MetaClass* metaClass = ClassRegistry::instance().findClass(*name);
    return JSC::JSValueMakeNumber(context, asHandle(metaClass));
}

JSC::JSValueRef ClassRegistry_classes(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    Runtime::Context runtimeContext(context);
    Iterator* iterator = newIterator(ClassRegistry::instance().registeredClasses());
    return JSC::JSValueMakeNumber(context, asHandle(iterator));
}

//----------------------------------------------------------------------------------------------
// Script APIs
// TODO:

//----------------------------------------------------------------------------------------------
// class Runtime
namespace internals {
    struct API {
        const char* name;
        APIPrototype function;
    };

    extern API apis[];
}

struct Runtime::Data {
    JSC::JSGlobalContextRef context;
    JSC::JSObjectRef global;
};

void Runtime::startup() {
    m_data = new Data();

    m_data->context = JSC::JSGlobalContextCreate(0);
    m_data->global = JSC::JSContextGetGlobalObject(m_data->context);
    for (int i = 0; ; ++i) {
        const internals::API& api = internals::apis[i];
        if (!api.name)
            break;

        JSC::JSStringRef name = JSC::JSStringCreateWithUTF8CString(api.name);
        JSC::JSValueRef function = JSC::JSObjectMakeFunctionWithCallback(m_data->context, name, api.function);
        JSC::JSObjectSetProperty(m_data->context, m_data->global, name, function, 0/*attributes*/, 0);
        JSC::JSStringRelease(name);
    }
}

void Runtime::shutdown() {
    if (m_data) {
        JSC::JSGlobalContextRelease(m_data->context);
    }
    delete m_data;
    m_data = 0;
}

void Runtime::runScript(const char* source) {
    JSC::JSStringRef script = JSC::JSStringCreateWithUTF8CString(source);
    JSC::JSEvaluateScript(
        m_data->context,
        script,
        0, // this object
        0, // source url
        0, // starting line number
        0);
    JSC::JSStringRelease(script);
}

#endif  // F_RUNTIME_JAVASCRIPTCORE
