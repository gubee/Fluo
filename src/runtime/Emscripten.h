/*
 * Emscripten.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef EMSCRIPTEN_H_
#define EMSCRIPTEN_H_


#include "kernel/Fluorine.h"


//----------------------------------------------------------------------------------------------
// StackFrame APIs
extern "C" {
	StackFrame* StackFrame_new();
	void StackFrame_delete(StackFrame* stackFrame);
}


//----------------------------------------------------------------------------------------------
// List APIs
extern "C" {
	List* List_new(Type type);
	void List_delete(List* list);
	void List_append(List* list, Value value);
	void List_remove(List* list, Value value, bool removeAll);
	void List_removeAt(List* list, int index);
	int List_count(List* list);
	int List_indexOf(List* list, Value value);
	Value List_at(List* list, int index);
	void List_setAt(List* list, int index, Value value);
}


//----------------------------------------------------------------------------------------------
// Map APIs
// TODO:


//----------------------------------------------------------------------------------------------
// Class APIs
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


#endif /* EMSCRIPTEN_H_ */
