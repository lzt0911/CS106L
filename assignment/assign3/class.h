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
    size_t get_capacity() const;
    size_t get_size() const;
    T* get_arr() const; 
    void set_capacity(size_t capacity);
    void set_size(size_t size);
    void set_arr(T* arr);

private:
    void resize();
    size_t m_capacity;
    size_t m_size;
    T* arr;
};

#include "class.cpp"

# endif