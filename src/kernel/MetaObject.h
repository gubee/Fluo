/*
 * MetaObject.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef METAOBJECT_H_
#define METAOBJECT_H_

#include "CoreType.h"
#include "CallContext.h"
#include "Invoker.h"

//----------------------------------------------------------------------------------------------
// Utilities
int propertyOffsetOf(const MetaClass& metaClass);
int methodOffsetOf(const MetaClass& metaClass);

template <typename ClassType>
struct ObjectFactory {
    static Object* create() {
        return new ClassType();
    }
};

template <typename ClassType, typename ReturnType, typename ArgumentType>
void addMetaProperty(MetaClass& metaClass, const char* name, ReturnType (ClassType::*getter)() const, void (ClassType::*setter)(ArgumentType)) {
    typedef GenericInvoker<ClassType, ReturnType> Getter;
    typedef GenericInvoker<ClassType, void, ArgumentType> Setter;

    MetaProperty metaProperty;
    metaProperty.name = name;
    metaProperty.getter = new Getter(getter);
    metaProperty.setter = new Setter(setter);
    metaClass.properties.push_back(metaProperty);
}

//----------------------------------------------------------------------------------------------
#define BEGIN_CLASS(classtype, basetype)                                \
    public:                                                             \
        virtual MetaClass* metaClass() const {                          \
            return classtype::staticMetaClass();                        \
        }                                                               \
        static MetaClass* staticMetaClass() {                           \
            static MetaClass metaClass = classtype::createMetaClass();  \
            return &metaClass;                                          \
        }                                                               \
    private:                                                            \
        static MetaClass createMetaClass() {                            \
            typedef classtype       ClassType;                          \
            MetaClass metaClass;                                        \
            metaClass.name = #classtype;                                \
            metaClass.base = basetype::staticMetaClass();               \
            metaClass.create = &ObjectFactory<ClassType>::create;       \
            metaClass.propertyOffset = propertyOffsetOf(metaClass);     \
            metaClass.methodOffset = methodOffsetOf(metaClass);

#define END_CLASS()                                                     \
            return metaClass;                                           \
        }

#define PROPERTY(type, name, getter, setter)                            \
    addMetaProperty(metaClass, name, &ClassType::getter, &ClassType::setter);

#define PROPERTY_READONLY(type, name, getter)                           \
    addMetaProperty(metaClass, name, &ClassType::getter, 0);

#define BEGIN_ENUM(enumName)                                            \
    {                                                                   \
        MetaEnum metaEnum;                                              \
        metaEnum.name = #enumName;

#define END_ENUM()                                                      \
        metaClass.enums.push_back(metaEnum);                            \
    }

#define VALUE(name, value)                                              \
    metaEnum.values.push_back(std::make_pair(#name, value));

#define REGISTER_CLASS(classtype)                                       \
    classRegistry.insert(std::make_pair(#classtype, classtype::staticMetaClass()));

#endif /* METAOBJECT_H_ */
