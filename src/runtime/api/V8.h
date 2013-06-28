/*
 * V8.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef RUNTIME_V8_H_
#define RUNTIME_V8_H_

#if defined(F_RUNTIME_V8)
#include "kernel/CoreType.h"

//----------------------------------------------------------------------------------------------
// API Prototype
typedef void (*APIPrototype)(const v8::FunctionCallbackInfo<v8::Value>&);

//----------------------------------------------------------------------------------------------
// StackFrame APIs
/*
    [PROTOTYPES]
    StackFrame* StackFrame_top();
    StackFrame* StackFrame_push();
    void StackFrame_pop();
*/
void StackFrame_top(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void StackFrame_push(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void StackFrame_pop(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// List APIs
/*
    [PROTOTYPES]
    List* List_new(Type type);
    void List_delete(List* list);
    void List_append(List* list, ValueReference value);
    void List_remove(List* list, ValueReference value, bool removeAll);
    void List_removeAt(List* list, int index);
    int List_count(List* list);
    int List_indexOf(List* list, ValueReference value);
    Value List_at(List* list, int index);
    void List_setAt(List* list, int index, ValueReference value);
*/
void List_new(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void List_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void List_append(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void List_remove(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void List_removeAt(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void List_count(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void List_indexOf(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void List_at(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void List_setAt(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// Map APIs
/*
     [PROTOTYPES]
     Map* Map_new(Type type);
     void Map_delete(Map* map);
     void Map_insert(Map* map, const char* name, ValueReference value);
     void Map_remove(Map* map, const char* name);
     int Map_count(Map* map);
     const List* Map_names(Map* map);
     Value Map_value(Map* map, const char* name);
 */
void Map_new(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Map_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Map_insert(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Map_remove(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Map_count(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Map_names(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Map_value(const v8::FunctionCallbackInfo<v8::Value>& arguments);

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
void Class_new(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_defineMethod(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_name(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_base(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_methodCount(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_method(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_enumCount(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_enum(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// Method APIs
/*
    [PROTOTYPES]
    const char* Method_name(const MetaMethod* metaMethod);
    MethodType Method_type(const MetaMethod* metaMethod);
    void Method_call(const MetaMethod* metaMethod);
 */
void Method_name(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Method_type(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Method_call(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// Enum APIs
/*
    [PROTOTYPES]
    const char* Enum_name(const MetaEnum* metaEnum);
    const Map* Enum_values(const MetaEnum* metaEnum);
 */
void Enum_name(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Enum_values(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// Object APIs
/*
    [PROTOTYPES]
    Object* Object_new(const MetaClass* metaClass);
    void Object_delete(const Object* object);
    const MetaClass* Object_class(const Object* object);
 */
void Object_new(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Object_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Object_class(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Script APIs
// TODO:

#endif  // F_RUNTIME_V8
#endif /* RUNTIME_V8_H_ */
