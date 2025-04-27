# Optional and Type Safety
* Type Safety: The extent(程度) to which a language prevents typing errors.
## `std::optional`
* `std::optional` is a template class which will either contain a value of type `T` or contain nothing (expressed as `nullopt`)
    * `nullptr`: an object that can be converted to a value of any pointer type
    * `nullopt`: an object that can be converted to a value of any optional type
```cpp
void main(){
    std::optional<int> num1 = {}; //num1 does not have a value
    num1 = 1; //now it does!
    num1 = std::nullopt; //now it doesn't anymore
}
```
```cpp
std::optional<valueType> vector<valueType>::back(){
    if(empty()){
        return {};
    }
    return *(begin() + size() - 1);
}
```
* `std::optional` types have:
    * `.value()` method: returns the contained value or throws bad_optional_access error
    * `.value_or(valueType val)`: returns the contained value or default value, parameter val
    * `.has_value()`: returns true if contained value exists, false otherwise
    * `.and_then(function f)`: 这个方法可以对`std::optional`中的值应用一个函数，该函数返回另一个`std::optional`。如果原始`std::optional` 有值，就将这个值作为参数传递给函数，并返回该函数的结果（也是一个 `std::optional`）；如果原始`std::optional`没有值，就直接返回一个空的`std::optional`
    * `.transform(function f)`: 这个方法可以对`std::optional`中的值应用一个转换函数。如果`std::optional`有值，就将这个值作为参数传递给转换函数，并将返回值封装在一个新的`std::optional`中返回；如果`std::optional`没有值，就返回一个空的`std::optional`
    * `.or_else(function f)`: 这个方法可以为`std::optional`提供一个默认值生成函数。如果`std::optional`没有值，就调用这个函数来生成一个默认值并返回；如果`std::optional`有值，就直接返回原始值
```cpp
// 法一
void removeOddsFromEnd(vector<int>& vec){
    while(vec.back().value() % 2 == 1){
        vec.pop_back();
    }
}

// 法二
void removeOddsFromEnd(vector<int>& vec){
    while(vec.back().has_value() && vec.back().value() % 2 == 1){
        vec.pop_back();
    }
}

// 法三
void removeOddsFromEnd(vector<int>& vec){
    while(vec.back() && vec.back().value() % 2 == 1){
        vec.pop_back();
    }
}

// 法四
void removeOddsFromEnd(vector<int>& vec){
    auto isOdd = [](optional<int> num){
        if(num)
            return num % 2 == 1;
        else
            return std::nullopt;
    };
    while(vec.back().and_then(isOdd)){
        vec.pop_back();
    }
}
```
```cpp
#include <iostream>
#include <optional>
#include <string>

std::optional<int> multiplyByTwo(std::optional<int> num) {
    return num.transform([](int n) { return n * 2; });
}

int main() {
    std::optional<int> num1 = 5;
    std::optional<int> num2 = std::nullopt;

    auto result1 = multiplyByTwo(num1);
    auto result2 = multiplyByTwo(num2);

    if (result1) {
        std::cout << "Result1: " << *result1 << std::endl; // 输出：Result1: 10
    } else {
        std::cout << "Result1 is empty" << std::endl;
    }

    if (result2) {
        std::cout << "Result2: " << *result2 << std::endl;
    } else {
        std::cout << "Result2 is empty" << std::endl; // 输出：Result2 is empty
    }

    return 0;
}
```
```cpp
#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> processNumber(std::optional<int> num) {
    return num.and_then([](int n) {
        if (n > 0) {
            return std::make_optional<std::string>("Positive: " + std::to_string(n));
        } else if (n < 0) {
            return std::make_optional<std::string>("Negative: " + std::to_string(n));
        } else {
            return std::nullopt;
        }
    });
}

int main() {
    std::optional<int> num1 = 5;
    std::optional<int> num2 = -3;
    std::optional<int> num3 = 0;
    std::optional<int> num4 = std::nullopt;

    auto result1 = processNumber(num1);
    auto result2 = processNumber(num2);
    auto result3 = processNumber(num3);
    auto result4 = processNumber(num4);

    if (result1) {
        std::cout << "Result1: " << *result1 << std::endl; // 输出：Result1: Positive: 5
    }

    if (result2) {
        std::cout << "Result2: " << *result2 << std::endl; // 输出：Result2: Negative: -3
    }

    if (result3) {
        std::cout << "Result3: " << *result3 << std::endl;
    } else {
        std::cout << "Result3 is empty" << std::endl; // 输出：Result3 is empty
    }

    if (result4) {
        std::cout << "Result4: " << *result4 << std::endl;
    } else {
        std::cout << "Result4 is empty" << std::endl; // 输出：Result4 is empty
    }

    return 0;
}
```
```cpp
#include <iostream>
#include <optional>
#include <string>

std::optional<int> getNumber() {
    // 假设这里有一个可能返回空的逻辑
    return std::nullopt;
}

int main() {
    std::optional<int> num = getNumber();

    auto result = num.or_else([]() { return 42; });

    std::cout << "Result: " << *result << std::endl; // 输出：Result: 42

    return 0;
}
```
```cpp
std::string output;
output = course.transform([](const Course* c) {
    return "Found course: " + c->title + "," + c->number_of_units + "," + c->quarter;
}).or_else([](){
    return std::optional<std::string>{"Course not found."};
}).value();
```