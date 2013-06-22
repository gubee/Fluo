/*
 * StackFrame.cpp
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#include "StackFrame.h"

#define STACK_SIZE                  1024
#define FRAME_POINTER_OFFSET        (sizeof(StackFrame) / sizeof(int))

namespace internals {
    static Address baseStackPointer = 0;
    static Address stackPointer = 0;
    static StackFrame* currentStackFrame = 0;

    void Stack_open() {
        baseStackPointer = new int[STACK_SIZE];
        stackPointer = baseStackPointer;
    }

    void Stack_close() {
        // TODO:
    }

    StackFrame* StackFrame_top() {
        return currentStackFrame;
    }

    StackFrame* StackFrame_push() {
        StackFrame* stackFrame = reinterpret_cast<StackFrame*>(stackPointer);
        stackFrame->previousFrame = currentStackFrame;
        stackFrame->framePointer = (stackPointer + FRAME_POINTER_OFFSET);
        stackFrame->argumentCount = 0;
        stackFrame->arguments[0] = 0;
        currentStackFrame = stackFrame;
        return stackFrame;
    }

    void StackFrame_pop() {

    }

    void StackFrame_set(Type type, Value value) {
        int index = currentStackFrame->argumentCount;
        int frameOffset = currentStackFrame->arguments[index];
        Argument* argument = reinterpret_cast<Argument*>(currentStackFrame->framePointer + frameOffset);

        argument->type = type;
        switch (type) {
        case UndefinedType:
            frameOffset += 1;
            break;

        case BoolType:
            frameOffset += 2;
            argument->boolean = (bool) value;
            argument->boolean = static_cast<bool>(value);
            break;

        case IntType:
            frameOffset += 2;
            //argument->integer = (int) value;
            //argument->integer = static_cast<int>(value);
            break;

        case RealType:
            frameOffset += 2;
            //argument->real = (float) value;
            break;

        case StringType:
            //frameOffset += 2;
            break;

        case PointType:
            frameOffset += 3;
            break;

        case SizeType:
            frameOffset += 3;
            break;

        case RectType:
            frameOffset += 5;
            break;

        case ListType:
            frameOffset += 2;
            break;

        case MapType:
            frameOffset += 2;
            break;

        case ScriptType:
            frameOffset += 2;
            break;

        case ObjectType:
            frameOffset += 2;
            break;
        }
        currentStackFrame->arguments[index + 1] = frameOffset;
    }
}
