/*
 * StackFrame.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef STACKFRAME_H_
#define STACKFRAME_H_

#include "CoreType.h"

namespace internals {
    void Stack_open();
    void Stack_close();

    StackFrame* StackFrame_top();
    StackFrame* StackFrame_push();
    void StackFrame_pop();
    void StackFrame_set(Type type, Value value);
}

#endif /* STACKFRAME_H_ */
