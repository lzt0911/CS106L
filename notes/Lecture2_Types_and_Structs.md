# Types and Structs
## Run code
```
$ g++ -std=c++20 main.cpp -o main
$ ./main
```
* compile allows us to generate more efficient machine code.
  * interpreters only see one small part of code at a time.
  * compilers see everything.
* compilation takes time.
## The Type System
* A type refers to the category of a variable.
* C++ is a statically typed language.
    * every variable must declare a type in the source code.
    * that type can't change after it's been declared.
* Python can change the type of the variable dynamically.
## Structs
```cpp
// 因index为非负，因此不使用int，而使用size_t
struct CharacterIndices {
  size_t first;
  size_t last;
};

CharacterIndices find(std::string str, char c) {
  size_t first, last = std::string::npos; // std::string::npos is a special value that refers to a non-existent position in a string
  /* Code to find the first and last indices */
  return { first, last };
}

​std::pair<size_t, size_t>‍ find(std::string str, char c) {
  size_t first, last = std::string::npos;
  /* Code to find the first and last indices */
  return { first, last };
}

std::string marquez = "Colonel Aureliano Buendía was to remember that distant afternoon";

std::pair<size_t, size_t> result = find(marquez, "a");
std::cout << result.first << std::endl;
std::cout << result.second << std::endl;
```
```cpp
std::pair<string, int> p{"Phone number", 6507232300};
std::make_pair("Phone number", 6507232300);
// make_pair automatically deduce the type;
```
* `std::pair` is a template.
```cpp
template<typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;
};

std::pair<std::string, int>

struct pair {
    std::string first;
    int second;
};
```
* `std` the C++ standard library
  * Built-in types, functions, and more provided by C++
  * You need to `#include` the relevant file
    * `#include <string>`—`std::string`
    * `#include <utility>`—`std::pair`
    * `#include <iostream>`—`std::cout` `std::endl`
  * We prefix standard library names with `std::`
    * If we write `using namespace std;` we don't have to, but this is considered bad style as it can introduce ambiguity
## Modern Typing
* 使用`using`给长类型起别名
```cpp
using Zeros = std::pair<double, double>;
using QuadraticSolution = std::pair<bool, Zeros>;

QuadraticSolution solveQuadratic(double a, double b, double c);

int main() {
  QuadraticSolution soln = solveQuadratic(1, 2, 3);
  return 0;
}
```
* 使用`auto`可让编译器自动推断变量的类型
```cpp
auto soln = solveQuadratic(1, 2, 3);

std::vector<int> vec { 1, 2, 3, 4 };
for (auto elem : vec) {
  std::cout << elem << " ";
}

// 推断返回值类型为int
auto smeagol() {
  return 20;
}

// 无法进行推断是std::pair<double, double>还是std::vector<double>
​auto‍ oops() {
  return { 106.0, 107.0 };
}


// 当auto作为函数参数时，类似于模板(C++20支持)
void borges(auto cuento) {
  std::cout << cuento << std::endl;
}

borges(std::string { "el sur" }); // auto deduced as `std::string`


void calculateSum(const vector<string>& v) {
    auto multiplier = 2.4; // double
    auto name = "Avery"; // const char []
    const auto& betterName2 = string{"Avery"}; // const string&
    auto copy = v; // vector<string>, const和&会被忽略
    auto& refMult = multiplier; // double&
    auto func = [](auto i) {return i * 2}; // 多态 lambda
    // 编译器会根据上下文推导出一个具体的函数对象类型
    // 如果调用时传入 int，它会生成一个返回 int 的函数对象
    // 如果传入 double，则生成返回 double 的函数对象
}
```