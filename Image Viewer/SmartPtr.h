#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <iostream>
#include <new>

template <class T>
class SmartPtr {
    T *obj;
public:
    SmartPtr(T *_obj = nullptr) : obj(_obj) {}
    ~SmartPtr() { if (obj != nullptr) delete obj; }
    T* operator->() { return obj; }
    T& operator*() { return *obj; }
    T* operator&() { return obj; }
    void operator=(T* _obj) { obj = _obj; }
    void* operator new(size_t size) { return ::operator new(size); }
};

#endif // SMARTPTR_H
