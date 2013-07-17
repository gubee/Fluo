/*
 * TypeTraits.h
 *
 *  Created on: 2013. 6. 30.
 *      Author: gubee
 */

#ifndef TYPETRAITS_H_
#define TYPETRAITS_H_

#if defined(F_RUNTIME_JAVASCRIPTCORE)
#include <JavaScriptCore/JSValueRef.h>
#include <JavaScriptCore/JSStringRef.h>
namespace JSC {
    using ::JSValueMakeBoolean;
    using ::JSValueToBoolean;
    using ::JSValueMakeNumber;
    using ::JSValueToNumber;
    using ::JSValueMakeString;
    using ::JSValueToStringCopy;
    using ::JSValueMakeUndefined;
    using ::JSStringCreateWithCharacters;
    using ::JSStringGetLength;
    using ::JSStringGetCharactersPtr;
    using ::JSStringIsEqual;
    using ::JSStringCreateWithUTF8CString;
    using ::JSStringGetMaximumUTF8CStringSize;
    using ::JSStringGetUTF8CString;
    using ::JSStringIsEqualToUTF8CString;
    using ::JSStringRetain;
    using ::JSStringRelease;
}
#endif  // F_RUNTIME_JAVASCRIPTCORE

#include "CoreType.h"
#include "StringArena.h"
// TODO:
#include "Point.h"
//#include "Size.h"
//#include "Rect.h"

//----------------------------------------------------------------------------------------------
// TypeCast
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
#endif  // F_RUNTIME_EMSCRIPTEN

#if defined(F_RUNTIME_FLASCC)
#endif  // F_RUNTIME_FLASCC

#if defined(F_RUNTIME_V8)
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
#endif  // F_RUNTIME_V8

#if defined(F_RUNTIME_SPIDERMONKEY)
#endif  // F_RUNTIME_SPIDERMONKEY

#if defined(F_RUNTIME_JAVASCRIPTCORE)
template <>
struct TypeCast<bool> {
    inline static bool fromValue(ValueReference value) {
        return JSC::JSValueToBoolean(F_RUNTIME_CONTEXT, value);
    }

    inline static Value toValue(bool value) {
        return JSC::JSValueMakeBoolean(F_RUNTIME_CONTEXT, value);
    }
};

template <>
struct TypeCast<int> {
    inline static int fromValue(ValueReference value) {
        return JSC::JSValueToNumber(F_RUNTIME_CONTEXT, value, 0);
    }

    inline static Value toValue(int value) {
        return JSC::JSValueMakeNumber(F_RUNTIME_CONTEXT, value);
    }
};

template <>
struct TypeCast<float> {
    inline static float fromValue(ValueReference value) {
        return JSC::JSValueToNumber(F_RUNTIME_CONTEXT, value, 0);
    }

    inline static Value toValue(float value) {
        return JSC::JSValueMakeNumber(F_RUNTIME_CONTEXT, value);
    }
};

template <>
struct TypeCast<std::string> {
    inline static std::string fromValue(ValueReference value) {
        JSC::JSStringRef data = JSC::JSValueToStringCopy(F_RUNTIME_CONTEXT, value, 0);
        size_t bufferSize = JSC::JSStringGetMaximumUTF8CStringSize(data);

        F_RUNTIME_STRINGARENA(buffer, bufferSize);
        JSC::JSStringGetUTF8CString(data, buffer, bufferSize);
        JSC::JSStringRelease(data);
        return buffer;
    }

    inline static Value toValue(const std::string& value) {
        JSC::JSStringRef data = JSC::JSStringCreateWithUTF8CString(value.c_str());
        JSC::JSValueRef result = JSC::JSValueMakeString(F_RUNTIME_CONTEXT, data);
        JSC::JSStringRelease(data);
        return result;
    }
};

template <typename T>
struct TypeCast<T*> {
    inline static T* fromValue(ValueReference value) {
        return cast(T, asInteger(JSC::JSValueToNumber(F_RUNTIME_CONTEXT, value, 0)));
    }

    template <typename U>
    inline static Value toValue(U* value) {
        return JSC::JSValueMakeNumber(F_RUNTIME_CONTEXT, asHandle(value));
    }
};

inline Value undefined() {
    return JSC::JSValueMakeUndefined(F_RUNTIME_CONTEXT);
}

#endif  // F_RUNTIME_JAVASCRIPTCORE

//----------------------------------------------------------------------------------------------
// Meta-Programming Utilities
template <typename T>
struct to_type {
    static const int value = UndefinedType;
};

template <typename T>
struct to_argument {
    typedef T result;
};

template <typename T>
struct from_argument {
    typedef T result;
};

template <typename T>
struct from_argument<const T> {
    typedef T result;
};

template <typename T>
struct from_argument<const T&> {
    typedef T result;
};

#define DEFINE_TOTYPE(type, code)                                           \
    template <> struct to_type<type> { static const Type value = code; };

#define DEFINE_TOARGUMENT_AS_NONSCALAR(type)                                \
    template <> struct to_argument<type> { typedef const type& result; };

DEFINE_TOTYPE(bool, BoolType);
DEFINE_TOTYPE(int, IntType);
DEFINE_TOTYPE(float, RealType);
DEFINE_TOTYPE(const char*, StringType);
DEFINE_TOTYPE(std::string, StringType);
DEFINE_TOTYPE(Point, PointType);
//DEFINE_TOTYPE(Size, SizeType);
//DEFINE_TOTYPE(Rect, RectType);
DEFINE_TOTYPE(List*, ListType);
DEFINE_TOTYPE(Map*, MapType);
// TODO:
//DEFINE_TOTYPE(Script*, ScriptType);
DEFINE_TOTYPE(Object*, ObjectType);

DEFINE_TOARGUMENT_AS_NONSCALAR(Point);
//DEFINE_TOARGUMENT_AS_NONSCALAR(Size);
//DEFINE_TOARGUMENT_AS_NONSCALAR(Rect);

#define F_TEMPLATE_FORMAL_LIST      typename Argument0 = void, typename Argument1 = void, typename Argument2 = void, typename Argument3 = void

#define F_TEMPLATE_FORMAL_LIST_0
#define F_TEMPLATE_FORMAL_LIST_1    typename Argument0
#define F_TEMPLATE_FORMAL_LIST_2    typename Argument0, typename Argument1
#define F_TEMPLATE_FORMAL_LIST_3    typename Argument0, typename Argument1, typename Argument2
#define F_TEMPLATE_FORMAL_LIST_4    typename Argument0, typename Argument1, typename Argument2, typename Argument3

#define F_TEMPLATE_ACTUAL_LIST_0
#define F_TEMPLATE_ACTUAL_LIST_1    Argument0
#define F_TEMPLATE_ACTUAL_LIST_2    Argument0, Argument1
#define F_TEMPLATE_ACTUAL_LIST_3    Argument0, Argument1, Argument2
#define F_TEMPLATE_ACTUAL_LIST_4    Argument0, Argument1, Argument2, Argument3

#define F_FUNCTION_FORMAL_LIST_1            \
    const Argument0& value0

#define F_FUNCTION_FORMAL_LIST_2            \
    const Argument0& value0,                \
    const Argument1& value1

#define F_FUNCTION_FORMAL_LIST_3            \
    const Argument0& value0,                \
    const Argument1& value1,                \
    const Argument2& value2

#define F_FUNCTION_FORMAL_LIST_4            \
    const Argument0& value0,                \
    const Argument1& value1,                \
    const Argument2& value2,                \
    const Argument3& value3

#endif /* TYPETRAITS_H_ */
