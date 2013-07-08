/*
 * Iterator.h
 *
 *  Created on: 2013. 6. 29.
 *      Author: gubee
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "CoreType.h"

//----------------------------------------------------------------------------------------------
// TypedIterator<>
template <typename Container>
class TypedIterator : public Iterator {
public:
    typedef typename Container::const_iterator Iterator;
    typedef typename Container::value_type::second_type ValueType;
    typedef ::TypeCast<ValueType> TypeCast;

public:
    TypedIterator(const Container& container)
        : m_current(container.begin()), m_end(container.end()) {
    }

    TypedIterator(Iterator begin, Iterator end)
        : m_current(begin), m_end(end) {
    }

    virtual ~TypedIterator() {
    }

    virtual const char* name() const {
        return toString(m_current->first);
    }

    virtual Value value() const {
        return TypeCast::toValue(m_current->second);
    }

    virtual bool next() {
        return (++m_current != m_end);
    }

private:
    inline const char* toString(const std::string& value) const {
        return value.c_str();
    }

    inline const char* toString(const char* value) const {
        return value;
    }

private:
    Iterator m_current;
    Iterator m_end;
};

template <typename Container>
Iterator* newIterator(const Container& container) {
    return new TypedIterator<Container>(container);
}

#endif /* ITERATOR_H_ */
