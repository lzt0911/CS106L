# Operator Overloading
* There are two ways to overload:
  * Member overloading
    * Declares the overloaded operator within the scope of your class
  ```cpp
  bool StanfordID::operator<(const StanfirdID& other) const {
    return idNumber < other.getIdNumber();
  }
  ```
  * Non-member overloading
    * Declare the overloaded operator outside of class definitions
    * Define both the left and right hand objects as parameters
    *  The `friend` keyword allows non-member functions or classes to access private information in another class(类外函数，但可以访问类内的私有成员变量，需要在类内声明)
  ```cpp
  class StanfordID {
  private:
    std::string name;
    std::string sunet;    
    int idNumber;
  public:
    // constructor for our StudentID
    StanfordID(std::string name, std::string sunet, int idNumber);

    friend bool operator < (const StanfordID& lhs, const StanfordID& rhs);
  } 

  bool operator< (const StanfordID& lhs, const StanfordID& rhs) {
    return lhs.idNumber < rhs.idNumber;
  }
  ```
* member function or non-member function
  * some operators must be implemented as members (eg. [], (), ->, =) due to C++ semantics.
  * some must be implemented as non-members (eg. <<)
  * if unary(一元) operator (eg. ++), implement as member.
  * If binary operator and treats both operands equally, implement as non-member(maybe friend) (eg. +, <)
  * If binary operator and not both equally, implement as member (eg. +=)
