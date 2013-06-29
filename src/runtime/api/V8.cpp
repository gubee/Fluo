/*
 * V8.cpp
 *
 *  Created on: 2013. 6. 25.
 *      Author: gubee
 */

#if defined(F_RUNTIME_V8)

#include "kernel/CoreObject.h"
#include "kernel/ClassRegistry.h"
#include "kernel/StackFrame.h"
#include "kernel/Iterator.h"
#include "runtime/Runtime.h"
#include "V8.h"

//----------------------------------------------------------------------------------------------
// StackFrame APIs
void StackFrame_top(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(internals::StackFrame_top())));
}

void StackFrame_push(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(internals::StackFrame_push())));
}

void StackFrame_pop(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    internals::StackFrame_pop();
}

//----------------------------------------------------------------------------------------------
// Iterator APIs
void Iterator_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    Iterator* iterator = cast(Iterator, arguments[0]->IntegerValue());
    delete iterator;
}

void Iterator_name(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    Iterator* iterator = cast(Iterator, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::String::New(iterator->name()));
}

void Iterator_value(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    Iterator* iterator = cast(Iterator, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(iterator->value());
}

void Iterator_next(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    Iterator* iterator = cast(Iterator, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Boolean::New(iterator->next()));
}

//----------------------------------------------------------------------------------------------
// List APIs
void List_new(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    List* list = List::newInstance((Type)arguments[0]->Int32Value());
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(list)));
}

void List_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    List* list = cast(List, arguments[0]->IntegerValue());
    delete list;
}

void List_append(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    List* list = cast(List, arguments[0]->IntegerValue());
    list->append(arguments[1]);
}

void List_remove(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    List* list = cast(List, arguments[0]->IntegerValue());
    list->remove(arguments[1], arguments.Length() > 2 ? arguments[2]->BooleanValue() : false);
}

void List_removeAt(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    List* list = cast(List, arguments[0]->IntegerValue());
    list->append(arguments[1]);
}

void List_count(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const List* list = cast(List, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Int32::New(list->count()));
}

void List_indexOf(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const List* list = cast(List, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Int32::New(list->indexOf(arguments[1])));
}

void List_at(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const List* list = cast(List, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(list->at(arguments[1]->Int32Value()));
}

void List_setAt(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    List* list = cast(List, arguments[0]->IntegerValue());
    list->setAt(arguments[1]->Int32Value(), arguments[2]);
}

//----------------------------------------------------------------------------------------------
// Map APIs
void Map_new(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    Map* map = Map::newInstance((Type)arguments[0]->Int32Value());
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(map)));
}

void Map_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    Map* map = cast(Map, arguments[0]->IntegerValue());
    delete map;
}

void Map_insert(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    Map* map = cast(Map, arguments[0]->IntegerValue());
    const v8::String::Utf8Value name(arguments[1]);
    map->insert(*name, arguments[2]);
}

void Map_remove(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    Map* map = cast(Map, arguments[0]->IntegerValue());
    const v8::String::Utf8Value name(arguments[1]);
    map->remove(*name);
}

void Map_count(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const Map* map = cast(Map, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Int32::New(map->count()));
}

void Map_names(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const Map* map = cast(Map, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(map->names())));
}

void Map_value(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const Map* map = cast(Map, arguments[0]->IntegerValue());
    const v8::String::Utf8Value name(arguments[1]);
    arguments.GetReturnValue().Set(map->value(*name));
}

//----------------------------------------------------------------------------------------------
// Class APIs
void Class_new(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const v8::String::Utf8Value name(arguments[0]);
    char* className = new char[name.length() + 1];
    std::strcpy(className, *name);
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
    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::String::New(metaClass->name));
}

void Class_base(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass->base)));
}

void Class_methodCount(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Uint32::New(metaClass->methods.size()));
}

void Class_method(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    std::size_t index = arguments[1]->Uint32Value();
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass->methods[index])));
}

void Class_enumCount(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Int32::New(metaClass->enums.size()));
}

void Class_enum(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    std::size_t index = arguments[1]->Uint32Value();
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass->enums[index])));
}

//----------------------------------------------------------------------------------------------
// Method APIs
void Method_name(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaMethod* metaMethod = cast(MetaMethod, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::String::New(metaMethod->name));
}

void Method_type(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaMethod* metaMethod = cast(MetaMethod, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Uint32::New(metaMethod->type));
}

void Method_call(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    // TODO:
}

//----------------------------------------------------------------------------------------------
// Enum APIs
void Enum_name(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaEnum* metaEnum = cast(MetaEnum, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::String::New(metaEnum->name));
}

void Enum_values(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaEnum* metaEnum = cast(MetaEnum, arguments[0]->IntegerValue());
    Iterator* iterator = newIterator(metaEnum->values);
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(iterator)));
}

//----------------------------------------------------------------------------------------------
// Object APIs
void Object_new(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    Object* object = metaClass->create(metaClass);
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(object)));
}

void Object_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const Object* object = cast(Object, arguments[0]->IntegerValue());
    delete object;
}

void Object_class(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    v8::HandleScope handleScope;
    const Object* object = cast(Object, arguments[0]->IntegerValue());
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(object->metaClass())));
}

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
void ClassRegistry_register(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    const MetaClass* metaClass = cast(MetaClass, arguments[0]->IntegerValue());
    ClassRegistry::instance().registerClass(metaClass);
}

void ClassRegistry_class(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    const v8::String::Utf8Value name(arguments[0]);
    const MetaClass* metaClass = ClassRegistry::instance().findClass(*name);
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(metaClass)));
}

void ClassRegistry_classes(const v8::FunctionCallbackInfo<v8::Value>& arguments) {
    Iterator* iterator = newIterator(ClassRegistry::instance().registeredClasses());
    arguments.GetReturnValue().Set(v8::Number::New(asHandle(iterator)));
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
