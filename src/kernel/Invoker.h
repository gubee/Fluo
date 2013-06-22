/*
 * Invoker.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef INVOKER_H_
#define INVOKER_H_

#include "CoreType.h"

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
    virtual void invoke(Object* object, CallContext* callContext) {
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

    virtual void invoke(Object* object, CallContext* callContext) {
        ReturnType result = (static_cast<ClassType*>(object)->*member)();
        // TODO:
        //CallStack < ReturnType > ::push(result);
        //callContext->set(2, result);
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
    virtual void invoke(Object* object, CallContext* callContext) {
    }
};

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type
>
struct GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type, void, void> : Invoker {
    virtual void invoke(Object* object, CallContext* callContext) {
    }
};

template <
    typename ClassType, typename ReturnType,
    typename Argument0Type, typename Argument1Type, typename Argument2Type
>
struct GenericInvoker<ClassType, ReturnType, Argument0Type, Argument1Type, Argument2Type, void> : Invoker {
    virtual void invoke(Object* object, CallContext* callContext) {
    }
};

template <
    typename ClassType
>
struct GenericInvoker<ClassType, void, void, void, void, void> : Invoker {
    virtual void invoke(Object* object, CallContext* callContext) {
    }
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

    virtual void invoke(Object* object, CallContext* callContext) {
        typedef typename ArgumentType<Argument0Type>::type Type0;
        // TODO:
        //Type0 value = CallStack < Type0 > ::pop();
        //Type0 value = Type0();
        //callContext->get(2, value);
        //(static_cast<ClassType*>(object)->*member)(value);
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
    virtual void invoke(Object* object, CallContext* callContext) {
    }
};

template <
    typename ClassType,
    typename Argument0Type, typename Argument1Type, typename Argument2Type
>
struct GenericInvoker<ClassType, void, Argument0Type, Argument1Type, Argument2Type, void> : Invoker {
    virtual void invoke(Object* object, CallContext* callContext) {
    }
};

#endif /* INVOKER_H_ */
