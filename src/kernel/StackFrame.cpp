/*
 * StackFrame.cpp
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#include <string>
#include "Point.h"
#include "Size.h"
#include "Rect.h"
#include "StackFrame.h"


#define STACK_SIZE                  1024
#define FRAME_POINTER_OFFSET        (sizeof(StackFrame) / sizeof(int))
#define POINTER_SIZE                (sizeof(void*) / sizeof(int))

namespace internals {
    static Address baseStackPointer = 0;
    static Address stackPointer = 0;
    static StackFrame* topStackFrame = 0;

    //----------------------------------------------------------------------------------------------
    // Utilities
    inline Argument* at(int index) {
        int frameOffset = topStackFrame->arguments[index];
        return cast(Argument, topStackFrame->framePointer + frameOffset);
    }

    inline Argument* push(int allocationSize) {
        int index = topStackFrame->argumentCount;
        int frameOffset = topStackFrame->arguments[index];
        Argument* argument = cast(Argument, topStackFrame->framePointer + frameOffset);

        topStackFrame->argumentCount += 1;
        topStackFrame->arguments[index + 1] = frameOffset + allocationSize + 1;
        stackPointer += (allocationSize + 1);

        return argument;
    }

    //----------------------------------------------------------------------------------------------
    void Stack_open() {
        baseStackPointer = new int[STACK_SIZE];
        stackPointer = baseStackPointer;
    }

    void Stack_close() {
        // TODO:
    }

    StackFrame* StackFrame_top() {
        return topStackFrame;
    }

    StackFrame* StackFrame_push() {
        StackFrame* stackFrame = cast(StackFrame, stackPointer);
        stackFrame->previousFrame = topStackFrame;
        stackFrame->framePointer = (stackPointer + FRAME_POINTER_OFFSET);
        stackFrame->argumentCount = 0;
        stackFrame->arguments[0] = 0;
        topStackFrame = stackFrame;
        stackPointer += FRAME_POINTER_OFFSET;
        return stackFrame;
    }

    void StackFrame_pop() {
        // TODO:
        //F_ASSERT(topStackFrame != 0);
        topStackFrame = topStackFrame->previousFrame;
        stackPointer = asAddress(topStackFrame);
    }

    Argument* StackFrame_at(int index) {
        return at(index);
    }

    void StackFrame_get(int index, bool& value) {
        Argument* argument = at(index);
        value = argument->boolean;
    }

    void StackFrame_get(int index, int& value) {
        Argument* argument = at(index);
        value = argument->integer;
    }

    void StackFrame_get(int index, float& value) {
        Argument* argument = at(index);
        value = argument->real;
    }

    void StackFrame_get(int index, const char*& value) {
        Argument* argument = at(index);
        value = argument->string.pointer;
    }

    void StackFrame_get(int index, std::string& value) {
        Argument* argument = at(index);
        value = argument->string.pointer;
    }

    void StackFrame_get(int index, Point& value) {
        Argument* argument = at(index);
        value = *cast(Point, argument->geometry);
    }

    void StackFrame_get(int index, Size& value) {
        Argument* argument = at(index);
        value = *cast(Size, argument->geometry);
    }

    void StackFrame_get(int index, Rect& value) {
        Argument* argument = at(index);
        value = *cast(Rect, argument->geometry);
    }

    void StackFrame_get(int index, Object*& value) {
        Argument* argument = at(index);
        value = argument->object;
    }

    // TODO:
    //void StackFrame_get(int index, Script*& value);

    void StackFrame_set() {
        Argument* argument = push(0);
        argument->type = UndefinedType;
    }

    void StackFrame_set(bool value) {
        Argument* argument = push(1);
        argument->type = BoolType;
        argument->boolean = value;
    }

    void StackFrame_set(int value) {
        Argument* argument = push(1);
        argument->type = IntType;
        argument->integer = value;
    }

    void StackFrame_set(float value) {
        Argument* argument = push(1);
        argument->type = RealType;
        argument->real = value;
    }

    void StackFrame_set(const char* value, std::size_t length, bool needsCopy) {
        int stringLength = static_cast<int>(length);
        int allocationSize = POINTER_SIZE;
        if (needsCopy) {
            if (stringLength == -1)
                stringLength = strlen(value);
            allocationSize += (stringLength + 5) >> 2;   // last '\0' character
        }
        Argument* argument = push(allocationSize);
        argument->type = StringType;
        if (needsCopy) {
            char* buffer = argument->string.pointer = argument->string.buffer;
            std::memcpy(buffer, value, stringLength);
            buffer[stringLength] = 0;
        } else {
            argument->constString = value;
        }
    }

    void StackFrame_set(const std::string& value, bool needsCopy) {
        int stringLength = static_cast<int>(value.size());
        int allocationSize = POINTER_SIZE;
        if (needsCopy) {
            allocationSize += (stringLength + 5) >> 2;   // last '\0' character
        }
        Argument* argument = push(allocationSize);
        argument->type = StringType;
        if (needsCopy) {
            char* buffer = argument->string.pointer = argument->string.buffer;
            std::memcpy(buffer, value.c_str(), stringLength);
            buffer[stringLength] = 0;
        } else {
            argument->constString = value.c_str();
        }
    }

    void StackFrame_set(const Point& value) {
        Argument* argument = push(2);
        argument->type = PointType;
        new (argument->geometry) Point(value);
    }

    void StackFrame_set(const Size& value) {
        Argument* argument = push(2);
        argument->type = SizeType;
        new (argument->geometry) Size(value);
    }

    void StackFrame_set(const Rect& value) {
        Argument* argument = push(4);
        argument->type = RectType;
        new (argument->geometry) Rect(value);
    }

    // TODO:
//    void StackFrame_set(const List* value);
//    void StackFrame_set(const Map* value);

    void StackFrame_set(const Object* value) {
        Argument* argument = push(POINTER_SIZE);
        argument->type = ObjectType;
        argument->constObject = value;
    }

    // TODO:
    //void StackFrame_set(const Script* value);
}
