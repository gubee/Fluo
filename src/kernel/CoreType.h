/*
 * CoreType.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef CORETYPE_H_
#define CORETYPE_H_

#include <inttypes.h>
#include <string>
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
class Signal;
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

//----------------------------------------------------------------------------------------------
// Address / Handle
typedef int* Address;
typedef intptr_t Handle;

#define cast(type, from)            reinterpret_cast<type*>(from)
#define asAddress(from)             reinterpret_cast<Address>(from)
#define asHandle(from)              reinterpret_cast<Handle>(from)

//----------------------------------------------------------------------------------------------
// Value / ScriptValue

#if defined(F_RUNTIME_EMSCRIPTEN)
typedef void* Value;
typedef void* ValueReference;
// TODO: ScriptValue
#elif defined(F_RUNTIME_FLASCC)
#elif defined(F_RUNTIME_V8)
typedef v8::Handle<v8::Value> Value;
typedef const v8::Handle<v8::Value>& ValueReference;
typedef v8::Handle<v8::Value> ScriptValue;
#elif defined(F_RUNTIME_SPIDERMONKEY)
typedef JS::Value Value;
typedef const JS::Value& ValueReference;
typedef JS::Value ScriptValue;
#elif defined(F_RUNTIME_JAVASCRIPTCORE)
typedef JSC::Value Value;
typedef const JSC::Value& ValueReference;
typedef JSC::Value ScriptValue;
#endif

template <typename T>
struct TypeCast {
    inline static T fromValue(ValueReference value) {
        return T();
    }

    template <typename U>
    inline static Value toValue(U value) {
        return Value();
    }
};

#if defined(F_RUNTIME_EMSCRIPTEN)
#elif defined(F_RUNTIME_FLASCC)
#elif defined(F_RUNTIME_V8)

template <>
struct TypeCast<bool> {
    inline static bool fromValue(ValueReference value) {
        return value->BooleanValue();
    }

    inline static Value toValue(bool value) {
        return v8::Boolean::New(value);
    }
};

template <>
struct TypeCast<int> {
    inline static int fromValue(ValueReference value) {
        return value->Int32Value();
    }

    inline static Value toValue(int value) {
        return v8::Integer::New(value);
    }
};

template <>
struct TypeCast<float> {
    inline static float fromValue(ValueReference value) {
        return value->NumberValue();
    }

    inline static Value toValue(float value) {
        return v8::Number::New(value);
    }
};

template <>
struct TypeCast<std::string> {
    inline static std::string fromValue(ValueReference value) {
        const v8::String::Utf8Value utf8(value);
        return *utf8;
    }

    inline static Value toValue(const std::string& value) {
        return v8::String::New(value.c_str());
    }
};

template <typename T>
struct TypeCast<T*> {
    inline static T* fromValue(ValueReference value) {
        return cast(T, value->IntegerValue());
    }

    template <typename U>
    inline static Value toValue(U* value) {
        return v8::Number::New(asHandle(value));
    }
};

inline Value undefined() {
    return v8::Undefined();
}

#elif defined(F_RUNTIME_SPIDERMONKEY)
#elif defined(F_RUNTIME_JAVASCRIPTCORE)
#endif

//----------------------------------------------------------------------------------------------
// ClassType
enum ClassType {
    NativeClass,
    DynamicClass
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
// Iterator
class Iterator {
public:
    Iterator() {
    }

    virtual ~Iterator() {
    }

    virtual const char* name() const = 0;
    virtual Value value() const = 0;
    virtual bool next() = 0;
};

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

public:
    static List* newInstance(Type type);

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
    virtual Iterator* names() const = 0;
    virtual Value value(const std::string& name) const = 0;

public:
    static Map* newInstance(Type type);

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
// SignalIndexer
struct SignalIndexer {
    SignalIndexer() {
    }
    virtual ~SignalIndexer() {
    }

    virtual Signal& operator()(Object* object) const = 0;
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
    Invoker* function;
};

//----------------------------------------------------------------------------------------------
// MetaProperty
struct MetaProperty {
    const char* name;
    Type type;
    Invoker* getter;
    Invoker* setter;
};

//----------------------------------------------------------------------------------------------
// MetaSignal
struct MetaSignal {
    const char* name;
    SignalIndexer* indexer;
};

//----------------------------------------------------------------------------------------------
// MetaClass
struct MetaClass {
    ClassType type;
    const char* name;
    const MetaClass* base;
    Object* (*create)(const MetaClass*);
    std::vector<MetaEnum*> enums;
    std::vector<MetaMethod*> methods;
    std::vector<MetaProperty*> properties;
    std::vector<MetaSignal*> signals;
};

struct none {
    static MetaClass* staticMetaClass() {
        return 0;
    }
};

#endif /* CORETYPE_H_ */
