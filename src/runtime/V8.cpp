/*
 * V8.cpp
 *
 *  Created on: 2013. 6. 25.
 *      Author: gubee
 */

#if defined(F_RUNTIME_V8)

#include "V8.h"

//----------------------------------------------------------------------------------------------
// StackFrame APIs
v8::Handle<v8::Value> StackFrame_top(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> StackFrame_push(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> StackFrame_pop(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

//----------------------------------------------------------------------------------------------
// List APIs
v8::Handle<v8::Value> List_new(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> List_delete(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> List_append(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> List_remove(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> List_removeAt(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> List_count(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> List_indexOf(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> List_at(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> List_setAt(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

//----------------------------------------------------------------------------------------------
// Map APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Class APIs
v8::Handle<v8::Value> Class_new(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Class_defineMethod(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Class_name(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Class_base(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Class_methodCount(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Class_method(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Class_enumCount(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Class_enum(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

//----------------------------------------------------------------------------------------------
// Method APIs
v8::Handle<v8::Value> Method_name(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Method_type(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Method_call(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

//----------------------------------------------------------------------------------------------
// Enum APIs
v8::Handle<v8::Value> Enum_name(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Enum_values(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

//----------------------------------------------------------------------------------------------
// Object APIs
v8::Handle<v8::Value> Object_new(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Object_delete(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

v8::Handle<v8::Value> Object_class(const v8::Arguments& arguments) {
    // TODO:
    return v8::Undefined();
}

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Script APIs
// TODO:

#endif  // F_RUNTIME_V8
