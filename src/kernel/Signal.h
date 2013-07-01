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
// Signal
class Signal {
public:
    Signal();
    ~Signal();

    inline bool empty() const;
    void connect(Object* receiver, const MetaMethod* method);
    void disconnect(Object* receiver, const MetaMethod* method);
    void notify(const Object* sender) const;

public:
    static const Object* sender();

private:
    typedef std::list<std::pair<Object*, const MetaMethod*> > Slots;

    Slots m_slots;
    static const Object* m_sender;
};

inline bool Signal::empty() const {
    return m_slots.empty();
}

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

//----------------------------------------------------------------------------------------------
    inline void Signal_connect(SignalIndexer* indexer, Object* sender, Object* receiver, const MetaMethod* metaMethod) {
        (*indexer)(sender).connect(receiver, metaMethod);
    }

    inline void Signal_disconnect(SignalIndexer* indexer, Object* sender, Object* receiver, const MetaMethod* metaMethod) {
        (*indexer)(sender).disconnect(receiver, metaMethod);
    }

    inline void Signal_emit(SignalIndexer* indexer, Object* sender) {
        (*indexer)(sender).notify(sender);
    }
}   // namespace internals

#endif /* SIGNAL_H_ */
