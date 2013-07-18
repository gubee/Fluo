/*
 * Runtime.h
 *
 *  Created on: 2013. 7. 18.
 *      Author: gubee
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include "CoreType.h"

//----------------------------------------------------------------------------------------------
// Runtime
class Runtime {
public:
    class Context {
    public:
        inline Context() {}
        inline Context(ExecutionContext context) { m_context = context; }

        inline ExecutionContext operator*() const { return m_context; }

    private:
        static ExecutionContext m_context;
    };

    class Arena {
    public:
        explicit Arena(int size);

        inline char* operator*() { return m_arena; }
        inline const char* operator*() const { return m_arena; }

    private:
        static char* m_arena;
        static int m_size;
    };

public:
    Runtime();
    ~Runtime();

    void startup();
    void shutdown();
    void runScript(const char* source);

private:
    struct Data;
    Data* m_data;
};

#endif /* RUNTIME_H_ */
