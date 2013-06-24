/*
 * CoreType.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef CORETYPE_H_
#define CORETYPE_H_

#include <vector>
#include "Point.h"
#include "Size.h"
#include "Rect.h"

//----------------------------------------------------------------------------------------------
// Forward Declarations
class Object;
struct List;
struct Map;

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
// Argument
struct Argument {
    Type type;
    union {
        bool boolean;
        int integer;
        float real;
        char* string;
        Point point;
        Size size;
        Rect rect;
        List* list;
        Map* map;
        Object* object;
        //TODO:
        //Script* script;

        const char* constString;
        const List* constList;
        const Map* constMap;
        const Object* constObject;
        //TODO:
        //const Script* constScript;
    };
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

    virtual void invoke(Object* object) = 0;
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
