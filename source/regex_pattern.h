/**
 * @file regex_pattern.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief This file defines the regex patterns of PL/0
 * @date 2023-04-20
 */
#ifndef LIB_2CXX_REGEX_PATTERN_H
#define LIB_2CXX_REGEX_PATTERN_H

#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

using std::regex;
using std::string;
using std::vector;

/**
 * The string objects starts with 'regstr' means "regex pattern string".
 * In the first half of this file, some even very complex regular
 * expression patterns are constructed to facilitate subsequent
 * construction of regular expression objects.
 *
 * You may find two different editions for the same pattern, we usually
 * test the unassembled edition and write a brief edition for flexibility.
 */

/**
 * @brief The legal letters in PL/0
 */
const string regstr_letter = "[A-Za-z]";
/**
 * @brief The digit number in PL/0
 */
const string regstr_digit = R"(\d)";
/**
 * @brief The parens in PL/0
 */
const string regstr_paren = R"([\(\)])";
/**
 * @brief The semicolon in PL/0
 */
const string regstr_semi = R"(;)";
/**
 * @brief The regex for identifiers:
 *
 * 1. The length of the identifiers should be shorter than 10
 * 2. The begin of the identifier should be a letter
 */
const string regstr_identifier = "(" + regstr_letter + R"(\w{0,9}))";
/**
 * @brief The regex for compound identifier statement
 */
const string regstr_identifier_unassembled = R"(([A-Za-z]\w{0,9}))";
/**
 * @brief The regex for unsigned integers.
 */
const string regstr_unsigned = R"(\d+)";
/**
 * @brief The brief edition for constant variables definition.
 */
const string regstr_const_define =
    regstr_identifier + R"(\s*=\s*)" + regstr_unsigned;
/**
 * @brief The unassembled edition for constant variables definition.
 */
const string regstr_const_define_unassembled = R"(([A-Za-z]\w{0,9})\s*=\s*\d+)";
/**
 * @brief The brief edition for constant variables declaration.
 */
const string regstr_const_declare = R"(const\s+)" + regstr_const_define + "(" +
                                    R"(\s*,\s*)" + regstr_const_define + ")" +
                                    R"(*\s*;)";
/**
 * @brief The unassembled edition for constant variables declaration.
 */
const string regstr_const_declare_unassembled =
    R"(const\s+([A-Za-z]\w{0,9})\s*=\s*\d+(\s*,\s*([A-Za-z]\w{0,9})\s*=\s*\d+)*\s*;)";
/**
 * @brief The brief edition for variable declaration
 */
const string regstr_variable = R"(var\s+()" + regstr_identifier +
                               R"((\s*,\s*)" + regstr_identifier + R"()*)\s*;)";
/**
 * @brief The unassembled edition for variable declaration
 */
const string regstr_variable_unassembled =
    R"(var\s+(([A-Za-z]\w{0,9})(\s*,\s*([A-Za-z]\w{0,9}))*)\s*;)";
/**
 * @brief The brief edition for procedure header declaration.
 */
const string regstr_procedure_header =
    R"(procedure\s+)" + regstr_identifier + R"(\s*;)";
/**
 * @brief The unassembled edition for procedure header declaration.
 */
const string regstr_procedure_header_unassembled =
    R"(procedure\s+([A-Za-z]\w{0,9})\s*;)";
/**
 * @brief The regex for plus operators
 */
const string regstr_operator_plus = R"((\+|-))";
/**
 * @brief The regex for times operators
 */
const string regstr_operator_times = R"((\*|/))";
/**
 * @brief The regex for relation operators
 */
const string regstr_operator_relation = R"(([^(:=)]=|#|(<>)|(>=)|(<=)|>|<))";
/**
 * @brief The brief edition for factor, which is called "因子" in Chinese.
 */
const string regstr_factor =
    regstr_identifier + "|" + regstr_unsigned + "|" + R"((\(.*?\)))";
/**
 * @brief The unassembled edition for factor, which is called "因子" in Chinese.
 */
const string regstr_factor_unassembled = R"(([A-Za-z]\w{0,9})|\d+|(\(.*?\)))";
/**
 * @brief The brief edition for item, which is called "词项" in Chinese.
 */
const string regstr_item = "(" + regstr_factor + R"()(\s*)" +
                           regstr_operator_times + R"(\s*()" + regstr_factor +
                           R"())*)";
/**
 * @brief The unassembled edition for item, which is called "词项" in Chinese.
 */
const string regstr_item_unassembled =
    R"((([A-Za-z]\w{0,9})|\d+|(\(.*?\)))(\s*(\*|/)\s*(([A-Za-z]\w{0,9})|\d+|(\(.*?\))))*)";
/**
 * @brief The brief edition for expression
 */
const string regstr_expression = R"([\+|-]?\s*)" + regstr_item + R"((\s*)" +
                                 regstr_operator_plus + R"(\s*)" + regstr_item +
                                 R"()*)";
/**
 * @brief The unassembled edition for expression
 */
const string regstr_expression_unassembled =
    R"([\+|-]?\s*(([A-Za-z]\w{0,9})|\d+|(\(.*?\)))(\s*(\*|/)\s*(([A-Za-z]\w{0,9})|\d+|(\(.*?\))))*(\s*(\+|-)\s*(([A-Za-z]\w{0,9})|\d+|(\(.*?\)))(\s*(\*|/)\s*(([A-Za-z]\w{0,9})|\d+|(\(.*?\))))*)*)";
/**
 * @brief The regex pattern for assignment
 */
const string regstr_assign =
    regstr_identifier + R"(\s*:=\s*)" + regstr_expression + R"(;+)";
/**
 * @brief The regex pattern for assignment operator
 */
const string regstr_operator_assign = R"(:=)";
/**
 * @brief The regex pattern for condition expression
 *
 * 1. identifier1 [(=)|(#)|(<>)|(<=)|(>=)|(<)|(>)] identifier2
 * 2. odd identifier
 */
const string regstr_condition_expression =
    R"(()" + regstr_expression + R"(\s*)" + regstr_operator_relation +
    R"(\s*)" + regstr_expression + R"()|(\s*odd\s*)" + regstr_expression +
    R"())";
/**
 * @brief The regex pattern for if statement
 */
const string regstr_if =
    R"(if\s*()" + regstr_condition_expression + R"()\s*then\s*.*?)";
/**
 * @brief The regex pattern for while statement
 *
 */
const string regstr_while =
    R"(while\s+()" + regstr_condition_expression + R"()\s*do\s*.*?)";
/**
 * @brief The regex pattern for procedure calling
 */
const string regstr_procedure_call = R"(call\s+)" + regstr_identifier;
/**
 * @brief The regex pattern for procedure declaration
 *
 */
const string regstr_procedure_declaration = regstr_procedure_header + R"(.*?)";
/**
 * @brief The regex pattern for read
 */
const string regstr_read = R"(read\s*\(.*?\)\s*;?)";
/**
 * @brief The regex pattern for write
 */
const string regstr_write = R"(write\s*\(.*?\)\s*;?)";
/**
 * @brief The regex pattern for compound expressions.
 */
const string regstr_compound = R"(begin\s*.*\s*end.)";
/**
 * @brie The regex pattern for sentence
 *
 */
const string regstr_sentence =
    R"((()" + regstr_compound + ")|(" + regstr_if + ")|(" + regstr_while +
    ")|(" + regstr_procedure_call + ")|(" + regstr_read + ")|(" + regstr_write +
    ")|(" + regstr_assign + R"()))";
/**
 * @brief The regex pattern for a sub-program
 */
const string regstr_sub_program =
    R"(()" + regstr_const_declare + R"()*()" + regstr_variable + R"()*()" +
    regstr_procedure_declaration + R"()*()" + regstr_sentence + R"()+)";
/**
 * @brief The regex pattern for a program
 */
const string regstr_program = regstr_sub_program;

#ifdef _PRINT_REGEX_

#define REGEX_PRINT_TRANS(var)                                                 \
  { #var, var }

const vector<std::pair<string, string>> regstrs = {
    REGEX_PRINT_TRANS(regstr_letter),
    REGEX_PRINT_TRANS(regstr_digit),
    REGEX_PRINT_TRANS(regstr_semi),
    REGEX_PRINT_TRANS(regstr_paren),
    REGEX_PRINT_TRANS(regstr_identifier_unassembled),
    REGEX_PRINT_TRANS(regstr_identifier),
    REGEX_PRINT_TRANS(regstr_unsigned),
    REGEX_PRINT_TRANS(regstr_const_define),
    REGEX_PRINT_TRANS(regstr_const_define_unassembled),
    REGEX_PRINT_TRANS(regstr_const_declare),
    REGEX_PRINT_TRANS(regstr_const_declare_unassembled),
    REGEX_PRINT_TRANS(regstr_variable),
    REGEX_PRINT_TRANS(regstr_variable_unassembled),
    REGEX_PRINT_TRANS(regstr_procedure_header),
    REGEX_PRINT_TRANS(regstr_procedure_header_unassembled),
    REGEX_PRINT_TRANS(regstr_procedure_declaration),
    REGEX_PRINT_TRANS(regstr_operator_plus),
    REGEX_PRINT_TRANS(regstr_operator_times),
    REGEX_PRINT_TRANS(regstr_operator_relation),
    REGEX_PRINT_TRANS(regstr_operator_assign),
    REGEX_PRINT_TRANS(regstr_factor),
    REGEX_PRINT_TRANS(regstr_factor_unassembled),
    REGEX_PRINT_TRANS(regstr_item),
    REGEX_PRINT_TRANS(regstr_item_unassembled),
    REGEX_PRINT_TRANS(regstr_expression),
    REGEX_PRINT_TRANS(regstr_expression_unassembled),
    REGEX_PRINT_TRANS(regstr_assign),
    REGEX_PRINT_TRANS(regstr_condition_expression),
    REGEX_PRINT_TRANS(regstr_if),
    REGEX_PRINT_TRANS(regstr_procedure_call),
    REGEX_PRINT_TRANS(regstr_while),
    REGEX_PRINT_TRANS(regstr_read),
    REGEX_PRINT_TRANS(regstr_write),
    REGEX_PRINT_TRANS(regstr_compound),
    REGEX_PRINT_TRANS(regstr_sentence),
    REGEX_PRINT_TRANS(regstr_sub_program),
    REGEX_PRINT_TRANS(regstr_program)};

inline void print_all_patterns() {
  for (auto pattern : regstrs) {
    std::cout << pattern.first << ":" << std::endl;
    std::cout << pattern.second << std::endl;
    std::cout << string(50, '=') << std::endl;
  }
}

#endif // _PRINT_REGEX_

/**
 * Here are the regex objects constructed with the regex pattern strings
 * declared earlier. All objects are case insensitive.
 */

#define REGEX_DEFINE(var_name, param_name)                                     \
  const regex var_name(param_name, std::regex::icase)

REGEX_DEFINE(reg_letter, regstr_letter);
REGEX_DEFINE(reg_digit, regstr_digit);
REGEX_DEFINE(reg_semi, regstr_semi);
REGEX_DEFINE(reg_paren, regstr_paren);
REGEX_DEFINE(reg_identifier, regstr_identifier);
REGEX_DEFINE(reg_unsigned, regstr_unsigned);
REGEX_DEFINE(reg_const_define, regstr_const_define);
REGEX_DEFINE(reg_const_declare, regstr_const_declare);
REGEX_DEFINE(reg_variable, regstr_variable);
REGEX_DEFINE(reg_procedure_header, regstr_procedure_header);
REGEX_DEFINE(reg_procedure_declaration, regstr_procedure_declaration);
REGEX_DEFINE(reg_operator_plus, regstr_operator_plus);
REGEX_DEFINE(reg_operator_times, regstr_operator_times);
REGEX_DEFINE(reg_operator_relation, regstr_operator_relation);
REGEX_DEFINE(reg_factor, regstr_factor);
REGEX_DEFINE(reg_item, regstr_item);
REGEX_DEFINE(reg_expression, regstr_expression);
REGEX_DEFINE(reg_assign, regstr_assign);
REGEX_DEFINE(reg_operator_assign, regstr_operator_assign);
REGEX_DEFINE(reg_condition_expression, regstr_condition_expression);
REGEX_DEFINE(reg_if, regstr_if);
REGEX_DEFINE(reg_procedure_call, regstr_procedure_call);
REGEX_DEFINE(reg_while, regstr_while);
REGEX_DEFINE(reg_read, regstr_read);
REGEX_DEFINE(reg_write, regstr_write);
REGEX_DEFINE(reg_compound, regstr_compound);
REGEX_DEFINE(reg_sentence, regstr_sentence);
REGEX_DEFINE(reg_sub_program, regstr_sub_program);
REGEX_DEFINE(reg_program, regstr_program);

#endif //LIB_2CXX_REGEX_PATTERN_H
