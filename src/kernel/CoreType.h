/*
 * CoreType.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef CORETYPE_H_
#define CORETYPE_H_

#include <vector>

//----------------------------------------------------------------------------------------------
// Forward Declarations
class Object;
class CallContext;

//----------------------------------------------------------------------------------------------
// Type
enum Type {
    UndefinedType,
    BoolType,
    IntType,
    RealType,
    StringType,
    PointType,
    SizeType,
    RectType,
    ListType,
    MapType,
    ScriptType,
    ObjectType
};

typedef void* Value;
typedef int* Address;

//----------------------------------------------------------------------------------------------
// StackFrame
struct StackFrame {
    StackFrame* previousFrame;
    Address framePointer;
    int argumentCount;
    int arguments[6];           // framePointer offsets
};

//----------------------------------------------------------------------------------------------
// List
struct List {
    Type type;
};

//----------------------------------------------------------------------------------------------
// Map
struct Map {
    Type type;
};

//----------------------------------------------------------------------------------------------
struct Invoker {
    Invoker() {
    }
    virtual ~Invoker() {
    }

    virtual void invoke(Object* object, CallContext* callContext) = 0;
};

//----------------------------------------------------------------------------------------------
// MetaEnum
struct MetaEnum {
    const char* name;
    std::vector<std::pair<const char*, int> > values;
};

//----------------------------------------------------------------------------------------------
// MetaProperty
struct MetaProperty {
    const char* name;
    Invoker* getter;
    Invoker* setter;
};

//----------------------------------------------------------------------------------------------
// MetaMethod
struct MetaMethod {
    const char* name;
    Invoker* function;
};

//----------------------------------------------------------------------------------------------
// MetaClass
struct MetaClass {
    const char* name;
    const MetaClass* base;
    Object* (*create)();
    int propertyOffset;
    int methodOffset;
    std::vector<MetaProperty> properties;
    std::vector<MetaMethod> methods;
    std::vector<MetaEnum> enums;
};

struct none {
    static MetaClass* staticMetaClass() {
        return 0;
    }
};

#endif /* CORETYPE_H_ */
