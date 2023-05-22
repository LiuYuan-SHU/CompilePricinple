/**
 * @file semantic_analyzer.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief Semantic Analyzer
 * @date 2023-05-10
 */
#ifndef LIB_4CXX_SEMANTIC_ANALYSIS_H
#define LIB_4CXX_SEMANTIC_ANALYSIS_H

#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using std::pair;
using std::shared_ptr;
using std::stack;
using std::string;
using std::vector;

/**
 * @brief The AST node class
 */
class ASTNode {
public:
  /**
   * @brief Construct a new ASTNode object
   * @param op Operator
   * @param val The value of the node
   * @param left The left child of node
   * @param right The right child of node
   */
  ASTNode(char op, int val, ASTNode *left = nullptr, ASTNode *right = nullptr)
      : _op(op), _val(val), _left(left), _right(right) {}

  /**
   * @brief Construct a new ASTNode object
   * @param op Operator
   * @param val The value of the node
   * @param left The left child of node
   * @param right The right child of node
   */
  ASTNode(char op, int val, const shared_ptr<ASTNode> &left,
          const shared_ptr<ASTNode> &right)
      : _op(op), _val(val), _left(left), _right(right) {}

  /**
   * @brief Get the operator
   * @return The operator
   */
  inline char get_op() const { return _op; }

  /**
   * @brief Get the value of the node
   * @return The value of the node
   */
  inline int get_val() const { return _val; }

  /**
   * @brief Get the left child node
   * @return The left child node
   */
  inline shared_ptr<ASTNode> get_left() const { return _left; }

  /**
   * @brief Get the right child node
   * @return The right child node
   */
  inline shared_ptr<ASTNode> get_right() const { return _right; }

private:
  char _op;                   // operator
  int _val;                   // operand
  shared_ptr<ASTNode> _left;  // left child node
  shared_ptr<ASTNode> _right; // right child node
};

class semantic_analyzer {
public:
  /**
   * @brief Construct a new semantic analyzer object
   */
  semantic_analyzer() : _root(nullptr) {}

  /**
   * @brief Construct a new semantic analyzer object
   * @param tokens The tokens
   */
  semantic_analyzer(const semantic_analyzer &) = delete;

  /**
   * @brief Construct a new semantic analyzer object
   */
  ~semantic_analyzer() = default;

  /**
   * @brief Construct the AST
   * @param tokens The parsed tokens
   */
  void construct_tree(vector<string> &tokens);

  /**
   * @brief Evaluate the AST
   * @return The result of the expression
   */
  inline int evaluate() { return evaluate_node(this->_root); }

  /**
   * @brief Get the root node
   * @return The root of the AST
   */
  inline shared_ptr<ASTNode> get_root() const { return this->_root; }

  /**
   * @brief Clear the AST
   */
  inline void clear() { this->_root.reset(); }

private:
  /**
   * @brief Evaluate the node
   * @param node
   * @return The result of the expression
   */
  int evaluate_node(shared_ptr<ASTNode> node);

private:
  /**
   * @brief The root of the AST
   */
  shared_ptr<ASTNode> _root;
};

#endif // LIB_4CXX_SEMANTIC_ANALYSIS_H
