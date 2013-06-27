/*
 * V8.cpp
 *
 *  Created on: 2013. 6. 25.
 *      Author: gubee
 */

#if defined(F_RUNTIME_V8)

#include "kernel/CoreObject.h"
#include "runtime/Runtime.h"
#include "V8.h"
#include <iostream> // TODO: del

namespace internals {
    const char* ToCString(const v8::String::Utf8Value& value) {
        return static_cast<const char*>(*value);
    }
}

//----------------------------------------------------------------------------------------------
// StackFrame APIs
void StackFrame_top(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void StackFrame_push(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void StackFrame_pop(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

//----------------------------------------------------------------------------------------------
// List APIs
void List_new(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void List_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void List_append(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void List_remove(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void List_removeAt(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void List_count(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void List_indexOf(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void List_at(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void List_setAt(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

//----------------------------------------------------------------------------------------------
// Map APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Class APIs
void Class_new(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const v8::String::Utf8Value name(arguments[0]);
    char* className = new char[name.length() + 1];
    strcpy(className, *name);
    MetaClass* baseClass = cast(MetaClass, arguments[0]->IntegerValue());

    MetaClass* metaClass = new MetaClass;
    metaClass->type = DynamicClass;
    metaClass->name = className;
    metaClass->base = baseClass;
    metaClass->create = &DynamicObject::create;
    metaClass->methodOffset = methodOffsetOf(*metaClass);
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass)));
}

void Class_defineMethod(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Class_name(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::String::New(metaClass->name));
}

void Class_base(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Class_methodCount(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Class_method(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Class_enumCount(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Class_enum(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

//----------------------------------------------------------------------------------------------
// Method APIs
void Method_name(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Method_type(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Method_call(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

//----------------------------------------------------------------------------------------------
// Enum APIs
void Enum_name(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Enum_values(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

//----------------------------------------------------------------------------------------------
// Object APIs
void Object_new(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Object_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

void Object_class(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
// TODO:

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
    v8::Handle<v8::Context> context;
};

void Runtime::startup() {
    m_data = new Data();

    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::HandleScope handleScope(isolate);
    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
    for (int i = 0; ; ++i) {
        const internals::API& api = internals::apis[i];
        if (!api.name)
            break;
        global->Set(v8::String::New(api.name), v8::FunctionTemplate::New(api.function));
    }

    m_data->context = v8::Context::New(isolate, 0, global);
    m_data->context->Enter();
}

void Runtime::shutdown() {
    m_data->context->Exit();
    delete m_data;
    m_data = 0;
}

#endif  // F_RUNTIME_V8
