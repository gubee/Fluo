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
#include "kernel/Signal.h"  // TODO: del
#include "kernel/Point.h"  // TODO: del
#include "items/Object.h"   // TODO: del
#include "Engine.h"

using namespace std;

struct AA {
    static const int M = 0;
};

class Test : public Object {
    BEGIN_CLASS(Test, Object)
        PROPERTY("readOnly", readOnly, none, bool);
        METHOD("test", test)
        SIGNAL("testSignal", testSignal)
    END_CLASS()

public:
    Signal testSignal;

    void test() {
        cout << this << ": test called(" << Signal::sender() << ")" << endl;
    }

    void testEmit() {
        emit(testSignal, Point());
    }

    bool readOnly() const {
        return true;
    }
};

//SignalPrototype
//Signals


//struct A {};
//template <typename T>
//struct A {};

//to_type<>
//from_argument<>
//to_argument<>


int main() {
    Object* o = new Object();
	std::string s = "Hello";

	internals::Stack_open();

    Test* t1 = new Test();
    Test* t2 = new Test();
    Test* t3 = new Test();
    CONNECT(t1, testSignal, t2, test);
    CONNECT(t1, testSignal, t3, test);

    cout << t1->property("readOnly")->getter << endl;
    cout << t1->property("readOnly")->setter << endl;

    t1->testEmit();

//	internals::StackFrame_push();
//    internals::StackFrame_set(o);
//	internals::StackFrame_set(s.c_str(), s.size());
//    //internals::StackFrame_set(s.c_str(), (std::size_t)-1, false);
//
//	const MetaClass* metaClass = o->metaClass();
//	MetaMethod* metaMethod = metaClass->methods[1];
//	metaMethod->function->invoke();
//
//	cout << ": " << o->objectName() << endl;
//
//	internals::StackFrame_pop();

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
