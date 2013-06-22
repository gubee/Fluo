/*
 * StackFrame.h
 *
 *  Created on: 2013. 6. 22.
 *      Author: gubee
 */

#ifndef STACKFRAME_H_
#define STACKFRAME_H_

namespace internals {
    StackFrame* StackFrame_new();
    StackFrame* StackFrame_current();
    void StackFrame_delete(StackFrame* stackFrame);
}

#endif /* STACKFRAME_H_ */
