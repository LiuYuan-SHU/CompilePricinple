/**
 * @file DAG_optimizer.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief DAG Optimizer
 * @date 2023-05-19
 */
#ifndef LIB_6CXX_DAG_OPTIMIZER_H
#define LIB_6CXX_DAG_OPTIMIZER_H

#include "intermediate_code_generator.h"

#include <fstream>
#include <stack>
#include <unordered_map>
#include <vector>

using quadruple = intermediate_code_generator::quadruple;

using std::ifstream;
using std::stack;
using std::unordered_map;
using std::vector;

// Hash function for quadruple::item
namespace std {
template <> struct hash<quadruple::item> {
  inline size_t operator()(const quadruple::item &p) const {
    return hash<int>()(static_cast<int>(p.first)) ^ hash<int>()(p.second);
  }
};
} // namespace std

/**
 * @brief DAG Node
 */
class DAG_optimizer {
public:
  typedef quadruple DAGNode;

public:
  /**
   * @brief Read origin nodes from file
   * @param fin ifstream object
   */
  void read_origin_nodes(ifstream &fin);

  /**
   * @brief Read origin nodes from vector
   * @param nodes nodes
   */
  inline void read_origin_nodes(const vector<quadruple> &nodes) {
    clear();
    _origin_nodes = nodes;
  }

  /**
   * @brief Optimize quadruples with DAG
   */
  void optimize_quadruples();

  /**
   * @brief Get optimized quadruples
   * @return optimized quadruples
   */
  inline vector<quadruple> get_optimized() { return _optimized_nodes; }

  /**
   * @brief Clear all data, ready for next optimization
   */
  inline void clear() {
    _optimized_count = 1;
    _table.clear();
    _origin_nodes.clear();
    _optimized_nodes.clear();
    while (!_operand_stack.empty()) {
      _operand_stack.pop();
    }
  }

private:
  /**
   * @brief Get a item in table
   * @param item key
   * @return value
   */
  quadruple::item table_lookup(const quadruple::item &item);

  /**
   * @brief Insert a item into table
   * @param key key
   * @param value value
   */
  void table_insert(const quadruple::item &key, const quadruple::item &value);

  /**
   * @brief Make a new tmp variable
   * @return new tmp variable
   */
  quadruple::item make_new_tmp();

private:
  /**
   * @brief Optimized quadruple count
   */
  unsigned int _optimized_count = 1;
  /**
   * @brief DAG table, used to store the mapping relationship of DAG nodes
   */
  unordered_map<quadruple::item, quadruple::item> _table;
  /**
   * @brief Origin nodes
   */
  vector<DAGNode> _origin_nodes;
  /**
   * @brief Optimized nodes
   */
  vector<quadruple> _optimized_nodes;
  /**
   * @brief Operand stack, used to store intermediate results
   */
  stack<quadruple::item> _operand_stack;
};

#endif // LIB_6CXX_DAG_OPTIMIZER_H
