//============================================================================
// Name        : Fluo.cpp
// Author      : Fluo Team
// Version     :
// Copyright   : Fluo, All Rights Reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "kernel/CoreType.h"    // TODO: del
#include "runtime/Emscripten.h"    // TODO: del
#include "kernel/StackFrame.h"    // TODO: del
#include "items/Object.h"   // TODO: del

using namespace std;

int main() {
    Object* o = new Object();
	std::string s = "Hello";

	internals::Stack_open();
	internals::StackFrame_push();
    internals::StackFrame_set(o);
	internals::StackFrame_set(s.c_str(), s.size());
    //internals::StackFrame_set(s.c_str(), (std::size_t)-1, false);

	const MetaClass* metaClass = o->metaClass();
	MetaMethod metaMethod = metaClass->methods[1];
	metaMethod.function->invoke();

	cout << ": " << o->objectName() << endl;

	internals::StackFrame_pop();

	return 0;
}
