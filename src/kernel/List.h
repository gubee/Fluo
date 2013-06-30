/*
 * List.h
 *
 *  Created on: 2013. 6. 28.
 *      Author: gubee
 */

#ifndef LIST_H_
#define LIST_H_

#include <vector>
#include <deque>
#include "CoreType.h"
#include "TypeTraits.h"

namespace internals {
    template <typename U>
    struct ListContainerType {
        typedef std::vector<U> result;
    };

    template <>
    struct ListContainerType<bool> {
        typedef std::deque<bool> result;
    };
}

//----------------------------------------------------------------------------------------------
// TypedList<>
template <typename T>
class TypedList : public List {
public:
    typedef typename internals::ListContainerType<T>::result Container;
    typedef TypeCast<T> TypeCast;

public:
    TypedList()
        : List(to_type<T>::value)
        , m_container(new Container())
        , m_needsToDeleteContainer(true) {
    }

    explicit TypedList(Container* container)
        : List(to_type<T>::value)
        , m_container(container)
        , m_needsToDeleteContainer(false) {
    }

    virtual ~TypedList() {
        if (m_needsToDeleteContainer)
            delete m_container;
    }

    virtual void append(ValueReference value) {
        m_container->push_back(TypeCast::fromValue(value));
    }

    virtual void remove(ValueReference value, bool removeAll = true) {
        T target = TypeCast::fromValue(value);
        if (removeAll) {
            m_container->erase(std::remove(m_container->begin(), m_container->end(), target), m_container->end());
        } else {
            typename Container::iterator i = std::find(m_container->begin(), m_container->end(), target);
            if (i != m_container->end())
                m_container->erase(i);
        }
    }

    virtual void removeAt(int index) {
        typename Container::iterator i = m_container->begin();
        std::advance(i, index);
        m_container->erase(i);
    }

    virtual int count() const {
        return m_container->size();
    }

    virtual int indexOf(ValueReference value) const {
        T target = TypeCast::fromValue(value);
        typename Container::iterator i = std::find(m_container->begin(), m_container->end(), target);
        return (i != m_container->end()) ? std::distance(m_container->begin(), i) : -1;
    }

    virtual Value at(int index) const {
        return TypeCast::toValue((*m_container)[index]);
    }

    virtual void setAt(int index, ValueReference value) {
        (*m_container)[index] = TypeCast::fromValue(value);
    }

private:
    Container* m_container;
    bool m_needsToDeleteContainer;
};

typedef TypedList<bool> BoolList;
typedef TypedList<int> IntList;
typedef TypedList<float> RealList;
typedef TypedList<std::string> StringList;
typedef TypedList<List*> ListList;
typedef TypedList<Map*> MapList;
// TODO:
//typedef TypedList<Script*> ScriptList;
typedef TypedList<Object*> ObjectList;

#endif /* LIST_H_ */
