/*
 * Map.cpp
 *
 *  Created on: 2013. 6. 29.
 *      Author: gubee
 */

#include "Map.h"

Map* Map::newInstance(Type type) {
    switch (type) {
    case BoolType:
        return new BoolMap();

    case IntType:
        return new IntMap();

    case RealType:
        return new RealMap();

    case StringType:
        return new StringMap();

    case ListType:
        return new ListMap();

    case MapType:
        return new MapMap();

// TODO:
//    case ScriptType:
//        return new ScriptMap();

    case ObjectType:
        return new ObjectMap();

    default:
        break;
    }

    return 0;
}
