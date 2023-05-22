/**
 * @file analysis_table.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief Read and parse csv file for analysis _table
 * @date 2023-04-20
 */
#ifndef LIB_3CXX_ANALYSIS_TABLE_H
#define LIB_3CXX_ANALYSIS_TABLE_H

#include <fstream>
#include <initializer_list>
#include <list>
#include <string>
#include <utility>
#include <vector>

using std::ifstream;
using std::pair;
using std::string;
using std::vector;

/**
 * @brief The index for action item in the _table
 */
enum action_index {
  ident,            // identifier
  unsigned_integer, // unsigned integer
  lparen,           // _left paren
  rparen,           // _right paren
  plus,             // operator +
  minus,            // operator -
  times,            // operator *
  divide,           // operator /
  acc,              // accepted
  action_index_size // the size of this enum
};

/**
 * @brief The index for goto item in the _table
 */
enum goto_index {
  expression,     // expression
  item,           // item
  factor,         // factor
  operator_plus,  // [+|-]
  operator_times, // [*|/]
  goto_index_size // the size of this enum
};

/**
 * @brief T The type of action
 */
enum action_type {
  reduction,        // action reduction
  shift_in,         // action shift-in
  finished,         // action ACC
  null,             // empty _table item
  action_type_size  // the size of this enum
};

enum symble_type {
  ACTION,
  GOTO
};

// The number of the next row
typedef int next_row_number;
typedef pair<action_type, next_row_number> action_item;

/**
 * @brief A row is consisted of two part: action and goto
 */
struct analysis_table_row {
  vector<action_item> action_items;
  vector<next_row_number> goto_items;
};

/**
 * @brief The _table reader, which reads the data in the csv and process it into
 * a vector
 */
class analysis_table_row_reader {
 private:
  /**
   * @brief The name of the csv file
   *
   */
  const char *_file_name = "../data/analysis_table.csv";

  /**
   * @brief The `ifstream` data reader
   */
  ifstream _fin;

 public:
  inline analysis_table_row_reader() : _fin(_file_name) {
    if (!_fin.is_open()) {
      throw std::ios::failure("File for analysis _table reader is not opened.");
    }
  }

  /**
   * @brief Read the data of _table from `_fin`
   *
   * @return vector<string> The data read
   */
  vector<string> read_table();
};

/**
 * @brief The analysis _table
 */
class analysis_table {
 public:
  inline analysis_table() { parse_table(_reader.read_table()); }

  analysis_table(const analysis_table &other) = delete;

  ~analysis_table() = default;

  /**
   * @brief Get the _table object
   *
   * @return const vector<analysis_table_row> The parsed _table, ready to use
   */
  vector<analysis_table_row> get_table() const { return _table; }

  /**
   * @brief operator[] overloard
   * @return const analysis_table_row& The corresponding line
   */
  const analysis_table_row &operator[](size_t index) { return _table[index]; }

 private:
  /**
   * @brief Parse the item vector from _table reader
   *
   * @param table_content The vector provided by _table reader
   */
  void parse_table(vector<string> table_content);

 private:
  /**
   * @brief The analysis _table
   *
   */
  vector<analysis_table_row> _table;

  /**
   * @brief The _table reader
   *
   */
  analysis_table_row_reader _reader;
};

#endif // LIB_3CXX_ANALYSIS_TABLE_H
