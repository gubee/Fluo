/*
 * Signal.cpp
 *
 *  Created on: 2013. 6. 30.
 *      Author: gubee
 */

#include "Signal.h"

Signal::Signal() {
}

Signal::~Signal() {
}

void Signal::connect(Object* receiver, const MetaMethod* method) {
    // TODO: check arguments compatibility

    m_slots.push_back(std::make_pair(receiver, method));
}

void Signal::disconnect(Object* receiver, const MetaMethod* method) {
    Slots::iterator i = std::find(m_slots.begin(), m_slots.end(), std::make_pair(receiver, method));
    if (i != m_slots.end())
        m_slots.erase(i);
}

void Signal::notify(const Object* sender) const {
    m_sender = sender;

    Argument* argument = internals::StackFrame_argument(0);
    Slots::const_iterator i(m_slots.begin());
    Slots::const_iterator e(m_slots.end());
    for (; i != e; ++i) {
        Object* receiver = i->first;
        Invoker* invoker = i->second->function;
        argument->object = receiver;
        invoker->invoke();
    }

    m_sender = 0;
}

const Object* Signal::sender() {
    return m_sender;
}

const Object* Signal::m_sender = 0;
