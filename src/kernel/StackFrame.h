/*
 * StackFrame.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef STACKFRAME_H_
#define STACKFRAME_H_

#include "CoreType.h"

//----------------------------------------------------------------------------------------------
// Forward Declarations
struct Point;
struct Size;
struct Rect;

//----------------------------------------------------------------------------------------------
namespace internals {
    void Stack_open();
    void Stack_close();

    StackFrame* StackFrame_top();
    StackFrame* StackFrame_push();
    void StackFrame_pop();

    Argument* StackFrame_argument(int index);

    void StackFrame_get(int index, bool& value);
    void StackFrame_get(int index, int& value);
    void StackFrame_get(int index, float& value);
    void StackFrame_get(int index, const char*& value);
    void StackFrame_get(int index, std::string& value);
    void StackFrame_get(int index, Point& value);
    void StackFrame_get(int index, Size& value);
    void StackFrame_get(int index, Rect& value);
    void StackFrame_get(int index, List*& value);
    void StackFrame_get(int index, Map*& value);
    void StackFrame_get(int index, Object*& value);
    // TODO:
    //void StackFrame_get(int index, Script*& value);

    void StackFrame_set();
    void StackFrame_set(bool value);
    void StackFrame_set(int value);
    void StackFrame_set(float value);
    void StackFrame_set(const char* value, std::size_t length = -1, bool needsCopy = true);
    void StackFrame_set(const std::string& value, bool needsCopy = true);
    void StackFrame_set(const Point& value);
    void StackFrame_set(const Size& value);
    void StackFrame_set(const Rect& value);
    void StackFrame_set(const List* value);
    void StackFrame_set(const Map* value);
    void StackFrame_set(const Object* value);
    // TODO:
    //void StackFrame_set(const Script* value);
}

#endif /* STACKFRAME_H_ */
