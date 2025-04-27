# Functions and Lambdas
## Functions and Lambdas
* A predicate is a boolean-valued function.
```cpp
// Pred: the type of our predicate, is a function pointer
// pred: our predicate passed as a parameter
template <typename It, typename Pred>
It find_if(It first, It last, Pred pred) {
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) return it;
    }
    return last;
}

bool isVowel(char c) {
    c = toupper(c);
    return c == 'A' || c == 'E' || c == 'I’ || c == 'O' || c == 'U’;
}

std::string corlys = "Lord of the Tides";
// Pred = bool (*)(char)
auto it = find_if(corlys.begin(), corlys.end(), isVowel);
```
* Lambda functions are functions that capture state from an enclosing scope.
```cpp
auto lambda = [capture-values](arguments) {
    return expression;
}

[x](arguments) // capture x by value (makes a copy)
[x&](arguments) // capture x by reference
[x, y](arguments) // capture x and y by value
[&](arguments) // capture everything by reference
[&, x](arguments) // capture everything except x by reference
[=](arguments) // capture everything by value
[](arguments) // capture nothing
```
* a functor is any object that defines an `operator()`
```cpp
template <typename T>
struct std::greater {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};
std::greater<int> g;
g(1, 2); // false
```
```cpp
struct my_functor {
    bool operator()(int a) const {
        return a * value;
    }
    int value;
};
my_functor f;
f.value = 5;
f(10); // 50
```
* when you use a lambda, a functor type is generated.
```cpp
int n = 10;
auto lessThanN = [n](int x) { return x < n; };
find_if(begin, end, lessThanN);

// is equivalent to the code below

// __lambda_6_18: Random name that only the compiler will see
class __lambda_6_18
{
public:
    bool operator()(int x) const { return x < n; }
    // constructor
    __lambda_6_18(int& _n) : n{_n} {}
private:
    int n;
};

int n = 10;
auto lessThanN = __lambda_6_18{ n }; // capturing value n from outer scope by passing to constructor
find_if(begin, end, lessThanN);
```
* `std::function` is an overarching(总体) type for functions/lambdas, but usually use `auto`
```cpp
std::function<bool(int, int)> less = std::less<int>{};
std::function<bool(char)> vowel = isVowel;
std::function<int(int)> twice = [](int x) { return x * 2; };
```
## Algorithms
* `std::count_if(InputIt first, InputIt last, UnaryPred p);`
    * How many elements in `[first, last]` match predicate `p`
* `std::sort(RandomIt first, RandomIt last, Compare comp);`
    * Sorts the elements in `[first, last)` according to comparison `comp`
* `std::max_element(ForwardIt first, ForwardIt last, Compare comp);`
    * Finds the maximum element in `[first, last]` according to comparison `comp`
* `std::copy_if(InputIt r1, InputIt r2, OutputIt o, UnaryPred p);`
    * Copy the only elements in `[r1, r2)` into `o` which meet predicate `p`
* `std::transform(ForwardIt1 r1, ForwardIt1 r2, ForwardIt2 o, UnaryOp op);`
    * Apply `op` to each element in `[r1, r2)`, writing a new sequence into `o`
  ```cpp
  transform(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _OutputIterator __result, _BinaryOperation __binary_op)
  {
      for (; __first1 != __last1; ++__first1, (void)++__first2, ++__result)
          *__result = __binary_op(*__first1, *__first2);
      return __result;
  }
  ```
* `std::unique_copy(InputIt i1, InputIt i2, OutputIt o, BinaryPred p);`
    * Remove consecutive duplicates(只保留一个连续重复元素) from `[r1, r2)`, writing new sequence into `o`
* `std::find_all`
* `std::inserter`
* `std::erase_if`
## Ranges and Views
* a range is anything with a begin and end.
* `std::ranges` provides new versions of `<algorithm>` for ranges
```cpp
int main() {
    std::vector<char> v = {'a', 'b', 'c', 'd', 'e’};
    auto it = std::ranges::find(v, 'c');

    // we can still work with iterators if we need to
    // Search from 'b' to 'd’
    auto first = v.begin() + 1;
    auto last = v.end() - 1;
    auto it = std::ranges::find(first, last, 'c');
}
```
* `views`: a way to compose algorithms, a view is a range that lazily adapts another range.
* We can chain views together use `operator|`
```cpp
// f is a view! It takes an underlying range letters
// and yields a new range with only vowels!
auto f = std::ranges::views::filter(letters, isVowel);
// t is a view! It takes an underlying range f
// and yields a new range with uppercase chars!
auto t = std::ranges::views::transform(f, toupper);
// Here we materialize the view into a vector!
auto vowelUpper = std::ranges::to<std::vector<char>>(t);


std::vector<char> letters = {'a','b','c','d','e'};
std::vector<char> upperVowel = letters
| std::ranges::views::filter(isVowel)
| std::ranges::views::transform(toupper)
| std::ranges::to<std::vector<char>>();

```
```cpp
namespace rng = std::ranges;
namespace rv = std::ranges::views;
auto ch = *rng::find_if(s, isalpha); // Get first letter
auto sx = s | rv::filter(isalpha) // Discard non-letters
| rv::transform(soundexEncode) // Encode letters
| rv::unique // Remove duplicates
| rv::filter(notZero) // Remove zeros
| rv::concat("0000") // Ensure length >= 4
| rv::drop(1) // Skip first digit
| rv::take(3) // Take next three
| rng::to<std::string>(); // Convert to string
return toupper(ch) + sx;
```
