/*
 * CoreObject.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef CORE_OBJECT_H_
#define CORE_OBJECT_H_

#include <string>
#include "MetaObject.h"

//----------------------------------------------------------------------------------------------
// class Object
class Object {
    BEGIN_CLASS(Object, none)
        PROPERTY("objectName", objectName, setObjectName, std::string)
    END_CLASS()

public:
    Object();
    virtual ~Object();

    std::string objectName() const;
    void setObjectName(const std::string& value);

    const MetaSignal* signal(const char* name) const;
    const MetaProperty* property(const char* name) const;
    const MetaMethod* method(const char* name) const;

    void emit(const Signal& signal) const;

    template <F_TEMPLATE_FORMAL_LIST_1>
    void emit(const Signal& signal, F_FUNCTION_FORMAL_LIST_1) const {
        if (signal.empty())
            return;

        internals::StackFrame_push();
        internals::StackFrame_set((Object*) 0);
        internals::StackFrame_set(value0);
        signal.notify(this);
        internals::StackFrame_pop();
    }

    template <F_TEMPLATE_FORMAL_LIST_2>
    void emit(const Signal& signal, F_FUNCTION_FORMAL_LIST_2) const {
        if (signal.empty())
            return;

        internals::StackFrame_push();
        internals::StackFrame_set((Object*) 0);
        internals::StackFrame_set(value0);
        internals::StackFrame_set(value1);
        signal.notify(this);
        internals::StackFrame_pop();
    }

    template <F_TEMPLATE_FORMAL_LIST_3>
    void emit(const Signal& signal, F_FUNCTION_FORMAL_LIST_3) const {
        if (signal.empty())
            return;

        internals::StackFrame_push();
        internals::StackFrame_set((Object*) 0);
        internals::StackFrame_set(value0);
        internals::StackFrame_set(value1);
        internals::StackFrame_set(value2);
        signal.notify(this);
        internals::StackFrame_pop();
    }

    template <F_TEMPLATE_FORMAL_LIST_4>
    void emit(const Signal& signal, F_FUNCTION_FORMAL_LIST_4) const {
        if (signal.empty())
            return;

        internals::StackFrame_push();
        internals::StackFrame_set((Object*) 0);
        internals::StackFrame_set(value0);
        internals::StackFrame_set(value1);
        internals::StackFrame_set(value2);
        internals::StackFrame_set(value3);
        signal.notify(this);
        internals::StackFrame_pop();
    }

public:
    struct none* none();

private:
    std::string m_objectName;
};

//----------------------------------------------------------------------------------------------
// class DynamicObject
class DynamicObject : public Object {
public:
    explicit DynamicObject(const MetaClass* metaClass);
    virtual ~DynamicObject();

    virtual const MetaClass* metaClass() const;

public:
    static Object* create(const MetaClass* metaClass);

private:
    const MetaClass* m_metaClass;
};

//----------------------------------------------------------------------------------------------
// Signal/Slot Connection
#define CONNECT(sender, signal, receiver, slot)                     \
    sender->signal.connect(receiver, receiver->method(#slot))

#define DISCONNECT(sender, signal, receiver, slot)                  \
    sender->signal.disconnect(receiver, receiver->method(#slot))

#endif /* CORE_OBJECT_H_ */
