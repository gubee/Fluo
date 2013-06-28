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

#define DEFINE_TYPE(type, code)      template <> struct TypeOf<type> { enum { value = code }; };

template <typename T>
struct TypeOf {
    enum {
        value = UndefinedType
    };
};

DEFINE_TYPE(bool, BoolType);
DEFINE_TYPE(int, IntType);
DEFINE_TYPE(float, RealType);
DEFINE_TYPE(const char*, StringType);
DEFINE_TYPE(std::string, StringType);
DEFINE_TYPE(List*, ListType);
DEFINE_TYPE(Map*, MapType);
// TODO:
//DEFINE_TYPE(Script*, ScriptType);
DEFINE_TYPE(Object*, ObjectType);

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
inline T fromValue(ValueReference value) {
    return T();
}

template <typename T, typename U>
inline Value toValue(U value) {
    return Value();
}

#if defined(F_RUNTIME_EMSCRIPTEN)
#elif defined(F_RUNTIME_FLASCC)
#elif defined(F_RUNTIME_V8)

template <>
inline bool fromValue<bool>(ValueReference value) {
    return value->BooleanValue();
}

template <>
inline Value toValue<bool>(bool value) {
    return v8::Boolean::New(value);
}

template <>
inline int fromValue<int>(ValueReference value) {
    return value->Int32Value();
}

template <>
inline Value toValue<int>(int value) {
    return v8::Integer::New(value);
}

template <>
inline float fromValue<float>(ValueReference value) {
    return value->NumberValue();
}

template <>
inline Value toValue<float>(float value) {
    return v8::Number::New(value);
}

template <>
inline std::string fromValue<std::string>(ValueReference value) {
    const v8::String::Utf8Value utf8(value);
    return *utf8;
}

template <>
inline Value toValue<std::string>(const std::string& value) {
    return v8::String::New(value.c_str());
}

template <>
inline List* fromValue<List*>(ValueReference value) {
    return 0;
}

template <>
inline Value toValue<List*>(List* value) {
    return v8::Number::New(asHandle(value));
}

template <>
inline Map* fromValue<Map*>(ValueReference value) {
    return 0;
}

template <>
inline Value toValue<Map*>(Map* value) {
    return v8::Number::New(asHandle(value));
}

// TODO:
//template <>
//inline Script* fromValue<Script*>(ValueReference value) {
//    return 0;
//}

//template <>
//inline Value toValue<Script*>(Script* value) {
//    return v8::Number::New(asHandle(value));
//}

template <>
inline Object* fromValue<Object*>(ValueReference value) {
    return cast(Object, value->IntegerValue());
}

template <>
inline Value toValue<Object*>(Object* value) {
    return v8::Number::New(asHandle(value));
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
