/**
 * @file lexical_analyzer.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief lexical analyzer for PL/0
 * @date 2023-04-20
 */
#ifndef LIB_2CXX_LEXICAL_ANALYZER_H
#define LIB_2CXX_LEXICAL_ANALYZER_H

#include "lexemes.h"
#include "regex_pattern.h"

#include <fstream>
#include <list>
#include <regex>
#include <string>

using std::ifstream;
using std::list;

/**
 * @brief The parser for PL/0 language
 * @warning You must call `read_text` before you call `parse_text`!
 */
class lexical_analyzer {
public:
  /**
   * @brief Read program text from a file
   *
   * @param fin A `ifstream` object
   * @return string The processed text.
   */
  string read_text(ifstream &fin);

  /**
   * @brief Read program text from a string
   *
   * @param str A string.
   * @return string The processed text.
   */
  string read_text(const string &str);

  /**
   * @brief Parse the program text
   *
   * @return list<lexical_pair> Parsed lexical pairs.
   */
  list<lexical_pair> parse_text();

  /**
   * @brief Get the expression
   * @return The expression
   */
  inline string &get_expression() { return _text; }

  /**
   * @brief Get the parsed list
   * @return list<lexical_pair> Parsed lexical pairs.
   */
  inline list<lexical_pair> &get_list() { return _parsed_pairs; }

  /**
   * @brief Clear the parsed list, to run next parse.
   */
  inline void clear() { this->_parsed_pairs.clear(); };

private:
  /**
   * @brief The common operation for function `read_text`
   * @param text The string to be processed
   * @return none
   */
  inline void read_text_common(string &text);

  /**
   * @brief Parse every item in the list with the specific regex pattern.
   *
   * @param reg_pattern A `std::regex` object
   */
  void parse_with_pattern(regex reg_pattern);

  /**
   * @brief Parse the program text with a series of regex patterns.
   */
  void parse_with_patterns();

  /**
   * @brief Call `strip` on each lexical pair
   */
  inline void strip_lexeme();

  /**
   * @brief Mark reserved key words in the list.
   */
  void token_mark_reserved();

  /**
   * @brief Mark operator key words in the list.
   */
  void token_mark_operators();

  /**
   * @brief Mark delimiter key words in the list.
   */
  void token_mark_delimiters();

  /**
   * @brief Mark unsigned numbers in the list.
   */
  void token_mark_unsigned();

  /**
   * @brief Mark identifiers in the list.
   */
  void token_mark_identifier();

private:
  list<lexical_pair> _parsed_pairs;
  string _text;
};

#endif //! LIB_2CXX_LEXICAL_ANALYZER_H
