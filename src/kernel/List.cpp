/*
 * List.cpp
 *
 *  Created on: 2013. 6. 29.
 *      Author: gubee
 */

#include "List.h"

List* List::newInstance(Type type) {
    switch (type) {
    case BoolType:
        return new BoolList();

    case IntType:
        return new IntList();

    case RealType:
        return new RealList();

    case StringType:
        return new StringList();

    case ListType:
        return new ListList();

    case MapType:
        return new MapList();

// TODO:
//    case ScriptType:
//        return new ScriptList();

    case ObjectType:
        return new ObjectList();

    default:
        break;
    }

    return 0;
}
