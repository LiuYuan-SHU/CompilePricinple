#include "analysis_table.h"
#include "str_opekit.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using std::back_inserter;
using std::copy;
using std::getline;
using std::pair;
using std::stoi;
using std::vector;

vector<string> analysis_table_row_reader::read_table() {
  string str, line;

  getline(_fin, line);
  getline(_fin, line);

  while (getline(_fin, line), _fin.good()) {
    str += line + ",";
  }

  return split(str, ",");
}

void analysis_table::parse_table(vector<string> table_content) {
  auto iter = table_content.begin();
  vector<string> vec_action;
  vector<string> vec_goto;

  while (true) {
    // jump the first item
    ++iter;
    if (iter == table_content.end()) {
      break;
    }
    // action
    copy(iter, iter + 9, back_inserter(vec_action));
    iter += 9;
    // goto
    copy(iter, iter + 5, back_inserter(vec_goto));
    iter += 5;

    analysis_table_row row;
    for (string item : vec_action) {
      if (item.find('S') != string::npos) {
        row.action_items.emplace_back(shift_in, stoi(item.substr(1)));
      } else if (item.find('r') != string::npos) {
        row.action_items.emplace_back(reduction, stoi(item.substr(1)));
      } else if (item == "ACC") {
        row.action_items.emplace_back(finished, -1);
      } else {
        row.action_items.emplace_back(null, -1);
      }
    }
    for (string item : vec_goto) {
      if (is_all_whitespace(item)) {
        row.goto_items.push_back(-1);
      } else {
        row.goto_items.push_back(stoi(item));
      }
    }
    _table.push_back(std::move(row));

    vec_action.clear();
    vec_goto.clear();
  }
}
