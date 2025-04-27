/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include "class.h"

void const_test(const MyVector<int>& vec) {
  std::cout << "const test" << std::endl;
  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec.at(i) << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;
}

void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  MyVector<int> vec(5);
  for (int i = 0; i < 10; i++) {
    vec.push_back(i);
  }
  vec.print();

  MyVector<int> vec2(vec);
  vec2.print();

  MyVector<int> vec3;
  vec3 = vec;
  vec3.print();


  vec.push_back(10);
  vec2.pop_back();
  vec3.push_back(100);
  std::cout << "vec: size = " << vec.size() << "; ";
  vec.print();
  std::cout << "vec2: size = " << vec2.size() << "; ";
  vec2.print();
  std::cout << "vec3: size = " << vec3.size() << "; ";
  vec3.print();

  const_test(vec3);

  // vec3.at(-1);
  // vec.at(100);

}