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
    typename Class, typename Return,
    typename Argument0 = void, typename Argument1 = void,
    typename Argument2 = void, typename Argument3 = void
>
struct GenericInvoker : Invoker {
    virtual void invoke() {
    }
};

//----------------------------------------------------------------------------------------------
template <
    typename Class, typename Return
>
struct GenericInvoker<Class, Return, void, void, void, void> : Invoker {
    typedef Return (Class::*MemberPtr)();
    typedef Return (Class::*ConstMemberPtr)() const;

    GenericInvoker(MemberPtr member)
        : member(member) {
    }

    GenericInvoker(ConstMemberPtr member)
        : constMember(member) {
    }

    virtual void invoke() {
        Object* object = 0;
        internals::StackFrame_get(0, object);
        Return result = (static_cast<Class*>(object)->*member)();
        internals::StackFrame_set(result);
    }

    union {
        MemberPtr member;
        ConstMemberPtr constMember;
    };
};

template <
    typename Class, typename Return,
    typename Argument0
>
struct GenericInvoker<Class, Return, Argument0, void, void, void> : Invoker {
    virtual void invoke() {
    }
};

template <
    typename Class, typename Return,
    typename Argument0, typename Argument1
>
struct GenericInvoker<Class, Return, Argument0, Argument1, void, void> : Invoker {
    virtual void invoke() {
    }
};

template <
    typename Class, typename Return,
    typename Argument0, typename Argument1, typename Argument2
>
struct GenericInvoker<Class, Return, Argument0, Argument1, Argument2, void> : Invoker {
    virtual void invoke() {
    }
};

template <
    typename Class
>
struct GenericInvoker<Class, void, void, void, void, void> : Invoker {
    typedef void (Class::*MemberPtr)();
    typedef void (Class::*ConstMemberPtr)() const;

    GenericInvoker(MemberPtr member)
        : member(member) {
    }

    GenericInvoker(ConstMemberPtr member)
        : constMember(member) {
    }

    virtual void invoke() {
        Object* object = 0;
        internals::StackFrame_get(0, object);
        (static_cast<Class*>(object)->*member)();
    }

    union {
        MemberPtr member;
        ConstMemberPtr constMember;
    };
};

template <
    typename Class,
    typename Argument0
>
struct GenericInvoker<Class, void, Argument0, void, void, void> : Invoker {
    typedef void (Class::*MemberPtr)(Argument0);
    typedef void (Class::*ConstMemberPtr)(Argument0) const;

    GenericInvoker(MemberPtr member)
        : member(member) {
    }

    GenericInvoker(ConstMemberPtr member)
        : constMember(member) {
    }

    virtual void invoke() {
        typedef typename ArgumentType<Argument0>::type Type0;

        Object* object = 0;
        Type0 value0 = Type0();
        internals::StackFrame_get(0, object);
        internals::StackFrame_get(1, value0);
        (static_cast<Class*>(object)->*member)(value0);
    }

    union {
        MemberPtr member;
        ConstMemberPtr constMember;
    };
};

template <
    typename Class,
    typename Argument0, typename Argument1
>
struct GenericInvoker<Class, void, Argument0, Argument1, void, void> : Invoker {
    virtual void invoke() {
    }
};

template <
    typename Class,
    typename Argument0, typename Argument1, typename Argument2
>
struct GenericInvoker<Class, void, Argument0, Argument1, Argument2, void> : Invoker {
    virtual void invoke() {
    }
};

//----------------------------------------------------------------------------------------------
template <
    typename Class, typename Return
>
Invoker* newInvoker(Return (Class::*method)()) {
    typedef GenericInvoker<Class, Return> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return,
    typename Argument0
>
Invoker* newInvoker(Return (Class::*method)(Argument0)) {
    typedef GenericInvoker<Class, Return, Argument0> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return,
    typename Argument0, typename Argument1
>
Invoker* newInvoker(Return (Class::*method)(Argument0, Argument1)) {
    typedef GenericInvoker<Class, Return, Argument0, Argument1> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return,
    typename Argument0, typename Argument1,
    typename Argument2
>
Invoker* newInvoker(Return (Class::*method)(Argument0, Argument1, Argument2)) {
    typedef GenericInvoker<Class, Return, Argument0, Argument1, Argument2> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return,
    typename Argument0, typename Argument1,
    typename Argument2, typename Argument3
>
Invoker* newInvoker(Return (Class::*method)(Argument0, Argument1, Argument2, Argument3)) {
    typedef GenericInvoker<Class, Return, Argument0, Argument1, Argument2, Argument3> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return
>
Invoker* newInvoker(Return (Class::*method)() const) {
    typedef GenericInvoker<Class, Return> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return,
    typename Argument0
>
Invoker* newInvoker(Return (Class::*method)(Argument0) const) {
    typedef GenericInvoker<Class, Return, Argument0> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return,
    typename Argument0, typename Argument1
>
Invoker* newInvoker(Return (Class::*method)(Argument0, Argument1) const) {
    typedef GenericInvoker<Class, Return, Argument0, Argument1> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return,
    typename Argument0, typename Argument1,
    typename Argument2
>
Invoker* newInvoker(Return (Class::*method)(Argument0, Argument1, Argument2) const) {
    typedef GenericInvoker<Class, Return, Argument0, Argument1, Argument2> InvokerType;
    return new InvokerType(method);
}

template <
    typename Class, typename Return,
    typename Argument0, typename Argument1,
    typename Argument2, typename Argument3
>
Invoker* newInvoker(Return (Class::*method)(Argument0, Argument1, Argument2, Argument3) const) {
    typedef GenericInvoker<Class, Return, Argument0, Argument1, Argument2, Argument3> InvokerType;
    return new InvokerType(method);
}

#endif /* INVOKER_H_ */
