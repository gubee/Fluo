//============================================================================
// Name        : Fluo.cpp
// Author      : Fluo Team
// Version     :
// Copyright   : Fluo, All Rights Reserved
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <stdint.h>
#include <v8.h> // TODO: del
#include "kernel/CoreType.h"    // TODO: del
#include "kernel/StackFrame.h"    // TODO: del
#include "kernel/List.h"    // TODO: del
#include "kernel/Map.h"    // TODO: del
#include "items/Object.h"   // TODO: del
#include "Engine.h"

using namespace std;

struct AA {
    static const int M = 0;
};

int main() {
    Object* o = new Object();
	std::string s = "Hello";

	internals::Stack_open();
	internals::StackFrame_push();
    internals::StackFrame_set(o);
	internals::StackFrame_set(s.c_str(), s.size());
    //internals::StackFrame_set(s.c_str(), (std::size_t)-1, false);

	const MetaClass* metaClass = o->metaClass();
	MetaMethod* metaMethod = metaClass->methods[1];
	metaMethod->function->invoke();

	cout << ": " << o->objectName() << endl;

	internals::StackFrame_pop();

    Engine engine;
    engine.startup();

    const char* ss = "var m = Class_new('ABC', 0); Class_name(m);";

    v8::HandleScope handleScope(v8::Isolate::GetCurrent());
	v8::Handle<v8::Script> script = v8::Script::Compile(v8::String::New(ss));
	script->Run();

	List* lb = new BoolList();
    List* li = new IntList();
//    List* lr = new RealList();
//    List* ls = new StringList();
//    List* ll = new ListList();
//    List* lm = new MapList();
//    List* lo = new ObjectList();
//
//    Map* mb = new BoolMap();
//    Map* mi = new IntMap();
//    Map* mr = new RealMap();
//    Map* ms = new StringMap();
//    Map* ml = new ListMap();
//    Map* mm = new MapMap();
//    Map* mo = new ObjectMap();


	return 0;
}
