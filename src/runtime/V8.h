/*
 * V8.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef RUNTIME_V8_H_
#define RUNTIME_V8_H_

#if defined(F_RUNTIME_V8)
#include <v8.h>
#include "kernel/CoreType.h"

//----------------------------------------------------------------------------------------------
// StackFrame APIs
/*
    [PROTOTYPES]
    StackFrame* StackFrame_top();
    StackFrame* StackFrame_push();
    void StackFrame_pop();
*/
v8::Handle<v8::Value> StackFrame_top(const v8::Arguments& arguments);
v8::Handle<v8::Value> StackFrame_push(const v8::Arguments& arguments);
v8::Handle<v8::Value> StackFrame_pop(const v8::Arguments& arguments);

//----------------------------------------------------------------------------------------------
// List APIs
/*
    [PROTOTYPES]
    List* List_new(Type type);
    void List_delete(List* list);
    void List_append(List* list, Value value);
    void List_remove(List* list, Value value, bool removeAll);
    void List_removeAt(List* list, int index);
    int List_count(List* list);
    int List_indexOf(List* list, Value value);
    Value List_at(List* list, int index);
    void List_setAt(List* list, int index, Value value);
*/
v8::Handle<v8::Value> List_new(const v8::Arguments& arguments);
v8::Handle<v8::Value> List_delete(const v8::Arguments& arguments);
v8::Handle<v8::Value> List_append(const v8::Arguments& arguments);
v8::Handle<v8::Value> List_remove(const v8::Arguments& arguments);
v8::Handle<v8::Value> List_removeAt(const v8::Arguments& arguments);
v8::Handle<v8::Value> List_count(const v8::Arguments& arguments);
v8::Handle<v8::Value> List_indexOf(const v8::Arguments& arguments);
v8::Handle<v8::Value> List_at(const v8::Arguments& arguments);
v8::Handle<v8::Value> List_setAt(const v8::Arguments& arguments);

//----------------------------------------------------------------------------------------------
// Map APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Class APIs
/*
    [PROTOTYPES]
    MetaClass* Class_new(const char* name, const MetaClass* base);
    MetaMethod* Class_defineMethod(MetaClass* metaClass, const char* name, MethodType: type, Script* function);
    const char* Class_name(const MetaClass* metaClass);
    const MetaClass* Class_base(const MetaClass* metaClass);
    int Class_methodCount(const MetaClass* metaClass);
    MetaMethod* Class_method(const MetaClass* metaClass, int index);
    int Class_enumCount(const MetaClass* metaClass);
    MetaEnum* Class_enum(const MetaClass* metaClass, int index);
 */
v8::Handle<v8::Value> Class_new(const v8::Arguments& arguments);
v8::Handle<v8::Value> Class_defineMethod(const v8::Arguments& arguments);
v8::Handle<v8::Value> Class_name(const v8::Arguments& arguments);
v8::Handle<v8::Value> Class_base(const v8::Arguments& arguments);
v8::Handle<v8::Value> Class_methodCount(const v8::Arguments& arguments);
v8::Handle<v8::Value> Class_method(const v8::Arguments& arguments);
v8::Handle<v8::Value> Class_enumCount(const v8::Arguments& arguments);
v8::Handle<v8::Value> Class_enum(const v8::Arguments& arguments);

//----------------------------------------------------------------------------------------------
// Method APIs
/*
    [PROTOTYPES]
    const char* Method_name(const MetaMethod* metaMethod);
    MethodType Method_type(const MetaMethod* metaMethod);
    void Method_call(const MetaMethod* metaMethod);
 */
v8::Handle<v8::Value> Method_name(const v8::Arguments& arguments);
v8::Handle<v8::Value> Method_type(const v8::Arguments& arguments);
v8::Handle<v8::Value> Method_call(const v8::Arguments& arguments);

//----------------------------------------------------------------------------------------------
// Enum APIs
/*
    [PROTOTYPES]
    const char* Enum_name(const MetaEnum* metaEnum);
    const Map* Enum_values(const MetaEnum* metaEnum);
 */
v8::Handle<v8::Value> Enum_name(const v8::Arguments& arguments);
v8::Handle<v8::Value> Enum_values(const v8::Arguments& arguments);

//----------------------------------------------------------------------------------------------
// Object APIs
/*
    [PROTOTYPES]
    Object* Object_new(const MetaClass* metaClass);
    Object* Object_delete(const Object* object);
    const MetaClass* Object_class(const Object* object);
 */
v8::Handle<v8::Value> Object_new(const v8::Arguments& arguments);
v8::Handle<v8::Value> Object_delete(const v8::Arguments& arguments);
v8::Handle<v8::Value> Object_class(const v8::Arguments& arguments);

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Script APIs
// TODO:

#endif  // F_RUNTIME_V8
#endif /* RUNTIME_V8_H_ */
