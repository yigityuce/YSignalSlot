# YSignalSlot


YSignalSlot is a header only C++ library. It is an implementation of signal-slot mechanism via
C++. It is similar to C++ signal, Boost::signal and SigSlot. It intensively uses C++11 features.

-------------------------------------------------------------------------------------------------------

Advantages:
- Almost everything is compile-time. So it is fast.
- It can be used with single slot function or unlimited slot functions.
- “emit” function’s return type is pointer of your actual slot function’s return type and it
can be any type.
- It supports “void” return type.
- Slot(s) can be set to enable or disable. If slot(s) is/are disabled, signal can’t emit
this/these slot(s).
- If slot which emitted is disabled or its return type is void, “emit” function returns “NULL”
pointer.
- It works with member slot functions.
- Slot functions’ signatures are converted and stored as string.
- Slot functions’ argument counts and receivers are stored.
- It uses meta programming methods for “static for loop” and “static if”.
- Signals can be used nested.
- Receivers can be “this” pointer.
- It is free and LGPL licensed.
- It uses C++11 features.














Disadvantages:
- It works only member functions.
- Executable size may be large. Because codes generated at compile-time, not run-time.
- It doesn’t works with “const” member functions. ( like “int function1(int) const;” )
- Users must add “-std=c++0x” flag to compiler. This is required for using C++11.
- It generates a struct inside the class where you define signal. So it uses a little more code
size.





