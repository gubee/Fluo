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

protected:
    void none();

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
