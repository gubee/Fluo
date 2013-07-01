/*
 * Invoker.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef INVOKER_H_
#define INVOKER_H_

#include "CoreType.h"
#include "TypeTraits.h"
#include "StackFrame.h"

//----------------------------------------------------------------------------------------------
// Utilities
#define F_DECLARE_GENERIC_INVOKER(returnType, argumentList)             \
    typedef returnType (Class::*MemberPtr)(argumentList);               \
    typedef returnType (Class::*ConstMemberPtr)(argumentList) const;    \
                                                                        \
    GenericInvoker(MemberPtr member)                                    \
        : member(member) {                                              \
    }                                                                   \
                                                                        \
    GenericInvoker(ConstMemberPtr member)                               \
        : constMember(member) {                                         \
    }                                                                   \
                                                                        \
    union {                                                             \
        MemberPtr member;                                               \
        ConstMemberPtr constMember;                                     \
    };

namespace internals {
//----------------------------------------------------------------------------------------------
// GenericInvoker
    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST>
    struct GenericInvoker : Invoker {
        virtual void invoke() {
        }
    };

//----------------------------------------------------------------------------------------------
    template <typename Class, typename Return>
    struct GenericInvoker<Class, Return> : Invoker {
        F_DECLARE_GENERIC_INVOKER(Return, F_TEMPLATE_ACTUAL_LIST_0)

        virtual void invoke() {
            Object* object = 0;
            StackFrame_get(0, object);
            Return result = (static_cast<Class*>(object)->*member)();
            StackFrame_set(result);
        }
    };

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_1>
    struct GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_1> : Invoker {
        F_DECLARE_GENERIC_INVOKER(Return, F_TEMPLATE_ACTUAL_LIST_1)

        virtual void invoke() {
            typedef typename from_argument<Argument0>::result Type0;

            Object* object = 0;
            Type0 value0 = Type0();
            StackFrame_get(0, object);
            StackFrame_get(1, value0);
            Return result = (static_cast<Class*>(object)->*member)(value0);
            StackFrame_set(result);
        }
    };

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_2>
    struct GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_2> : Invoker {
        F_DECLARE_GENERIC_INVOKER(Return, F_TEMPLATE_ACTUAL_LIST_2)

        virtual void invoke() {
            typedef typename from_argument<Argument0>::result Type0;
            typedef typename from_argument<Argument1>::result Type1;

            Object* object = 0;
            Type0 value0 = Type0();
            Type1 value1 = Type1();
            StackFrame_get(0, object);
            StackFrame_get(1, value0);
            StackFrame_get(2, value1);
            Return result = (static_cast<Class*>(object)->*member)(value0, value1);
            StackFrame_set(result);
        }
    };

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_3>
    struct GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_3> : Invoker {
        F_DECLARE_GENERIC_INVOKER(Return, F_TEMPLATE_ACTUAL_LIST_3)

        virtual void invoke() {
            typedef typename from_argument<Argument0>::result Type0;
            typedef typename from_argument<Argument1>::result Type1;
            typedef typename from_argument<Argument2>::result Type2;

            Object* object = 0;
            Type0 value0 = Type0();
            Type1 value1 = Type1();
            Type2 value2 = Type2();
            StackFrame_get(0, object);
            StackFrame_get(1, value0);
            StackFrame_get(2, value1);
            StackFrame_get(3, value2);
            Return result = (static_cast<Class*>(object)->*member)(value0, value1, value2);
            StackFrame_set(result);
        }
    };

    template <typename Class>
    struct GenericInvoker<Class, void> : Invoker {
        F_DECLARE_GENERIC_INVOKER(void, F_TEMPLATE_ACTUAL_LIST_0)

        virtual void invoke() {
            Object* object = 0;
            StackFrame_get(0, object);
            (static_cast<Class*>(object)->*member)();
        }
    };

    template <typename Class, F_TEMPLATE_FORMAL_LIST_1>
    struct GenericInvoker<Class, void, F_TEMPLATE_ACTUAL_LIST_1> : Invoker {
        F_DECLARE_GENERIC_INVOKER(void, F_TEMPLATE_ACTUAL_LIST_1)

        virtual void invoke() {
            typedef typename from_argument<Argument0>::result Type0;

            Object* object = 0;
            Type0 value0 = Type0();
            StackFrame_get(0, object);
            StackFrame_get(1, value0);
            (static_cast<Class*>(object)->*member)(value0);
        }
    };

    template <typename Class, F_TEMPLATE_FORMAL_LIST_2>
    struct GenericInvoker<Class, void, F_TEMPLATE_ACTUAL_LIST_2> : Invoker {
        F_DECLARE_GENERIC_INVOKER(void, F_TEMPLATE_ACTUAL_LIST_2)

        virtual void invoke() {
            typedef typename from_argument<Argument0>::result Type0;
            typedef typename from_argument<Argument1>::result Type1;

            Object* object = 0;
            Type0 value0 = Type0();
            Type1 value1 = Type1();
            StackFrame_get(0, object);
            StackFrame_get(1, value0);
            StackFrame_get(2, value1);
            (static_cast<Class*>(object)->*member)(value0, value1);
        }
    };

    template <typename Class, F_TEMPLATE_FORMAL_LIST_3>
    struct GenericInvoker<Class, void, F_TEMPLATE_ACTUAL_LIST_3> : Invoker {
        F_DECLARE_GENERIC_INVOKER(void, F_TEMPLATE_ACTUAL_LIST_3)

        virtual void invoke() {
            typedef typename from_argument<Argument0>::result Type0;
            typedef typename from_argument<Argument1>::result Type1;
            typedef typename from_argument<Argument2>::result Type2;

            Object* object = 0;
            Type0 value0 = Type0();
            Type1 value1 = Type1();
            Type2 value2 = Type2();
            StackFrame_get(0, object);
            StackFrame_get(1, value0);
            StackFrame_get(2, value1);
            StackFrame_get(3, value2);
            (static_cast<Class*>(object)->*member)(value0, value1, value2);
        }
    };

//----------------------------------------------------------------------------------------------
    inline Invoker* newInvoker(none* (Object::*method)()) {
        return 0;
    }

    template <typename Class, typename Return>
    Invoker* newInvoker(Return (Class::*method)()) {
        typedef GenericInvoker<Class, Return> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_1>
    Invoker* newInvoker(Return (Class::*method)(F_TEMPLATE_ACTUAL_LIST_1)) {
        typedef GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_1> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_2>
    Invoker* newInvoker(Return (Class::*method)(F_TEMPLATE_ACTUAL_LIST_2)) {
        typedef GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_2> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_3>
    Invoker* newInvoker(Return (Class::*method)(F_TEMPLATE_ACTUAL_LIST_3)) {
        typedef GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_3> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_4>
    Invoker* newInvoker(Return (Class::*method)(F_TEMPLATE_ACTUAL_LIST_4)) {
        typedef GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_4> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return>
    Invoker* newInvoker(Return (Class::*method)() const) {
        typedef GenericInvoker<Class, Return> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_1>
    Invoker* newInvoker(Return (Class::*method)(F_TEMPLATE_ACTUAL_LIST_1) const) {
        typedef GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_1> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_2>
    Invoker* newInvoker(Return (Class::*method)(F_TEMPLATE_ACTUAL_LIST_2) const) {
        typedef GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_2> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_3>
    Invoker* newInvoker(Return (Class::*method)(F_TEMPLATE_ACTUAL_LIST_3) const) {
        typedef GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_3> InvokerType;
        return new InvokerType(method);
    }

    template <typename Class, typename Return, F_TEMPLATE_FORMAL_LIST_4>
    Invoker* newInvoker(Return (Class::*method)(F_TEMPLATE_ACTUAL_LIST_4) const) {
        typedef GenericInvoker<Class, Return, F_TEMPLATE_ACTUAL_LIST_4> InvokerType;
        return new InvokerType(method);
    }
}   // namespace internals

#endif /* INVOKER_H_ */
