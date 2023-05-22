#include "slr1.h"
#include "analysis_table.h"
#include "lexemes.h"

#include <exception>
#include <iterator>
#include <list>
#include <stdexcept>

using std::logic_error;

const vector<pair<string, size_t>> grammars = {{"start", 1},
                                               {"expression", 1},
                                               {"expression", 2},
                                               {"expression", 3},
                                               {"item", 1},
                                               {"item", 3},
                                               {"factor", 1},
                                               {"factor", 1},
                                               {"factor", 3},
                                               {"plus-operator", 1},
                                               {"plus-operator", 1},
                                               {"times-operator", 1},
                                               {"times-operator", 1}};

bool slr1::parse_lexeme(const pair<const string, const string> &lexeme) {
  int col_index = -1;

  if (lexeme.first == "ident") {
    col_index = action_index::ident;
  } else if (lexeme.first == "number") {
    col_index = action_index::unsigned_integer;
  } else if (lexeme.first == "lparen") {
    col_index = action_index::lparen;
  } else if (lexeme.first == "rparen") {
    col_index = action_index::rparen;
  } else if (lexeme.first == "plus") {
    col_index = action_index::plus;
  } else if (lexeme.first == "minus") {
    col_index = action_index::minus;
  } else if (lexeme.first == "times") {
    col_index = action_index::times;
  } else if (lexeme.first == "slash") {
    col_index = action_index::divide;
  } else if (lexeme.first == "acc") {
    col_index = action_index::acc;
  } else {
    string error_message =
        "Unexpected token: " + lexeme.first + " with text " + lexeme.second;
    throw logic_error(error_message);
  }

  action_item item = _table[_status_stack.top()].action_items[col_index];
  action_type type = item.first;
  next_row_number next_row = item.second;

  if (next_row < 0) {
    _grammar_status = invalid;
  }

  // shift in
  if (type == action_type::shift_in) {
    _status_stack.push(next_row);
    return true;
  }
  // reduction
  else if (type == action_type::reduction) {
    pair<string, size_t> grammar_item = grammars[next_row];
    string grammar = grammar_item.first;
    for (size_t count = 0; count < grammar_item.second; ++count) {
      _status_stack.pop();
    }

    if (grammar == "start") {
      _grammar_status = grammar_judgement::valid;
    } else if (grammar == "expression") {
      col_index = goto_index::expression;
    } else if (grammar == "item") {
      col_index = goto_index::item;
    } else if (grammar == "factor") {
      col_index = goto_index::factor;
    } else if (grammar == "plus-operator") {
      col_index = goto_index::operator_plus;
    } else if (grammar == "times-operator") {
      col_index = goto_index::operator_times;
    } else {
      _grammar_status = grammar_judgement::invalid;
    }

    _status_stack.push(_table[_status_stack.top()].goto_items[col_index]);

    return false;
  } else if (type == finished) {
    this->_grammar_status = valid;
    return true;
  }
  // error
  else {
    _grammar_status = invalid;

    return true;
  }
}

bool slr1::parse(list<lexical_pair> &list) {
  clear();

  auto &parsed_text = list;
  parsed_text.push_back({"acc", "#"});

  _status_stack.push(0);

  for (auto pair_iter = parsed_text.begin();
       pair_iter != parsed_text.end() && _grammar_status != invalid;) {
    bool move_next = parse_lexeme(*pair_iter);
    if (move_next) {
      ++pair_iter;
    }
  }

  return _grammar_status == valid;
}
