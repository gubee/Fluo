/*
 * Object.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include "kernel/MetaObject.h"

class Object {
    BEGIN_CLASS(Object, none)
        PROPERTY(std::string, "objectName", objectName, setObjectName)
    END_CLASS()

public:
    Object();
    virtual ~Object();

    std::string objectName() const;
    void setObjectName(const std::string& value);

private:
    std::string     m_objectName;
};

#endif /* OBJECT_H_ */
