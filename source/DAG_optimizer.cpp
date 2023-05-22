#include "DAG_optimizer.h"
#include "str_opekit.h"

#include <algorithm>
#include <string>
#include <vector>

using std::stoi;
using std::string;
using std::transform;
using std::vector;

void DAG_optimizer::optimize_quadruples() {
  for (const quadruple &quad : this->_origin_nodes) {
    if (quad.op == '=') {
      // process assignment
      quadruple::item result = table_lookup(quad.operand1);
      if (result.first == quadruple::empty) {
        result = quad.operand1;
      }
      table_insert(quad.count, result);
    } else {
      // process other operations - Optimization
      quadruple::item arg1 = table_lookup(quad.operand1);
      if (arg1.first == quadruple::empty) {
        throw std::logic_error("Undefined variable: " +
                               quadruple::item2str(quad.operand1));
      }
      quadruple::item arg2 = table_lookup(quad.operand2);
      if (arg2.first == quadruple::empty) {
        throw std::logic_error("Undefined variable: " +
                               quadruple::item2str(quad.operand2));
      }
      quadruple::item result = make_new_tmp();
      // map the original quadruple to the optimized one
      table_insert(quad.count, result);
      // add optimized node to the quadruple map
      table_insert(result, quadruple::item(quadruple::empty, -1));
      // add optimized node to the optimized vector
      _optimized_nodes.push_back({quad.op, arg1, arg2, result});
    }
  }
}

quadruple::item DAG_optimizer::table_lookup(const quadruple::item &item) {
  // if found, return the value
  // if not, return { quadruple::empty, -1 }
  auto it = _table.find(item);
  if (it != _table.end()) {
    return it->second;
  }
  return {quadruple::empty, -1};
}

inline void DAG_optimizer::table_insert(const quadruple::item &key,
                                        const quadruple::item &value) {
  _table[key] = value;
}

quadruple::item DAG_optimizer::make_new_tmp() {
  return {quadruple::optimized, _optimized_count++};
}

void DAG_optimizer::read_origin_nodes(ifstream &fin) {
  clear();

  string line;
  vector<string> parsed_string;
  while (fin.good()) {
    // read a line and parsed into strings
    getline(fin, line);
    if (line.empty()) {
      break;
    }

    line = line.substr(1, line.length() - 2);
    parsed_string = split(line, ",");
    transform(parsed_string.begin(), parsed_string.end(), parsed_string.begin(),
              strip);

    // parse strings into quadruple
    quadruple quad;
    quad.op = parsed_string[0].length() == 1 ? parsed_string[0][0] : '=';
    quad.operand1 = quadruple::str2item(parsed_string[1]);
    quad.operand2 = quadruple::str2item(parsed_string[2]);
    quad.count = quadruple::str2item(parsed_string[3]);

    this->_origin_nodes.push_back(quad);

    parsed_string.clear();
  }
}
