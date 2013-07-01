/*
 * Engine.cpp
 *
 *  Created on: 2013. 6. 27.
 *      Author: gubee
 */

#include "Engine.h"
#include "runtime/Runtime.h"

Engine::Engine()
    : m_runtime(new Runtime()) {
}

Engine::~Engine() {
    delete m_runtime;
}

void Engine::startup() {
    m_runtime->startup();
}

void Engine::shutdown() {
    m_runtime->shutdown();
}

void Engine::runScript(const char* source) {
    m_runtime->runScript(source);
}
