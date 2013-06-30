/*
 * MetaObject.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef METAOBJECT_H_
#define METAOBJECT_H_

#include "CoreType.h"
#include "TypeTraits.h"
#include "Invoker.h"
#include "Signal.h"

//----------------------------------------------------------------------------------------------
// Utilities
namespace internals {
    void Method_define(MetaClass* metaClass, const char* name, Invoker* invoker);
    void Property_define(MetaClass* metaClass, const char* name, Invoker* getter, Invoker* setter, Type type);
    void Signal_define(MetaClass* metaClass, const char* name, SignalIndexer* indexer);

    template <typename ClassType>
    struct ObjectFactory {
        static Object* create(const MetaClass*) {
            return new ClassType();
        }
    };
}

//----------------------------------------------------------------------------------------------
#define BEGIN_CLASS(classtype, basetype)                                            \
    public:                                                                         \
        virtual const MetaClass* metaClass() const {                                \
            return classtype::staticMetaClass();                                    \
        }                                                                           \
        static const MetaClass* staticMetaClass() {                                 \
            static MetaClass metaClass = classtype::createMetaClass();              \
            return &metaClass;                                                      \
        }                                                                           \
    private:                                                                        \
        static MetaClass createMetaClass() {                                        \
            using namespace internals;                                              \
            typedef classtype ClassType;                                            \
            MetaClass metaClass;                                                    \
            metaClass.type = NativeClass;                                           \
            metaClass.name = #classtype;                                            \
            metaClass.base = basetype::staticMetaClass();                           \
            metaClass.create = &ObjectFactory<ClassType>::create;

#define END_CLASS()                                                                 \
            return metaClass;                                                       \
        }

#define METHOD(name, method)                                                        \
    Method_define(&metaClass, name, newInvoker(&ClassType::method));

#define PROPERTY(name, getter, setter, type)                                        \
    Property_define(&metaClass, name, newInvoker(&ClassType::getter), newInvoker(&ClassType::setter), to_type<type>::value);

#define SIGNAL(name, signal)                                                        \
    Signal_define(&metaClass, name, newSignalIndexer(&ClassType::signal));

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
