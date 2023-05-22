#include "semantic_analyzer.h"
#include "str_opekit.h"

#include <memory>
#include <unordered_map>

using std::make_shared;
using std::unordered_map;

// calculate the result of expression
int semantic_analyzer::evaluate_node(shared_ptr<ASTNode> node) {
  if (node->get_left() == nullptr && node->get_right() == nullptr) {
    return node->get_val();
  }
  int left_val = evaluate_node(node->get_left());
  int right_val = evaluate_node(node->get_right());
  switch (node->get_op()) {
  case '+':
    return left_val + right_val;
  case '-':
    return left_val - right_val;
  case '*':
    return left_val * right_val;
  case '/':
    return left_val / right_val;
  default:
    throw std::logic_error(string("unexpected operator") + node->get_op());
  }
}

// generate semantic analyzer tree
std::unordered_map<std::string, int> priority = {
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};

void semantic_analyzer::construct_tree(vector<string> &tokens) {
  stack<shared_ptr<ASTNode>> nodeStack; // operand stack
  stack<char> opStack;                  // operatod stack

  // itetate tokens
  for (auto &token : tokens) {
    if (is_all_whitespace(token)) {
      shared_ptr<ASTNode> node(new ASTNode(' ', 0, nullptr, nullptr));
      nodeStack.push(node);
    }
    // If it is an operand, construct an ASTNode and push into operand stack
    else if (is_digit(token)) {
      int val = stoi(token);
      nodeStack.push(make_shared<ASTNode>(' ', val));
    }
    // If it is a left paren, push it into operator stack
    else if (token == "(") {
      opStack.push('(');
    }
    // If it is a right paren, pop the operator in the operator stack and
    // calculate result
    else if (token == ")") {
      // Keep popping operatos in the operator stack until a left paren
      while (opStack.top() != '(') {
        // Pop two operands in the operand stack and construct them into a node
        shared_ptr<ASTNode> right = nodeStack.top();
        nodeStack.pop();
        shared_ptr<ASTNode> left = nodeStack.top();
        nodeStack.pop();
        // Construct a new ASTNode with the two nodes and push into the stack
        shared_ptr<ASTNode> node(new ASTNode(opStack.top(), 0, left, right));
        opStack.pop();
        nodeStack.push(node);
      }
      opStack.pop(); // pop left paren
    }
      // If it is #
    else if (token == "#") {
      continue;
    }
    // If it is an operator, compare its priority with the operator on the top
    // of the stack
    else {
      char op = token[0];
      while (!opStack.empty() && opStack.top() != '(' &&
             priority[string(1, opStack.top())] >= priority[string(1, op)]) {
        // Pop two operands in the stack and construct them into an ASTNode
        shared_ptr<ASTNode> right = nodeStack.top();
        nodeStack.pop();
        shared_ptr<ASTNode> left = nodeStack.top();
        nodeStack.pop();
        // Construct a new ASTNode with the two nodes and push it into the
        // operand stack
        shared_ptr<ASTNode> node =
            make_shared<ASTNode>(opStack.top(), 0, left, right);
        opStack.pop();
        nodeStack.push(node);
      }
      opStack.push(op);
    }
  }

  // Process operators and operands in the stack and construct the tree
  while (!opStack.empty()) {
    shared_ptr<ASTNode> right = nodeStack.top();
    nodeStack.pop();
    shared_ptr<ASTNode> left = nodeStack.top();
    nodeStack.pop();
    shared_ptr<ASTNode> node =
        make_shared<ASTNode>(opStack.top(), 0, left, right);
    opStack.pop();
    nodeStack.push(node);
  }

  this->_root = nodeStack.top();
  nodeStack.pop();
}
