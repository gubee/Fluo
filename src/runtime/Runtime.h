/*
 * Runtime.h
 *
 *  Created on: 2013. 6. 27.
 *      Author: gubee
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include "kernel/CoreType.h"

//----------------------------------------------------------------------------------------------
// Runtime APIs
#define F_RUNTIME_API(returnType, functionName)         \
    F_RUNTIME_API_RETURN(returnType) functionName F_RUNTIME_API_ARGUMENTS

#define F_RUNTIME_API_CONCEPTUAL_ARGUMENTS(...)

#if defined(F_RUNTIME_EMSCRIPTEN)
#endif  // F_RUNTIME_EMSCRIPTEN

#if defined(F_RUNTIME_FLASCC)
#endif  // F_RUNTIME_FLASCC

#if defined(F_RUNTIME_V8)
#define F_RUNTIME_API_RETURN(x)     void
#define F_RUNTIME_API_ARGUMENTS     (const v8::FunctionCallbackInfo<v8::Value>&) F_RUNTIME_API_CONCEPTUAL_ARGUMENTS

typedef void (*APIPrototype)(const v8::FunctionCallbackInfo<v8::Value>&);
#endif  // F_RUNTIME_V8

#if defined(F_RUNTIME_SPIDERMONKEY)
#endif  // F_RUNTIME_SPIDERMONKEY

#if defined(F_RUNTIME_JAVASCRIPTCORE)
#define F_RUNTIME_API_RETURN(x)     JSC::JSValueRef
#define F_RUNTIME_API_ARGUMENTS     (JSC::JSContextRef, JSC::JSObjectRef, JSC::JSObjectRef, size_t, const JSC::JSValueRef[], JSC::JSValueRef*) F_RUNTIME_API_CONCEPTUAL_ARGUMENTS

typedef JSValueRef (*APIPrototype)(JSC::JSContextRef, JSC::JSObjectRef, JSC::JSObjectRef, size_t, const JSC::JSValueRef[], JSC::JSValueRef*);
#endif  // F_RUNTIME_JAVASCRIPTCORE

//----------------------------------------------------------------------------------------------
// StackFrame APIs
F_RUNTIME_API(StackFrame*, StackFrame_top)();
F_RUNTIME_API(StackFrame*, StackFrame_push)();
F_RUNTIME_API(void, StackFrame_pop)();

//----------------------------------------------------------------------------------------------
// Iterator APIs
F_RUNTIME_API(void, Iterator_delete)(Iterator* iterator);
F_RUNTIME_API(const char*, Iterator_name)(Iterator* iterator);
F_RUNTIME_API(Value, Iterator_value)(Iterator* iterator);
F_RUNTIME_API(bool, Iterator_next)(Iterator* iterator);

//----------------------------------------------------------------------------------------------
// List APIs
F_RUNTIME_API(List*, List_new)(Type type);
F_RUNTIME_API(void, List_delete)(List* list);
F_RUNTIME_API(void, List_append)(List* list, ValueReference value);
F_RUNTIME_API(void, List_remove)(List* list, ValueReference value, bool removeAll);
F_RUNTIME_API(void, List_removeAt)(List* list, int index);
F_RUNTIME_API(int, List_count)(List* list);
F_RUNTIME_API(int, List_indexOf)(List* list, ValueReference value);
F_RUNTIME_API(Value, List_at)(List* list, int index);
F_RUNTIME_API(void, List_setAt)(List* list, int index, ValueReference value);

//----------------------------------------------------------------------------------------------
// Map APIs
F_RUNTIME_API(Map*, Map_new)(Type type);
F_RUNTIME_API(void, Map_delete)(Map* map);
F_RUNTIME_API(void, Map_insert)(Map* map, const char* name, ValueReference value);
F_RUNTIME_API(void, Map_remove)(Map* map, const char* name);
F_RUNTIME_API(int, Map_count)(Map* map);
F_RUNTIME_API(const List*, Map_names)(Map* map);
F_RUNTIME_API(Value, Map_value)(Map* map, const char* name);

//----------------------------------------------------------------------------------------------
// Class APIs
F_RUNTIME_API(MetaClass*, Class_new)(const char* name, const MetaClass* base);
F_RUNTIME_API(MetaMethod*, Class_defineMethod)(MetaClass* metaClass, const char* name, Script* function);
F_RUNTIME_API(MetaMethod*, Class_defineProperty)(MetaClass* metaClass, const char* name, Script* getter, Script* setter, Type type);
F_RUNTIME_API(MetaMethod*, Class_defineSignal)(MetaClass* metaClass, const char* name);
F_RUNTIME_API(const char*, Class_name)(const MetaClass* metaClass);
F_RUNTIME_API(const MetaClass*, Class_base)(const MetaClass* metaClass);
F_RUNTIME_API(int, Class_enumCount)(const MetaClass* metaClass);
F_RUNTIME_API(const MetaEnum*, Class_enum)(const MetaClass* metaClass, int index);
F_RUNTIME_API(int, Class_methodCount)(const MetaClass* metaClass);
F_RUNTIME_API(const MetaMethod*, Class_method)(const MetaClass* metaClass, int index);
F_RUNTIME_API(int, Class_propertyCount)(const MetaClass* metaClass);
F_RUNTIME_API(const MetaProperty*, Class_property)(const MetaClass* metaClass, int index);
F_RUNTIME_API(int, Class_signalCount)(const MetaClass* metaClass);
F_RUNTIME_API(const MetaSignal*, Class_signal)(const MetaClass* metaClass, int index);

//----------------------------------------------------------------------------------------------
// Enum APIs
F_RUNTIME_API(const char*, Enum_name)(const MetaEnum* metaEnum);
F_RUNTIME_API(const Map*, Enum_values)(const MetaEnum* metaEnum);

//----------------------------------------------------------------------------------------------
// Method APIs
F_RUNTIME_API(const char*, Method_name)(const MetaMethod* metaMethod);
F_RUNTIME_API(void, Method_call)(const MetaMethod* metaMethod);

//----------------------------------------------------------------------------------------------
// Property APIs
F_RUNTIME_API(const char*, Property_name)(const MetaProperty* metaProperty);
F_RUNTIME_API(Type, Property_type)(const MetaProperty* metaProperty);
F_RUNTIME_API(bool, Property_isReadOnly)(const MetaProperty* metaProperty);
F_RUNTIME_API(void, Property_read)(const MetaProperty* metaProperty);
F_RUNTIME_API(void, Property_write)(const MetaProperty* metaProperty);

//----------------------------------------------------------------------------------------------
// Signal APIs
F_RUNTIME_API(const char*, Signal_name)(const MetaSignal* metaSignal);
F_RUNTIME_API(void, Signal_connect)(const MetaSignal* metaSignal, Object* sender, Object* receiver, const MetaMethod* metaMethod);
F_RUNTIME_API(void, Signal_disconnect)(const MetaSignal* metaSignal, Object* sender, Object* receiver, const MetaMethod* metaMethod);
F_RUNTIME_API(void, Signal_emit)(const MetaSignal* metaSignal, Object* sender);

//----------------------------------------------------------------------------------------------
// Object APIs
F_RUNTIME_API(Object*, Object_new)(const MetaClass* metaClass);
F_RUNTIME_API(void, Object_delete)(const Object* object);
F_RUNTIME_API(const MetaClass*, Object_class)(const Object* object);

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
F_RUNTIME_API(void, ClassRegistry_register)(const MetaClass* metaClass);
F_RUNTIME_API(const MetaClass*, ClassRegistry_class)(const char* name);
F_RUNTIME_API(const List*, ClassRegistry_classes)();

//----------------------------------------------------------------------------------------------
// Script APIs
// TODO:

//----------------------------------------------------------------------------------------------
// class Runtime
class Runtime {
public:
    Runtime();
    ~Runtime();

    void startup();
    void shutdown();
    void runScript(const char* source);

private:
    struct Data;
    Data* m_data;
};

#endif /* RUNTIME_H_ */
