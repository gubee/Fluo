/*
 * TypeTraits.h
 *
 *  Created on: 2013. 6. 30.
 *      Author: gubee
 */

#ifndef TYPETRAITS_H_
#define TYPETRAITS_H_

#include "CoreType.h"
// TODO:
#include "Point.h"
//#include "Size.h"
//#include "Rect.h"

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
