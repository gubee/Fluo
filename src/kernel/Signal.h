/*
 * Signal.h
 *
 *  Created on: 2013. 6. 30.
 *      Author: gubee
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <list>
#include "CoreType.h"
#include "TypeTraits.h"
#include "StackFrame.h"

//----------------------------------------------------------------------------------------------
// Forward Declarations
class Signal;

namespace internals {
//----------------------------------------------------------------------------------------------
// GenericSignalIndexer<>
    template <typename Class>
    struct GenericSignalIndexer : SignalIndexer {
        typedef Signal (Class::*MemberPtr);

        GenericSignalIndexer(MemberPtr member)
            : member(member) {
        }

        virtual ~GenericSignalIndexer() {
        }

        virtual Signal& operator()(Object* object) const {
            return (static_cast<Class*>(object)->*member);
        }

        MemberPtr member;
    };

    template <typename Class>
    SignalIndexer* newSignalIndexer(Signal (Class::*member)) {
        return new GenericSignalIndexer<Class>(member);
    }
}   // namespace internals

//----------------------------------------------------------------------------------------------
// Signal
class Signal {
public:
    Signal();
    ~Signal();

    inline bool empty() const;
    void connect(Object* receiver, const MetaMethod* method);
    void disconnect(Object* receiver, const MetaMethod* method);
    void emit() const;

    template <F_TEMPLATE_FORMAL_LIST_1>
    void emit(F_FUNCTION_FORMAL_LIST_1) const {
        if (m_slots.empty())
            return;

        internals::StackFrame_push();
        internals::StackFrame_set((Object*)0);
        internals::StackFrame_set(value0);
        invokeSlots();
        internals::StackFrame_pop();
    }

    template <F_TEMPLATE_FORMAL_LIST_2>
    void emit(F_FUNCTION_FORMAL_LIST_2) const {
        if (m_slots.empty())
            return;

        internals::StackFrame_push();
        internals::StackFrame_set((Object*)0);
        internals::StackFrame_set(value0);
        internals::StackFrame_set(value1);
        invokeSlots();
        internals::StackFrame_pop();
    }

    template <F_TEMPLATE_FORMAL_LIST_3>
    void emit(F_FUNCTION_FORMAL_LIST_3) const {
        if (m_slots.empty())
            return;

        internals::StackFrame_push();
        internals::StackFrame_set((Object*)0);
        internals::StackFrame_set(value0);
        internals::StackFrame_set(value1);
        internals::StackFrame_set(value2);
        invokeSlots();
        internals::StackFrame_pop();
    }

    template <F_TEMPLATE_FORMAL_LIST_4>
    void emit(F_FUNCTION_FORMAL_LIST_4) const {
        if (m_slots.empty())
            return;

        internals::StackFrame_push();
        internals::StackFrame_set((Object*)0);
        internals::StackFrame_set(value0);
        internals::StackFrame_set(value1);
        internals::StackFrame_set(value2);
        internals::StackFrame_set(value3);
        invokeSlots();
        internals::StackFrame_pop();
    }

private:
    void invokeSlots() const;

private:
    typedef std::list<std::pair<Object*, const MetaMethod*> > Slots;

    Slots m_slots;
};

inline bool Signal::empty() const {
    return m_slots.empty();
}

#endif /* SIGNAL_H_ */
