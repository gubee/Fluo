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
// Iterator APIs
/*
    [PROTOTYPES]
    void Iterator_delete(Iterator* iterator);
    const char* Iterator_name(Iterator* iterator);
    Value Iterator_value(Iterator* iterator);
    bool Iterator_next(Iterator* iterator);
 */
void Iterator_delete(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Iterator_name(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Iterator_value(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Iterator_next(const v8::FunctionCallbackInfo<v8::Value>& arguments);

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
    MetaMethod* Class_defineMethod(MetaClass* metaClass, const char* name, Script* function);
    MetaMethod* Class_defineProperty(MetaClass* metaClass, const char* name, Script* getter, Script* setter, Type type);
    MetaMethod* Class_defineSignal(MetaClass* metaClass, const char* name);
    const char* Class_name(const MetaClass* metaClass);
    const MetaClass* Class_base(const MetaClass* metaClass);
    int Class_enumCount(const MetaClass* metaClass);
    const MetaEnum* Class_enum(const MetaClass* metaClass, int index);
    int Class_methodCount(const MetaClass* metaClass);
    const MetaMethod* Class_method(const MetaClass* metaClass, int index);
    int Class_propertyCount(const MetaClass* metaClass);
    const MetaProperty* Class_property(const MetaClass* metaClass, int index);
    int Class_signalCount(const MetaClass* metaClass);
    const MetaSignal* Class_signal(const MetaClass* metaClass, int index);
 */
void Class_new(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_defineMethod(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_defineProperty(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_defineSignal(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_name(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_base(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_enumCount(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_enum(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_methodCount(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_method(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_propertyCount(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_property(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_signalCount(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Class_signal(const v8::FunctionCallbackInfo<v8::Value>& arguments);

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
// Method APIs
/*
    [PROTOTYPES]
    const char* Method_name(const MetaMethod* metaMethod);
    void Method_call(const MetaMethod* metaMethod);
 */
void Method_name(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Method_call(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// Property APIs
/*
    [PROTOTYPES]
    const char* Property_name(const MetaProperty* metaProperty);
    Type Property_type(const MetaProperty* metaProperty);
    bool Property_isReadOnly(const MetaProperty* metaProperty);
    void Property_read(const MetaProperty* metaProperty);
    void Property_write(const MetaProperty* metaProperty);
 */
void Property_name(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Property_type(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Property_isReadOnly(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Property_read(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Property_write(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// Signal APIs
/*
    [PROTOTYPES]
    const char* Signal_name(const MetaSignal* metaSignal);
    void Signal_connect(const MetaSignal* metaSignal, Object* sender, Object* receiver, const MetaMethod* metaMethod);
    void Signal_disconnect(const MetaSignal* metaSignal, Object* sender, Object* receiver, const MetaMethod* metaMethod);
    void Signal_emit(const MetaSignal* metaSignal, Object* sender);
 */
void Signal_name(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Signal_connect(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Signal_disconnect(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void Signal_emit(const v8::FunctionCallbackInfo<v8::Value>& arguments);

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
/*
    [PROTOTYPES]
    void ClassRegistry_register(const MetaClass* metaClass);
    const MetaClass* ClassRegistry_class(const char* name);
    const List* ClassRegistry_classes();
 */
void ClassRegistry_register(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void ClassRegistry_class(const v8::FunctionCallbackInfo<v8::Value>& arguments);
void ClassRegistry_classes(const v8::FunctionCallbackInfo<v8::Value>& arguments);

//----------------------------------------------------------------------------------------------
// Script APIs
// TODO:

#endif  // F_RUNTIME_V8
#endif /* RUNTIME_V8_H_ */
