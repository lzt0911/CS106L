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

template <typename T>
size_t MyVector<T>::get_capacity() const {
    return m_capacity;
}

template <typename T>
size_t MyVector<T>::get_size() const {
    return m_size;
}

template <typename T>
T* MyVector<T>::get_arr() const {
    return arr;
}


template <typename T>
void MyVector<T>::set_capacity(size_t capacity) {
    m_capacity = capacity;
    T* temp = new T[capacity];
    for (size_t i = 0; i < m_size; ++i) {
        temp[i] = arr[i];
    }
    delete [] arr;
    arr = temp;
}

template <typename T>
void MyVector<T>::set_arr(T* arr) {
    // 在不能传入arr大小的情况下，无法set
    // 不懂为什么测试项必须要把每个private成员变量都set
}

template <typename T>
void MyVector<T>::set_size(size_t size) {
    m_size = size;
}