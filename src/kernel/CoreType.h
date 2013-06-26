/*
 * CoreType.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef CORETYPE_H_
#define CORETYPE_H_

#include <inttypes.h>
#include <vector>

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
typedef intptr_t Handle;

#define cast(type, from)            reinterpret_cast<type*>(from)
#define asAddress(from)             reinterpret_cast<Address>(from)
#define asHandle(from)              reinterpret_cast<Handle>(from)

//----------------------------------------------------------------------------------------------
// MethodType
enum MethodType {
    ReadProperty,
    WriteProperty,
    Method
};

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
        struct {
            char* pointer;
            char buffer[1];
        } string;
        float geometry[4];
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
}
#if !defined(F_RUNTIME_EMSCRIPTEN) && !defined(F_RUNTIME_FLASCC)
__attribute__((aligned(4), packed))
#endif
;

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

    virtual void invoke() = 0;
};

//----------------------------------------------------------------------------------------------
// MetaEnum
struct MetaEnum {
    const char* name;
    std::vector<std::pair<const char*, int> > values;
};

//----------------------------------------------------------------------------------------------
// MetaMethod
struct MetaMethod {
    const char* name;
    MethodType type;
    Invoker* function;
};

//----------------------------------------------------------------------------------------------
// MetaClass
struct MetaClass {
    const char* name;
    const MetaClass* base;
    Object* (*create)();
    int methodOffset;
    std::vector<MetaMethod*> methods;
    std::vector<MetaEnum*> enums;
};

struct none {
    static MetaClass* staticMetaClass() {
        return 0;
    }
};

#endif /* CORETYPE_H_ */
