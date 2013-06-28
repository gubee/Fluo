/*
 * Emscripten.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef RUNTIME_EMSCRIPTEN_H_
#define RUNTIME_EMSCRIPTEN_H_

#if defined(F_RUNTIME_EMSCRIPTEN)
#include "kernel/CoreType.h"

//----------------------------------------------------------------------------------------------
// StackFrame APIs
extern "C" {
    StackFrame* StackFrame_top();
    StackFrame* StackFrame_push();
    void StackFrame_pop();
}

//----------------------------------------------------------------------------------------------
// List APIs
extern "C" {
    List* List_new(Type type);
    void List_delete(List* list);
    void List_append(List* list, ValueReference value);
    void List_remove(List* list, ValueReference value, bool removeAll);
    void List_removeAt(List* list, int index);
    int List_count(List* list);
    int List_indexOf(List* list, ValueReference value);
    Value List_at(List* list, int index);
    void List_setAt(List* list, int index, ValueReference value);
}

//----------------------------------------------------------------------------------------------
// Map APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Class APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Method APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Enum APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Object APIs
// TODO:

//----------------------------------------------------------------------------------------------
// ClassRegistry APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Script APIs
// TODO:

#endif  // EMSCRIPTEN
#endif /* RUNTIME_EMSCRIPTEN_H_ */
