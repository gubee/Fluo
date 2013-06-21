/*
 * Fluorine.h
 *
 *  Created on: 2013. 6. 21.
 *      Author: gubee
 */

#ifndef FLUORINE_H_
#define FLUORINE_H_

//----------------------------------------------------------------------------------------------
// Type
enum Type {
    Bool,
    Int,
    Real,
    String,
    Point,
    Size,
    Rect,
    List,
    Map,
    ScriptObject,
    Object
};

typedef void* Value;
typedef int* Address;

//----------------------------------------------------------------------------------------------
// StackFrame
struct StackFrame {
    StackFrame* previousFrame;
    Address framePointer;
    int argumentCount;
    int arguments[6];		// framePointer offsets
};

//----------------------------------------------------------------------------------------------
// List
struct List {
    Type type;
};

//----------------------------------------------------------------------------------------------
// Map
struct Map {
    Type type;
};

#endif /* FLUORINE_H_ */
