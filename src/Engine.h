/*
 * Engine.h
 *
 *  Created on: 2013. 6. 27.
 *      Author: gubee
 */

#ifndef ENGINE_H_
#define ENGINE_H_

class Runtime;

class Engine {
public:
    Engine();
    virtual ~Engine();

    void startup();
    void shutdown();
    void runScript(const char* source);

private:
    Runtime* m_runtime;
};

#endif /* ENGINE_H_ */
