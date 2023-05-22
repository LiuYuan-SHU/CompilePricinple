#include "intermediate_code_generator.h"
#include "semantic_analyzer.h"
#include "str_opekit.h"

#include <string>
#include <utility>
#include <vector>

using std::make_pair;
using std::to_string;
using item = intermediate_code_generator::quadruple::item;

item intermediate_code_generator::generate_quadruples(
    const shared_ptr<ASTNode> &node) {
  {
    // Leaf node (operand)
    if (node->get_left() == nullptr && node->get_right() == nullptr) {
      quadruple quad;
      quad.op = '=';
      quad.operand1 = make_pair(quadruple::number, node->get_val());
      quad.operand2 = make_pair(quadruple::empty, 0);
      quad.count = make_pair(quadruple::T, _count++);

      _quadruples.push_back(quad);

      return quad.count;
    }

    item left_child = generate_quadruples(node->get_left());
    item right_child = generate_quadruples(node->get_right());
    int count = _count++;

    quadruple quad;
    quad.op = node->get_op();
    quad.count = make_pair(quadruple::T, count);
    quad.operand1 = left_child;
    quad.operand2 = right_child;

    _quadruples.push_back(quad);

    return quad.count;
  }
}

string intermediate_code_generator::quadruple::item2str(item i) {
  switch (i.first) {
  case quadruple::number:
    return to_string(i.second);
  case quadruple::T:
  case quadruple::optimized:
    return "T" + to_string(i.second);
  case quadruple::empty:
  default:
    return "";
  }
}

intermediate_code_generator::quadruple::item
intermediate_code_generator::quadruple::str2item(const string &str) {
  // quadruple::empty
  if (is_all_whitespace(str)) {
    return {quadruple::type::empty, 0};
  }
  // quadruple::T
  else if (str[0] == 'T') {
    return {quadruple::type::T, stoi(str.substr(1))};
  }
  // quadruple::optimized
  else if (str[0] == 'O') {
    return {quadruple::type::optimized, stoi(str.substr(1))};
  }
  // quadruple::number
  else {
    return {quadruple::type::number, stoi(str)};
  }
}
