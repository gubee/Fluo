/*
 * StringArena.cpp
 *
 *  Created on: 2013. 7. 18.
 *      Author: gubee
 */

#include <algorithm>

namespace internals {
    static char* arena = 0;
    static int arenaSize = 0;

    char* StringArena_new(int size) {
        if (arenaSize <= size) {
            int newArenaSize = size * 2;
            char* buffer = new char[newArenaSize];
            std::swap(arena, buffer);
            delete[] buffer;
            arenaSize = newArenaSize;
        }

        if (arena) {
            arena[size] = 0;
        }
        return arena;
    }

    void StringArena_delete() {
        delete[] arena;
        arena = 0;
        arenaSize = 0;
    }
}
