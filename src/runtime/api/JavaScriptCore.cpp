/*
 * JavaScriptCore.cpp
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#if defined(F_RUNTIME_JAVASCRIPTCORE)

#include <cstring>
#include "kernel/CoreObject.h"
#include "kernel/ClassRegistry.h"
#include "kernel/StackFrame.h"
#include "kernel/Iterator.h"
#include "runtime/Runtime.h"

//----------------------------------------------------------------------------------------------
// StackFrame APIs
JSC::JSValueRef StackFrame_top(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(internals::StackFrame_top())));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef StackFrame_push(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(internals::StackFrame_push())));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef StackFrame_pop(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    internals::StackFrame_pop();
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// Iterator APIs
JSC::JSValueRef Iterator_delete(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    Iterator* iterator = cast(Iterator, arguments[0]->IntegerValue());
//    delete iterator;
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Iterator_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    Iterator* iterator = cast(Iterator, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::String::New(iterator->name()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Iterator_value(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    Iterator* iterator = cast(Iterator, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(iterator->value());
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Iterator_next(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    Iterator* iterator = cast(Iterator, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Boolean::New(iterator->next()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// List APIs
JSC::JSValueRef List_new(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    List* list = List::newInstance((Type)arguments[0]->Int32Value());
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(list)));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef List_delete(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    List* list = cast(List, arguments[0]->IntegerValue());
//    delete list;
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef List_append(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    List* list = cast(List, arguments[0]->IntegerValue());
//    list->append(arguments[1]);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef List_remove(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    List* list = cast(List, arguments[0]->IntegerValue());
//    list->remove(arguments[1], arguments.Length() > 2 ? arguments[2]->BooleanValue() : false);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef List_removeAt(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    List* list = cast(List, arguments[0]->IntegerValue());
//    list->append(arguments[1]);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef List_count(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const List* list = cast(List, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Int32::New(list->count()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef List_indexOf(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const List* list = cast(List, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Int32::New(list->indexOf(arguments[1])));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef List_at(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const List* list = cast(List, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(list->at(arguments[1]->Int32Value()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef List_setAt(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    List* list = cast(List, arguments[0]->IntegerValue());
//    list->setAt(arguments[1]->Int32Value(), arguments[2]);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// Map APIs
JSC::JSValueRef Map_new(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    Map* map = Map::newInstance((Type)arguments[0]->Int32Value());
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(map)));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Map_delete(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    Map* map = cast(Map, arguments[0]->IntegerValue());
//    delete map;
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Map_insert(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    Map* map = cast(Map, arguments[0]->IntegerValue());
//    const v8::String::Utf8Value name(arguments[1]);
//    map->insert(*name, arguments[2]);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Map_remove(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    Map* map = cast(Map, arguments[0]->IntegerValue());
//    const v8::String::Utf8Value name(arguments[1]);
//    map->remove(*name);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Map_count(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const Map* map = cast(Map, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Int32::New(map->count()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Map_names(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const Map* map = cast(Map, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(map->names())));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Map_value(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const Map* map = cast(Map, arguments[0]->IntegerValue());
//    const v8::String::Utf8Value name(arguments[1]);
//    arguments.GetReturnValue().Set(map->value(*name));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// Class APIs
JSC::JSValueRef Class_new(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const v8::String::Utf8Value name(arguments[0]);
//    char* className = new char[name.length() + 1];
//    std::strcpy(className, *name);
//    MetaClass* baseClass = cast(MetaClass, arguments[0]->IntegerValue());
//
//    MetaClass* metaClass = new MetaClass;
//    metaClass->type = DynamicClass;
//    metaClass->name = className;
//    metaClass->base = baseClass;
//    metaClass->create = &DynamicObject::create;
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass)));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_defineMethod(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_defineProperty(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_defineSignal(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::String::New(metaClass->name));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_base(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass->base)));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_enumCount(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Int32::New(metaClass->enums.size()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_enum(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    std::size_t index = arguments[1]->Uint32Value();
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass->enums[index])));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_methodCount(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Uint32::New(metaClass->methods.size()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_method(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    std::size_t index = arguments[1]->Uint32Value();
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass->methods[index])));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_propertyCount(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Int32::New(metaClass->properties.size()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_property(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    std::size_t index = arguments[1]->Uint32Value();
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass->properties[index])));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_signalCount(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Int32::New(metaClass->signals.size()));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Class_signal(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    std::size_t index = arguments[1]->Uint32Value();
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass->signals[index])));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// Enum APIs
JSC::JSValueRef Enum_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaEnum* metaEnum = cast(MetaEnum, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::String::New(metaEnum->name));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Enum_values(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaEnum* metaEnum = cast(MetaEnum, arguments[0]->IntegerValue());
//    Iterator* iterator = newIterator(metaEnum->values);
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(iterator)));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// Method APIs
JSC::JSValueRef Method_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaMethod* metaMethod = cast(MetaMethod, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::String::New(metaMethod->name));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Method_call(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaMethod* metaMethod = cast(MetaMethod, arguments[0]->IntegerValue());
//    metaMethod->function->invoke();
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// Property APIs
JSC::JSValueRef Property_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaProperty* metaProperty = cast(MetaProperty, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::String::New(metaProperty->name));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Property_type(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaProperty* metaProperty = cast(MetaProperty, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Uint32::New(metaProperty->type));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Property_isReadOnly(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaProperty* metaProperty = cast(MetaProperty, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Boolean::New(metaProperty->setter != 0));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Property_read(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaProperty* metaProperty = cast(MetaProperty, arguments[0]->IntegerValue());
//    metaProperty->getter->invoke();
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Property_write(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaProperty* metaProperty = cast(MetaProperty, arguments[0]->IntegerValue());
//    if (!metaProperty->setter) {
//        // TODO: read-only property calling error
//        return;
//    }
//    metaProperty->setter->invoke();
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// Signal APIs
JSC::JSValueRef Signal_name(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaSignal* metaSignal = cast(MetaSignal, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::String::New(metaSignal->name));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Signal_connect(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaSignal* metaSignal = cast(MetaSignal, arguments[0]->IntegerValue());
//    Object* sender = cast(Object, arguments[1]->IntegerValue());
//    Object* receiver = cast(Object, arguments[2]->IntegerValue());
//    const MetaMethod* metaMethod = cast(MetaMethod, arguments[3]->IntegerValue());
//    internals::Signal_connect(metaSignal->indexer, sender, receiver, metaMethod);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Signal_disconnect(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaSignal* metaSignal = cast(MetaSignal, arguments[0]->IntegerValue());
//    Object* sender = cast(Object, arguments[1]->IntegerValue());
//    Object* receiver = cast(Object, arguments[2]->IntegerValue());
//    const MetaMethod* metaMethod = cast(MetaMethod, arguments[3]->IntegerValue());
//    internals::Signal_disconnect(metaSignal->indexer, sender, receiver, metaMethod);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Signal_emit(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaSignal* metaSignal = cast(MetaSignal, arguments[0]->IntegerValue());
//    Object* sender = cast(Object, arguments[1]->IntegerValue());
//    internals::Signal_emit(metaSignal->indexer, sender);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// Object APIs
JSC::JSValueRef Object_new(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    Object* object = metaClass->create(metaClass);
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(object)));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Object_delete(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const Object* object = cast(Object, arguments[0]->IntegerValue());
//    delete object;
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef Object_class(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    v8::HandleScope handleScope;
//    const Object* object = cast(Object, arguments[0]->IntegerValue());
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(object->metaClass())));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
JSC::JSValueRef ClassRegistry_register(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
//    ClassRegistry::instance().registerClass(metaClass);
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef ClassRegistry_class(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    const v8::String::Utf8Value name(arguments[0]);
//    const MetaClass* metaClass = ClassRegistry::instance().findClass(*name);
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass)));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

JSC::JSValueRef ClassRegistry_classes(JSC::JSContextRef context, JSC::JSObjectRef function, JSC::JSObjectRef thisObject, size_t argumentCount, const JSC::JSValueRef arguments[], JSC::JSValueRef*) {
//    Iterator* iterator = newIterator(ClassRegistry::instance().registeredClasses());
//    arguments.GetReturnValue().Set(v8::Number::New(asHandle(iterator)));
    // TODO:
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
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

    JSC::JSContextRef context;
}

struct Runtime::Data {
    // TODO:
    //v8::Handle<v8::Context> context;
};

void Runtime::startup() {
    m_data = new Data();

    // TODO:
//    v8::Isolate* isolate = v8::Isolate::GetCurrent();
//    v8::HandleScope handleScope(isolate);
//    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
//    for (int i = 0; ; ++i) {
//        const internals::API& api = internals::apis[i];
//        if (!api.name)
//            break;
//        global->Set(v8::String::New(api.name), v8::FunctionTemplate::New(api.function));
//    }
//
//    m_data->context = v8::Context::New(isolate, 0, global);
//    m_data->context->Enter();
}

void Runtime::shutdown() {
//    m_data->context->Exit();
//    delete m_data;
//    m_data = 0;
}

void Runtime::runScript(const char* source) {
//    v8::HandleScope handleScope;
//    v8::Handle<v8::Script> script = v8::Script::Compile(v8::String::New(source));
//    script->Run();
}

#endif  // F_RUNTIME_JAVASCRIPTCORE
