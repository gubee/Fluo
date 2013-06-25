/*
 * Invoker.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef INVOKER_H_
#define INVOKER_H_

#include "CoreType.h"
#include "StackFrame.h"

//----------------------------------------------------------------------------------------------
// Utilities
template <typename T>
struct ArgumentType {
    typedef T type;
};

template <typename T>
struct ArgumentType<const T> {
    typedef T type;
};

template <typename T>
struct ArgumentType<const T&> {
    typedef T type;
};

//----------------------------------------------------------------------------------------------
// GenericInvoker
template <
    typename ClassType, typename ReturnType,
    typename Argument0Type = void, typename Argument1Type = void,
    typename Argument2Type = void, typename Argument3Type = void
>
struct GenericInvoker : Invoker {
    virtual void invoke() {
    }
};

//----------------------------------------------------------------------------------------------
template <
    typename ClassType, typename ReturnType
>
struct GenericInvoker<ClassType, ReturnType, void, void, void, void> : Invoker {
    typedef ReturnType (ClassType::*MemberPtr)();
    typedef ReturnType (ClassType::*ConstMemberPtr)() const;

    GenericInvoker(MemberPtr member)
        : member(member) {
    }

    GenericInvoker(ConstMemberPtr member)
        : constMember(member) {
    }

    virtual void invoke() {
        Object* object = 0;
        internals::StackFrame_get(0, object);
        ReturnType result = (static_cast<ClassType*>(object)->*member)();
        internals::StackFrame_set(result);
    }

    union {
        MemberPtr member;
        ConstMemberPtr constMember;
    };
};

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type
>
struct GenericInvoker<ClassType, ReturnType, Argument0Type, void, void, void> : Invoker {
    virtual void invoke() {
    }
};

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type
>
struct GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type, void, void> : Invoker {
    virtual void invoke() {
    }
};

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type, typename Argument2Type
>
struct GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type, Argument2Type, void> : Invoker {
    virtual void invoke() {
    }
};

template <
    typename ClassType
>
struct GenericInvoker<ClassType, void, void, void, void, void> : Invoker {
    typedef void (ClassType::*MemberPtr)();
    typedef void (ClassType::*ConstMemberPtr)() const;

    GenericInvoker(MemberPtr member)
        : member(member) {
    }

    GenericInvoker(ConstMemberPtr member)
        : constMember(member) {
    }

    virtual void invoke() {
        Object* object = 0;
        internals::StackFrame_get(0, object);
        (static_cast<ClassType*>(object)->*member)();
    }

    union {
        MemberPtr member;
        ConstMemberPtr constMember;
    };
};

template <
    typename ClassType,
    typename Argument0Type
>
struct GenericInvoker<ClassType, void, Argument0Type, void, void, void> : Invoker {
    typedef void (ClassType::*MemberPtr)(Argument0Type);
    typedef void (ClassType::*ConstMemberPtr)(Argument0Type) const;

    GenericInvoker(MemberPtr member)
        : member(member) {
    }

    GenericInvoker(ConstMemberPtr member)
        : constMember(member) {
    }

    virtual void invoke() {
        typedef typename ArgumentType<Argument0Type>::type Type0;

        Object* object = 0;
        Type0 value0 = Type0();
        internals::StackFrame_get(0, object);
        internals::StackFrame_get(1, value0);
        (static_cast<ClassType*>(object)->*member)(value0);
    }

    union {
        MemberPtr member;
        ConstMemberPtr constMember;
    };
};

template <
    typename ClassType,
    typename Argument0Type, typename Argument1Type
>
struct GenericInvoker<ClassType, void, Argument0Type, Argument1Type, void, void> : Invoker {
    virtual void invoke(Object* object) {
    }
};

template <
    typename ClassType,
    typename Argument0Type, typename Argument1Type, typename Argument2Type
>
struct GenericInvoker<ClassType, void, Argument0Type, Argument1Type, Argument2Type, void> : Invoker {
    virtual void invoke(Object* object) {
    }
};

//----------------------------------------------------------------------------------------------
template <
    typename ClassType, typename ReturnType
>
Invoker* newInvoker(ReturnType (ClassType::*method)()) {
    typedef GenericInvoker<ClassType, ReturnType> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type
>
Invoker* newInvoker(ReturnType (ClassType::*method)(Argument0Type)) {
    typedef GenericInvoker<ClassType, ReturnType, Argument0Type> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type
>
Invoker* newInvoker(ReturnType (ClassType::*method)(Argument0Type, Argument1Type)) {
    typedef GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type,
    typename Argument2Type
>
Invoker* newInvoker(ReturnType (ClassType::*method)(Argument0Type, Argument1Type, Argument2Type)) {
    typedef GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type, Argument2Type> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type,
    typename Argument2Type, typename Argument3Type
>
Invoker* newInvoker(ReturnType (ClassType::*method)(Argument0Type, Argument1Type, Argument2Type, Argument3Type)) {
    typedef GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type, Argument2Type, Argument3Type> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType
>
Invoker* newInvoker(ReturnType (ClassType::*method)() const) {
    typedef GenericInvoker<ClassType, ReturnType> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type
>
Invoker* newInvoker(ReturnType (ClassType::*method)(Argument0Type) const) {
    typedef GenericInvoker<ClassType, ReturnType, Argument0Type> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type
>
Invoker* newInvoker(ReturnType (ClassType::*method)(Argument0Type, Argument1Type) const) {
    typedef GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type,
    typename Argument2Type
>
Invoker* newInvoker(ReturnType (ClassType::*method)(Argument0Type, Argument1Type, Argument2Type) const) {
    typedef GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type, Argument2Type> InvokerType;
    return new InvokerType(method);
}

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type,
    typename Argument2Type, typename Argument3Type
>
Invoker* newInvoker(ReturnType (ClassType::*method)(Argument0Type, Argument1Type, Argument2Type, Argument3Type) const) {
    typedef GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type, Argument2Type, Argument3Type> InvokerType;
    return new InvokerType(method);
}

#endif /* INVOKER_H_ */
