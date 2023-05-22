/**
 * @file intermediate_code_generator.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief DAG Optimizer
 * @date 2023-05-17
 */
#ifndef LIB_5CXX_INTERMEDIATE_CODE_GENERATOR_H
#define LIB_5CXX_INTERMEDIATE_CODE_GENERATOR_H

#include "semantic_analyzer.h"

#include <string>

using std::string;

/**
 * @brief Intermediate code generator
 */
class intermediate_code_generator {
 public:
  /**
   * @brief Quadruple
   */
  struct quadruple {
    enum type {
      number,   // The item is a number
      T,        // The item is a new-temp
      empty,    // The item is empty
      optimized // The item is generated by optimizing algorithm
    };
    typedef pair<type, int> item;

    static string item2str(item i);

    static quadruple::item str2item(const string &str);

    char op;       // Operator
    item operand1; // Operand 1
    item operand2; // Operand 2
    item count;    // Count
  };

 public:
  /**
   * @brief Generate quadruples
   * @param node The ASTNode tree node
   * @return The count of the quadruple
   */
  quadruple::item generate_quadruples(const shared_ptr<ASTNode> &node);

  /**
   * @brief Get quadruples
   * @return All quadruples
   */
  inline vector<quadruple> get_quadruples() { return this->_quadruples; }

  /**
   * @brief Clear quadruples
   */
  inline void clear() {
    this->_count = 1;
    this->_quadruples.clear();
  }

 private:
  int _count = 1;                // start from 1
  vector<quadruple> _quadruples; // All quadruples
};

#endif // LIB_5CXX_INTERMEDIATE_CODE_GENERATOR_H