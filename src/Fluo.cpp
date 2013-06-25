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
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << sizeof(void*) << sizeof(int) << sizeof(char) << endl;

	int* p = new int[16];
	cout << p << "\n" << p + 12 << endl;

    Object* o = new Object();
    o->setObjectName("XXX");
	std::string s = "Hello";

	std::cout << ">> " << o << std::endl;

	internals::Stack_open();
	internals::StackFrame_push();
    internals::StackFrame_set(o);

    Object* oo = 0;
    internals::StackFrame_get(0, oo);
    std::cout << ">> " << oo << std::endl;

	internals::StackFrame_set(s.c_str(), s.size());
    //internals::StackFrame_set(s.c_str(), (std::size_t)-1, false);
    internals::StackFrame_get(0, oo);
    std::cout << ">> " << oo << std::endl;

	const MetaClass* metaClass = o->metaClass();
	MetaMethod metaMethod = metaClass->methods[1];
	metaMethod.function->invoke();

	cout << ": " << o->objectName() << endl;

	internals::StackFrame_pop();

	return 0;
}
