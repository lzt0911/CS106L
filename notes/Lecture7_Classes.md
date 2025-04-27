# Classes
## Struct and Class
* classes containing a sequence of objects of various types, a set of functions for manipulating these objects, and a set of restrictions on the access of these objects and functions.
* structures which are classes without access restrictions.
## Access restrictions
* classes have public and private sections.
* a user can access the public stuff. But is restricted from accessing the private stuff.
## Header File vs Source File
| | Header File(.h) | Source File(.cpp) |
|-| --------------- | ----------------- |
| Purpose | Defines the interface | Implements class functions |
| Contains | Function prototypes, class declarations, type definitions, macros, constants | Function implementations, executable code |
| Access | This is shares across source files | Is compiled into an object file |
## Class Design
* Constructor
    * The constructor initializes the state of newly created objects.
    * `this` is a pointer to the curent class instance.
    * no return type is specified, implicitly returns the new object.
    * 初始化列表：成员变量中含有const，或引用。（因const成员和引用成员变量必须在声明时完成初始化，而不能先声明再定义）
* Private member
* Public member
* Destructor
  * called when the object is deleted by the program.
* C++ 不允许成员变量和方法具有相同的名称，因为这会导致编译器无法区分它们
```cpp
// StanfordID.h
class StanfordID {
private:
    std::string name;
    std::string sunet;
    int idNumber;

public:
    // constructor for our student
    StanfordID(std::string name, std::string sunet, int idNumber);
    // method to get name, sunet, idNumber
    std::string getName();
    std::string getSunet();
    int getID();
    // method to set name, sunet, idNumber
    void setName(std::string name);
    void setSunet(std::string sunet);
    void setID(int idNumber);
    // destructor
    ~StanfordID();
};
```
```cpp
// .cpp file
#include "StanfordID.h"
#include <string>

// In our .cpp file we need to use our class as our namespace when defining our member functions

// parameterized constructor
StanfordID::StanfordID(std::string name, std::string sunet, int idNumber) {
    this->name = name;
    this->sunet = sunet;
    if (idNumber > 0)
        this->idNumber = idNumber;
}

// list initialization constructor
StanfordID::StanfordID(std::string name, std::string sunet, int idNumber) : name(name), sunet(sunet), idNumber(idNumber) {}

// default constructor
StanfordID::StanfordID() {
    name = “John Appleseed”;
    sunet = “jappleseed”;
    idNumber = 00000001;
}

std::string StanfordID::getName() {
    return this->name;
}
std::string StanfordID::getSunet() {
    return this->sunet;
}
int StanfordID::getID() {
    return this->idNumber;
}

void StanfordID::setName(std::string name) {
    this->name = name;
}
void StanfordID::setSunet(std::string sunet) {
    this->sunet = sunet;
}
void StanfordID::setID(int idNumber) {
    if (idNumber >= 0){
        this->idNumber = idNumber;
    }
}


StanfordID::~StanfordID() {
// free/deallocate any data here
}
```
## Inheritance
* Dynamic Polymorphism(动态多态): Different types of objects may need the same interface
* Extensibility: Inheritance allows you to extend a class by creating a subclass with specific properties
* pure vitual function denoted by `=0`, means that the inheriting class must define that function.
* If a class has at least one pure virtual function, then it's called an abstract class. (Interfaces are a subset of abstract classes)
* Abstract classes cannot be instantiated.
```cpp
class Shape {
public:
    // pure virtual function
    virtual double area() const = 0;
};

class Circle : public Shape {
public:
    // constructor
    Circle(double radius): _radius{radius} {};
    double area() const {
        return 3.14 * _radius * _radius;
    }
private:
    double _radius;
};

class Rectangle: public Shape {
public:
    // constructor
    Rectangle(double height, double width): _height{height}, _width{width}
    {};
    double area() const {
        return _width * _height;
    }
private:
    double _width, _height;
};
```
```cpp
class Base {
public:
    virtual void foo() = 0; // pure virtual function
    virtual void foo2(); // non-pure virtual function
    void bar() = {return 42;}; // regular function
};
```
* types of inheritance
  * private: can only be accessed by this class
  * protected: can only be accessed by this class or derived classed
  * public: can be accessed by anyone

| Type | public | protected | private |
| ---- | ------ | --------- | ------- |
| Example | `class B : public A {...}` | `class B : protected A {...}` | `class B : private A {...}` |
| Public Members | Are public in the derived class | Protected in the derived class | Privated in the derived class |
| Protected Members | Protected in the derived class | Protected in the derived class | Privated in the derived class |
| Private Members | Not accessible in derived class | Not accessible in derived class | Not accessible in derived class |
* Diamond Inheritance (菱形继承)
    * 指一个派生类通过多个路径继承同一个基类，形成类似菱形的类层次结构。
    ```
      A
     / \
    B   C
     \ /
      D
    ```
    * 内存浪费：基类`A`被`B`和`C`继承，而`D`同时继承`B`和`C`，导致`D`间接继承了两份`A`的成员。
    * 访问冲突：当直接访问`A`的成员时，编译器无法确定应使用`B::A`还是`C::A`的成员，导致编译错误
    * 解决方案：虚继承——虚继承确保`A`的成员在`D`中仅保留一份，消除冗余和二义性，虚基类的构造函数由最底层的派生类（如`D`）直接调用，而非中间类（`B`或`C`）
    ```cpp
    class B : virtual public A { /* ... */ };
    class C : virtual public A { /* ... */ };
    class D : public B, public C { /* ... */ };
    ```
* 析构函数应为虚函数
```cpp
class Base {
    ~Base() {}
};

class Derived : public Base {
    ~Derived() {}
}

Base *b = new Derived();
delete b; // never calls the destructor for Derived
```
* 模板是静态多态，继承是动态多态