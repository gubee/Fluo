/*
 * Runtime.cpp
 *
 *  Created on: 2013. 6. 27.
 *      Author: gubee
 */

#include "Runtime.h"

#include "api/V8.h"
#include "api/SpiderMonkey.h"
#include "api/JavaScriptCore.h"

#if !defined(F_RUNTIME_EMSCRIPTEN) && !defined(F_RUNTIME_FLASCC)
namespace internals {
#define F_API(function)     {#function, ::function}
#define F_API_END           {0, 0}

    struct API {
        const char* name;
        APIPrototype function;
    };

    API apis[] = {
        // StackFrame APIs
        F_API(StackFrame_top),
        F_API(StackFrame_push),
        F_API(StackFrame_pop),
        // List APIs
        F_API(List_new),
        F_API(List_delete),
        F_API(List_append),
        F_API(List_remove),
        F_API(List_removeAt),
        F_API(List_count),
        F_API(List_indexOf),
        F_API(List_at),
        F_API(List_setAt),
        // Map APIs
        F_API(Map_new),
        F_API(Map_delete),
        F_API(Map_insert),
        F_API(Map_remove),
        F_API(Map_count),
        F_API(Map_names),
        F_API(Map_value),
        // Class APIs
        F_API(Class_new),
        F_API(Class_defineMethod),
        F_API(Class_name),
        F_API(Class_base),
        F_API(Class_methodCount),
        F_API(Class_method),
        F_API(Class_enumCount),
        F_API(Class_enum),
        // Method APIs
        F_API(Method_name),
        F_API(Method_type),
        F_API(Method_call),
        // Enum APIs
        F_API(Enum_name),
        F_API(Enum_values),
        // Object APIs
        F_API(Object_new),
        F_API(Object_delete),
        F_API(Object_class),

        F_API_END
    };
}
#endif  // !defined(F_RUNTIME_EMSCRIPTEN) && !defined(F_RUNTIME_FLASCC)

Runtime::Runtime()
    : m_data(0) {
}

Runtime::~Runtime() {
}
