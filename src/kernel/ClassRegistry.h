/*
 * ClassRegistry.h
 *
 *  Created on: 2013. 6. 29.
 *      Author: gubee
 */

#ifndef CLASSREGISTRY_H_
#define CLASSREGISTRY_H_

#include <string>
#include <map>

struct MetaClass;

class ClassRegistry {
public:
    typedef std::map<std::string, const MetaClass*> Container;
    typedef Container::const_iterator Iterator;

private:
    ClassRegistry();
    ~ClassRegistry();

public:
    void registerClass(const MetaClass* metaClass);
    const MetaClass* findClass(const char* name) const;
    const Container& registeredClasses() const;

public:
    static ClassRegistry& instance();

private:
    Container m_registry;
};

#endif /* CLASSREGISTRY_H_ */
