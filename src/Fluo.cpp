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
	cout << p << "\n" << p + 1 << endl;

	std::string s = "Hello";
	internals::Stack_open();
	internals::StackFrame_push();
	internals::StackFrame_set();
    internals::StackFrame_set();
	//internals::StackFrame_set(s.c_str(), s.size());
    internals::StackFrame_set(s.c_str(), -1, false);

	Object* o = new Object();
	const MetaClass* metaClass = o->metaClass();
	MetaProperty metaProperty = metaClass->properties[0];
	metaProperty.setter->invoke(o);

	cout << ": " << o->objectName() << endl;

	internals::StackFrame_pop();

	return 0;
}
