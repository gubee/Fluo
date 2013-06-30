/*
 * Map.h
 *
 *  Created on: 2013. 6. 28.
 *      Author: gubee
 */

#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <map>
#include "CoreType.h"
#include "TypeTraits.h"
#include "Iterator.h"

//----------------------------------------------------------------------------------------------
// TypedMap<>
template <typename T>
class TypedMap : public Map {
public:
    typedef std::map<std::string, T> Container;
    typedef TypeCast<T> TypeCast;

public:
    TypedMap()
        : Map(to_type<T>::value)
        , m_container(new Container())
        , m_needsToDeleteContainer(true) {
    }

    explicit TypedMap(Container* container)
        : Map(to_type<T>::value)
        , m_container(container)
        , m_needsToDeleteContainer(false) {
    }

    virtual ~TypedMap() {
        if (m_needsToDeleteContainer)
            delete m_container;
    }

    virtual void insert(const std::string& name, ValueReference value) {
        m_container->insert(std::make_pair(name, TypeCast::fromValue(value)));
    }

    virtual void remove(const std::string& name) {
        m_container->erase(name);
    }

    virtual int count() const {
        return m_container->size();
    }

    virtual Iterator* names() const {
        return newIterator(*m_container);
    }

    virtual Value value(const std::string& name) const {
        typename Container::const_iterator i = m_container->find(name);
        if (i != m_container->end())
            return TypeCast::toValue(i->second);
        else
            return undefined();
    }

private:
    Container* m_container;
    bool m_needsToDeleteContainer;
};

typedef TypedMap<bool> BoolMap;
typedef TypedMap<int> IntMap;
typedef TypedMap<float> RealMap;
typedef TypedMap<std::string> StringMap;
typedef TypedMap<List*> ListMap;
typedef TypedMap<Map*> MapMap;
// TODO:
//typedef TypedMap<Script*> ScriptMap;
typedef TypedMap<Object*> ObjectMap;

#endif /* MAP_H_ */
