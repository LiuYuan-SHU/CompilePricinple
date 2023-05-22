/**
 * @file slr1.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief Read and parse csv file for analysis _table
 * @date 2023-04-20
 */
#ifndef LIB_3CXX_SLR1_H
#define LIB_3CXX_SLR1_H

#include "analysis_table.h"
#include "lexical_analyzer.h"

#include <fstream>
#include <stack>
#include <string>
#include <utility>

using std::ifstream;
using std::pair;
using std::stack;
using std::string;

/**
 * @brief SLR(1) analyzer
 */
class slr1 {
 public:
  /**
   * @brief The expression's judgement result
   */
  enum grammar_judgement {
    invalid, // The expression is invalid
    valid,   // The expression is valid
    not_sure // The parser hasn't done yet
  };

  slr1() = default;

  slr1(const slr1 &) = delete;

  ~slr1() = default;

  /**
   * @brief Parse expression
   *
   * @return true The expression is valid
   * @return false The expression is invalid
   */
  bool parse(list<lexical_pair> &);

  /**
   * @brief Reset the parser's status
   */
  inline void clear() {
    while (!_status_stack.empty()) {
      _status_stack.pop();
    }

    _grammar_status = grammar_judgement::not_sure;
  }

 private:
  /**
   * @brief Parse expression's lexemes
   *
   * @param lexeme The parsed lexemes by `lexical_analyzer`
   * @return true The parser should analyze the next lexeme
   * @return false The parser should not analyze the next lexeme
   */
  bool parse_lexeme(const pair<const Token, const Lexeme> &lexeme);

 private:
  typedef unsigned int line_number;

  analysis_table _table;
  stack<line_number> _status_stack;
  grammar_judgement _grammar_status = grammar_judgement::not_sure;
};

#endif // LIB_3CXX_SLR1_H
