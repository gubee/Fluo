/*
 * MetaObject.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef METAOBJECT_H_
#define METAOBJECT_H_

#include "CoreType.h"
#include "Invoker.h"

//----------------------------------------------------------------------------------------------
// Utilities
int methodOffsetOf(const MetaClass& metaClass);
void addMetaMethod(MetaClass& metaClass, const char* name, MethodType type, Invoker* invoker);

template <typename ClassType>
struct ObjectFactory {
    static Object* create(const MetaClass*) {
        return new ClassType();
    }
};

//----------------------------------------------------------------------------------------------
#define BEGIN_CLASS(classtype, basetype)                                            \
    public:                                                                         \
        virtual const MetaClass* metaClass() const {                                      \
            return classtype::staticMetaClass();                                    \
        }                                                                           \
        static const MetaClass* staticMetaClass() {                                       \
            static MetaClass metaClass = classtype::createMetaClass();              \
            return &metaClass;                                                      \
        }                                                                           \
    private:                                                                        \
        static MetaClass createMetaClass() {                                        \
            typedef classtype       ClassType;                                      \
            MetaClass metaClass;                                                    \
            metaClass.type = NativeClass;                                           \
            metaClass.name = #classtype;                                            \
            metaClass.base = basetype::staticMetaClass();                           \
            metaClass.create = &ObjectFactory<ClassType>::create;                   \
            metaClass.methodOffset = methodOffsetOf(metaClass);

#define END_CLASS()                                                                 \
            return metaClass;                                                       \
        }

#define PROPERTY(type, name, getter, setter)                                        \
    addMetaMethod(metaClass, name, ReadProperty, newInvoker(&ClassType::getter));   \
    addMetaMethod(metaClass, name, WriteProperty, newInvoker(&ClassType::setter));

#define METHOD(type, name, method)                                                  \
    addMetaMethod(metaClass, name, Method, newInvoker(&ClassType::method));

#define BEGIN_ENUM(enumName)                                                        \
    {                                                                               \
        MetaEnum metaEnum;                                                          \
        metaEnum.name = #enumName;

#define END_ENUM()                                                                  \
        metaClass.enums.push_back(metaEnum);                                        \
    }

#define VALUE(name, value)                                                          \
    metaEnum.values.push_back(std::make_pair(#name, value));

#define REGISTER_CLASS(classtype)                                                   \
    classRegistry.insert(std::make_pair(#classtype, classtype::staticMetaClass()));

#endif /* METAOBJECT_H_ */
