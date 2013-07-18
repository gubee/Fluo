/*
 * Runtime.cpp
 *
 *  Created on: 2013. 7. 18.
 *      Author: gubee
 */

#include "Runtime.h"

ExecutionContext Runtime::Context::m_context;
char* Runtime::Arena::m_arena = 0;
int Runtime::Arena::m_size = 0;

Runtime::Arena::Arena(int size) {
    if (m_size <= size) {
        int newArenaSize = size * 2;
        char* arena = new char[newArenaSize];
        std::swap(m_arena, arena);
        delete[] arena;
        m_size = newArenaSize;
    }

    if (m_arena) {
        m_arena[size] = 0;
    }
}

Runtime::Runtime()
    : m_data(0) {
}

Runtime::~Runtime() {
}
