# Template Classes and Const Correctness
## Template Classes
```cpp
template<typename T> // template declaration
// vector is a template that takes in the name of a type T
// T gets replaced when Vector is instantiated
class Vector {
public:
    T& at(size_t index);
    void push_back(const T& elem);
private:
    T* elems;
};

// template instantiation
// code for a specific type is generated on demand, when you use it
Vector<int> intVec;
Vector<double> doubleVec;
```
```cpp
template<typename T, std::size_t N>
struct std::array { /*...*/ };

std::array<std::string, 5> arr; // an array of exactly 5 strings
```
* must copy `template<...>` syntax in .cpp
* .h must include .cpp at bottom of file
* `typename` is the same as `class`
```cpp
// Vector.h
template<typename T>
class Vector {
public:
    T& at(size_t index);
    void push_back(const T& elem);
private:
    T* elems;
};

#include "Vector.cpp"
```
```cpp
// Vector.cpp
template<typename T>
// Vector is a template not a type, Vector<T> is a type
T& Vector<T>::at(size_t index) {
    // Implementation
}
```
## Const Correctness
```cpp
// Vector.h
template<typename T>
class Vector {
public:
    size_t size() const; // const promise not to modify this object inside of this method
};

#include "Vector.cpp"
```
```cpp
// Vector.cpp
template<typename T>
size_t Vector<T>::size() const {
    // Implementation
}
```
```cpp
template<class T>
class Vector {
public:
    const T& at(size_t index) const;
    T& at(size_t index);
};

template<class T>
const T& Vector<T>::at(size_t index) const {
    // return elems[index];
    return const_cast<Vector<T>&>(*this).at(idex);
}

T& Vector<T>::at(size_t index) {
    return elems[index];
}
```
* `mutable` circumvents(规避) const protections.
```cpp
struct MutableStruct {
    int dontTouchThis;
    mutable double iCanChange;
};

const MutableStruct cm;
cm.dontTouchThis = 42; // no
cm.iCanChange = 3.14; // ok
```
```cpp
// assign3实现一个自己的类
// class.h
#ifndef CLASS_H
#define CLASS_H

#include <string>

template <typename T>
class MyVector {
public:
    MyVector();
    MyVector(size_t capacity);
    MyVector(const MyVector &vec);
    MyVector& operator=(const MyVector &vec);
    ~MyVector();
    size_t size() const;
    void push_back(T val);
    void pop_back();
    T& at(size_t index);
    T& operator[](size_t index);
    const T& at(size_t index) const;
    const T& operator[](size_t index) const;
    void print() const;

private:
    void resize();
    size_t m_capacity;
    size_t m_size;
    T* arr;
};

#include "class.cpp"

# endif
```
```cpp
//class.cpp
#include <iostream>

template <typename T>
MyVector<T>::MyVector() {
    m_capacity = 10;
    m_size = 0;
    arr = new T[m_capacity];
}

template <typename T>
MyVector<T>::MyVector(size_t capacity) {
    m_size = 0;
    m_capacity = capacity;
    arr = new T[m_capacity];
}

template <typename T>
MyVector<T>::MyVector(const MyVector &vec) {
    m_size = vec.m_size;
    m_capacity = vec.m_capacity;
    arr = new T[m_capacity];
    for (size_t i = 0; i < m_size; i++) {
        arr[i] = vec.arr[i];
    }
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector &vec) {
    if (this == &vec) {
        return *this;
    }
    m_size = vec.m_size;
    m_capacity = vec.m_capacity;
    T* new_arr = new T[vec.m_capacity];
    for (size_t i = 0; i < vec.m_size; ++i) {
        new_arr[i] = vec.arr[i];
    }
    delete[] arr;
    arr = new_arr;
    return *this;
}

template <typename T>
MyVector<T>::~MyVector() {
    delete [] arr;
}

template <typename T>
size_t MyVector<T>::size() const {
    return m_size;
}


template <typename T>
void MyVector<T>::resize() {
    m_capacity *= 2;
    T* temp = new T[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
        temp[i] = arr[i];
    }
    delete [] arr;
    arr = temp;
}

template <typename T>
void MyVector<T>::push_back(T val) {
    if (m_size == m_capacity) {
        resize();
    }
    arr[m_size++] = val;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (m_size == 0) {
        return;
    } 
    m_size--;
}

template <typename T>
T& MyVector<T>::at(size_t index) {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    return arr[index];
}

template <typename T>
const T& MyVector<T>::at(size_t index) const{
    return const_cast<MyVector<T>&>(*this).at(index);
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    return const_cast<MyVector<T>&>(*this)[index];
}

template <typename T>
void MyVector<T>::print() const {
    for (int i = 0; i < m_size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

```
