/*
 * V8.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef RUNTIME_V8_H_
#define RUNTIME_V8_H_

#if defined(F_RUNTIME_V8)
#include <v8.h>
#include "kernel/CoreType.h"

//----------------------------------------------------------------------------------------------
// StackFrame APIs
//StackFrame* StackFrame_top();
//StackFrame* StackFrame_push();
//void StackFrame_pop();

//----------------------------------------------------------------------------------------------
// List APIs
//List* List_new(Type type);
//void List_delete(List* list);
//void List_append(List* list, Value value);
//void List_remove(List* list, Value value, bool removeAll);
//void List_removeAt(List* list, int index);
//int List_count(List* list);
//int List_indexOf(List* list, Value value);
//Value List_at(List* list, int index);
//void List_setAt(List* list, int index, Value value);

//----------------------------------------------------------------------------------------------
// Map APIs
// TODO:

//----------------------------------------------------------------------------------------------
// Class APIs
// TODO:
v8::Handle<v8::Value> Class_new(const v8::Arguments& arguments);

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

#endif  // F_RUNTIME_V8
#endif /* RUNTIME_V8_H_ */
