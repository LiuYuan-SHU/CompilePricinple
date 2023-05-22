#include "lexical_analyzer.h"
#include "regex_pattern.h"
#include "str_opekit.h"

#include <list>
#include <regex>
#include <string>
#include <utility>

using std::list;
using std::make_pair;
using std::regex;
using std::regex_search;
using std::smatch;
using std::sregex_iterator;
using std::string;

string lexical_analyzer::read_text(ifstream &fin) {
  string text, line;

  while (fin.good()) {
    std::getline(fin, line);
    text += line;
  }

  read_text_common(text);

  return this->_text;
}

string lexical_analyzer::read_text(const string &str) {
  string text = str;

  read_text_common(text);

  return this->_text;
}

void lexical_analyzer::read_text_common(string &text) {
  _parsed_pairs.clear();

  replace_all(text, "\n", "");
  str_tolower(text);
  this->_text = text;
}

list<lexical_pair> lexical_analyzer::parse_text() {
  this->_parsed_pairs.push_back({"", _text});

  parse_with_patterns();

  strip_lexeme();

  token_mark_reserved();
  token_mark_operators();
  token_mark_delimiters();
  token_mark_unsigned();
  token_mark_identifier();

  return this->_parsed_pairs;
}

void lexical_analyzer::parse_with_pattern(regex reg_pattern) {
  string text;
  /*******************************************
   *   asdasdasdasd HelloWorld asdaxzsdasdasd
   *                  |
   *                 /|\
   *                / | \
   *               /  |  \
   * new_string_pre   |   new_string_post
   *            matched_string
   ********************************************/
  string new_string_pre, new_string_post, matched_string;
  string token;

  for (auto iterator = this->_parsed_pairs.begin();
       iterator != this->_parsed_pairs.end(); ++iterator) {
    smatch match_result;

    while (true) {
      text = iterator->second;
      regex_search(text, match_result, reg_pattern);
      if (match_result.empty() || match_result[0].str() == text) {
        break;
      }

      matched_string = match_result[0].str();
      size_t pos = text.find(matched_string);
      new_string_pre = text.substr(0, pos);
      new_string_post = text.substr(pos + matched_string.size());

      iterator = this->_parsed_pairs.erase(iterator);
      if (!is_all_whitespace(new_string_pre)) {
        this->_parsed_pairs.insert(iterator,
                                   make_pair("", strip(new_string_pre)));
      }

      this->_parsed_pairs.insert(iterator, make_pair(token, matched_string));

      if (!is_all_whitespace(new_string_post)) {
        iterator = this->_parsed_pairs.insert(
            iterator, make_pair("", strip(new_string_post)));
      }
    }
  }
}

void lexical_analyzer::parse_with_patterns() {
  parse_with_pattern(reg_program);
  parse_with_pattern(reg_sub_program);
  parse_with_pattern(reg_const_declare);
  parse_with_pattern(reg_variable);
  parse_with_pattern(reg_procedure_declaration);
  parse_with_pattern(reg_sentence);
  parse_with_pattern(reg_const_define);
  parse_with_pattern(reg_assign);
  parse_with_pattern(reg_operator_assign);
  parse_with_pattern(reg_if);
  parse_with_pattern(reg_while);
  parse_with_pattern(reg_procedure_call);
  parse_with_pattern(reg_compound);
  parse_with_pattern(reg_read);
  parse_with_pattern(reg_write);
  parse_with_pattern(reg_paren);
  parse_with_pattern(reg_condition_expression);
  parse_with_pattern(reg_operator_relation);
  parse_with_pattern(reg_operator_plus);
  parse_with_pattern(reg_operator_times);
  parse_with_pattern(reg_semi);
  parse_with_pattern(reg_identifier);
}

void lexical_analyzer::strip_lexeme() {
  for (auto &p : this->_parsed_pairs) {
    p.second = strip(p.second);
  }
}

void lexical_analyzer::token_mark_reserved() {
  decltype(reserved.begin()) ite;
  for (auto &p : this->_parsed_pairs) {
    if (ite = reserved.find(p.second), ite != reserved.end()) {
      p.first = ite->second;
    }
  }
}

void lexical_analyzer::token_mark_operators() {
  decltype(operators.begin()) ite;
  for (auto &p : this->_parsed_pairs) {
    if (ite = operators.find(p.second), ite != operators.end()) {
      p.first = ite->second;
    }
  }
}

void lexical_analyzer::token_mark_delimiters() {
  decltype(delimiters.begin()) ite;
  for (auto &p : this->_parsed_pairs) {
    if (ite = delimiters.find(p.second), ite != delimiters.end()) {
      p.first = ite->second;
    }
  }
}

void lexical_analyzer::token_mark_unsigned() {
  smatch match_result;
  for (auto &p : this->_parsed_pairs) {
    if (std::regex_match(p.second, match_result, reg_unsigned)) {
      p.first = "number";
    }
  }
}

void lexical_analyzer::token_mark_identifier() {
  for (auto &p : this->_parsed_pairs) {
    if (p.first.empty()) {
      p.first = "ident";
    }
  }
}
