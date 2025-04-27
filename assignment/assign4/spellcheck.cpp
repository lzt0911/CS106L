#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  /* TODO: Implement this method */
  std::vector<std::string::const_iterator> space = find_all(source.begin(), source.end(), isspace);
  
  Corpus result{};
  // 这个函数看一下cppref的实现例子更好理解
  /*
    transform(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _OutputIterator __result, _BinaryOperation __binary_op)
    {
      for (; __first1 != __last1; ++__first1, (void)++__first2, ++__result)
	        *__result = __binary_op(*__first1, *__first2);
      return __result;
    }
  // 注意 停止条件为 __first1 != __last1, 如果__last1 == iterators.end(), __first2会指向end, 导致内存错误
  */
  std::transform(space.begin(), space.end() - 1 , space.begin() + 1 , std::inserter(result, result.end()), [&source](auto it1, auto it2){
    return Token{source, it1, it2};
  });

  std::erase_if(result, [](const Token &token) {
    return token.content.empty();
  });

  return result;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  namespace rv = std::ranges::views;
  auto find_in_dic = [&dictionary](const Token &t) {
    return dictionary.count(t.content) == 0;
  };
  auto token_to_mispelling = [&dictionary](const Token &t) {
    auto view = dictionary | rv::filter([&t](const std::string &s) {
        return levenshtein(t.content, s) == 1;
    });
    std::set<std::string> sug(view.begin(), view.end());
    return Mispelling{t, sug};
  };
  auto find_valid_suggestion = [](const Mispelling& m) {
    return !m.suggestions.empty();
  };
  auto view = source | rv::filter(find_in_dic)
                     | rv::transform(token_to_mispelling)
                     | rv::filter(find_valid_suggestion);
  
  std::set<Mispelling> result(view.begin(), view.end());
  return result;
};

/* Helper methods */

#include "utils.cpp"