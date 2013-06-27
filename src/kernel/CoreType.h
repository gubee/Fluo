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

#if defined(F_RUNTIME_EMSCRIPTEN)
#elif defined(F_RUNTIME_FLASCC)
#elif defined(F_RUNTIME_V8)
#include <v8.h>
#elif defined(F_RUNTIME_SPIDERMONKEY)
#elif defined(F_RUNTIME_JAVASCRIPTCORE)
#endif

//----------------------------------------------------------------------------------------------
// Forward Declarations
class Object;
class List;
class Map;

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

#if defined(F_RUNTIME_EMSCRIPTEN)
typedef void* Value;
typedef void* ValueReference;
#elif defined(F_RUNTIME_FLASCC)
#elif defined(F_RUNTIME_V8)
typedef v8::Handle<v8::Value> Value;
typedef const v8::Handle<v8::Value>& ValueReference;
#elif defined(F_RUNTIME_SPIDERMONKEY)
typedef JS::Value Value;
typedef const JS::Value& ValueReference;
#elif defined(F_RUNTIME_JAVASCRIPTCORE)
typedef JSC::Value Value;
typedef const JSC::Value& ValueReference;
#endif
typedef int* Address;
typedef intptr_t Handle;

#define cast(type, from)            reinterpret_cast<type*>(from)
#define asAddress(from)             reinterpret_cast<Address>(from)
#define asHandle(from)              reinterpret_cast<Handle>(from)

//----------------------------------------------------------------------------------------------
// ClassType
enum ClassType {
    NativeClass,
    DynamicClass
};

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
class List {
public:
    explicit List(Type type)
        : m_type(type) {
    }

    virtual ~List() {
    }

    inline Type type() const {
        return m_type;
    }

    virtual void append(ValueReference value) = 0;
    virtual void remove(ValueReference value, bool removeAll = true) = 0;
    virtual void removeAt(int index) = 0;
    virtual int count() const = 0;
    virtual int indexOf(ValueReference value) const = 0;
    virtual Value at(int index) const = 0;
    virtual void setAt(int index, ValueReference value) = 0;

protected:
    Type m_type;
};

//----------------------------------------------------------------------------------------------
// Map
class Map {
public:
    explicit Map(Type type)
        : m_type(type) {
    }

    virtual ~Map() {
    }

    inline Type type() const {
        return m_type;
    }

    virtual void insert(const std::string& name, ValueReference value) = 0;
    virtual void remove(const std::string& name) = 0;
    virtual int count() const = 0;
    virtual const List* names() const = 0;
    virtual Value value(const std::string& name) const = 0;

protected:
    Type m_type;
};

//----------------------------------------------------------------------------------------------
// Invoker
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
    MethodType type;
    const char* name;
    Invoker* function;
};

//----------------------------------------------------------------------------------------------
// MetaClass
struct MetaClass {
    ClassType type;
    const char* name;
    const MetaClass* base;
    Object* (*create)(const MetaClass*);
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
