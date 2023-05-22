/**
 * @file str_opekit.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief Some string operating functions
 * @date 2023-04-20
 */
#ifndef LIB_CXX_STR_OPEKIT_H
#define LIB_CXX_STR_OPEKIT_H

#include <algorithm>
#include <list>
#include <string>
#include <vector>

using std::isspace;
using std::list;
using std::string;
using std::transform;
using std::vector;

/**
 * @brief Replace all `from` in the `str` to `to`
 *
 * @param str The operated string
 * @param from The substring to be replaced
 * @param to The substring to replace
 */
inline void replace_all(std::string &str, const std::string &from,
                        const std::string &to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

/**
 * @brief Convert all uppercase letters to lowercase letters in the string.
 *
 * @param str The string to be operated.
 */
inline void str_tolower(string &str) {
  transform(str.begin(), str.end(), str.begin(),
            [](char ch) -> char { return std::tolower(ch); });
}

/**
 * @brief Judge if all chars in the string are white space
 *
 * @param str The string to be judged
 * @return true All chars are white spaces
 * @return false Not all chars are white spaces
 */
inline bool is_all_whitespace(const string &str) {
  return std::all_of(str.begin(), str.end(), [](char c) {
    return isspace(static_cast<unsigned char>(c));
  });
}

/**
 * @brief Judge if a string represents an unsigned integer
 * @param str The string to be judged
 * @return true The string represents an unsigned integer
 * @return False The string does not represent an unsigned integer
 */
inline bool is_digit(const string &str) {
  for (auto c : str) {
    if (!std::isdigit(c)) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Remove white space at the beginning and end of the string
 *
 * @param str The string to be operated
 * @return string Operated string
 */
inline string strip(const std::string &str) {
  if (is_all_whitespace(str)) {
    return "";
  }
  auto first = std::find_if_not(str.begin(), str.end(),
                                [](int c) { return isspace(c); });
  auto last = std::find_if_not(str.rbegin(), str.rend(),
                               [](int c) { return isspace(c); });
  return {first, last.base()};
}

/**
 * @brief Split a string with the specified substring into a list
 * @param str The origin string
 * @param substr The split substring
 * @return The parsed result
 */
inline vector<string> split(const string &str, const string &substr) {
  vector<string> result;
  size_t pos = 0;
  size_t end_pos;

  while ((end_pos = str.find(substr, pos)) != string::npos) {
    if (pos != end_pos) {
      result.push_back(str.substr(pos, end_pos - pos));
    } else {
      result.push_back("");
    }
    pos = end_pos + substr.length();
  }

  result.push_back(str.substr(pos));
  return result;
}

#endif //! LIB_CXX_STR_OPEKIT_H
