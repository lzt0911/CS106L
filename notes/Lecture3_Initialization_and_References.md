# Initialization and References
* Initialization: provides initial values at the time of construction.
## Direct initialization (C++98)
```cpp
int main() {
    ​int foo = 12.0;‍
    return 0;
}

int main() {
    int foo(12.0);
    return 0;
}
```
缺点：narrowing conversion, where the compiler will implicitly cast the value assigned to a variable to the type of the variable.
## Uniform Initialization (C++11)
```cpp
struct IDCard {
    std::string name;
    int number;
    std::string email;
};

int main() {
    IDCard id ​{ "Miguel de Cervantes", 1605, "miguel@quijote.edu" }‍;
    return 0;
}
```
类型安全，若发生类型不匹配，编译器会报错。
## Structured Binding (C++17)
Structured binding is a method of initializing variables from data structures with size known at compile-time.
```cpp
std::tuple<std::string, std::string, std::string> getClassInfo() {
    std::string className = "CS106L";
    std::string location = "online";
    std::string language = "C++";
    return {className, location, language};
}

int main() {
    ​auto [className, location, language] = getClassInfo();‍
    std::cout << "Join us " << location << " for " << className << " to learn " << language << "!" << std::endl;

    auto classInfo = getClassInfo();
    std::string className = std::get<0>(classInfo);
    std::string location = std::get<1>(classInfo);
    std::string language = std::get<2>(classInfo);

    return 0;
}
```
## Reference
* A reference is an alias to something that already exists in memory.
* A reference refers to the same memory as its associated variable.
```cpp
int main() {
    int x = 10;
    int& reference = x;

    reference = 20; // assigning a new value through the reference
    std::cout << x << std::endl; // 20
    return 0;
}
```
```cpp

void shift(std::vector<std::pair<int, int>> &nums) {
    for (auto& [num1, num2] : nums) {
        num1++;
        num2++;
    }
}
```
* never return references to local variables
```cpp
char& firstCharBad(string& s) {
    string local = s;
    return local[0];
}
char& firstCharGood(string& s) {
    return s[0];
}

int main() {
    string tea = “Ito-En”;
    char& bad = firstCharBad(tea); // undefined, ref to local out of scope
    char& good = firstCharGood(tea); // good ref to tea[0]
}
```
## L-values vs R-values
|   | l-value | r-value |
|----------|----------|----------|
| Where with respect to equal sign? | left or right | right |
| Example | `int x = 10;` <br> `int y = x;` <br> `x is l-value` | `int x = 10;` <br> `int y = x;` <br> `10 is r-value` |
```cpp
#include <iostream>
#include <cmath>
#include <stdio.h>

int squareN(int& num) { // int& num is a l-value
    return std::pow(num, 2);
}

int main() {
    int lValue = 2;
    auto four = squareN(lValue);
    auto fourAgain = squareN(2); // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

    return 0;
}

```
* You can only reference a l-value.
## Const
* A qualifer for objects that declares they cannot be modified.
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec{ 1, 2, 3 }; // a normal vector
    const std::vector<int> const_vec{ 1, 2, 3 }; // a const vector
    std::vector<int>& ref_vec{ vec }; // a reference to 'vec'
    const std::vector<int>& const_ref{ vec }; // a const reference

    vec.push_back(3); // this is ok!
    const_vec.push_back(3); // no, this is const!
    ref_vec.push_back(3); // this is ok, just a reference!
    const_ref.push_back(3); // this is const, compiler error!
    return 0;
}
```
```cpp
#include <iostream>
#include <vector>

int main()
{
    const std::vector<int> const_vec{ 1, 2, 3 }; // a const vector
    std::vector<int>& bad_ref{ vec }; // error, you can't declare a non-const reference to a const variable

    return 0;
}
```