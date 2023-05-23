#include "lexical_analyzer.h"
#include "semantic_analyzer.h"
#include "slr1.h"
#include "intermediate_code_generator.h"
#include "DAG_optimizer.h"
#include "regex_pattern.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  const string delimiter_line(80, '-');
#ifndef _PRINT_REGEX_
  const char *BASE_INPUT_FILENAME_PRE = "../test_files/input";
  const char *BASE_FILENAME_POST = ".txt";
  const char *BASE_OUTPUT_FILENAME_PRE = "../output/output";

  ifstream fin;   // input file stream
  ofstream fout;  // output file stream

  lexical_analyzer lexicalAnalyzer;                       // lexical analyzer
  semantic_analyzer semanticAnalyzer;                     // semantic analyzer
  slr1 slr1;                                              // SLR1 parser
  intermediate_code_generator intermediateCodeGenerator;  // intermediate code generator
  DAG_optimizer dagOptimizer;                             // DAG optimizer

  vector<Token> tokens; // tokens

  for (size_t count = 1; count <= 10; ++count) {
    // generate filename and open file
    string file_name_input =
            BASE_INPUT_FILENAME_PRE + to_string(count) + BASE_FILENAME_POST;
    string file_name_output =
            BASE_OUTPUT_FILENAME_PRE + to_string(count) + BASE_FILENAME_POST;

    fin.open(file_name_input);
    if (!fin.is_open()) {
      throw ios_base::failure("file " + file_name_input + " open failed");
    }

    fout.open(file_name_output);
    if (!fout.is_open()) {
      throw ios_base::failure("file " + file_name_output + " open failed");
    }

    // read text and parse it into {Token, Lexeme} pairs
    lexicalAnalyzer.clear();
    lexicalAnalyzer.read_text(fin);
    lexicalAnalyzer.parse_text();

    // judge if the expression is valid
    slr1.clear();
    bool is_valid = slr1.parse(lexicalAnalyzer.get_list());
    if (!is_valid) {
      fout << file_name_input << " is not valid" << endl;
      continue;
    }

    // transform {Token, Lexem} into {Lexem}
    tokens.clear();
    transform(lexicalAnalyzer.get_list().begin(),
              lexicalAnalyzer.get_list().end(), back_inserter(tokens),
              [](const lexical_pair &pair) -> Token { return pair.second; });

    // construct semantic tree
    semanticAnalyzer.clear();
    semanticAnalyzer.construct_tree(tokens);

    // transform semantic tree into quadruple
    intermediateCodeGenerator.clear();
    intermediateCodeGenerator.generate_quadruples(semanticAnalyzer.get_root());

    // optimize quadruple with DAG
    dagOptimizer.clear();
    dagOptimizer.read_origin_nodes(intermediateCodeGenerator.get_quadruples());
    dagOptimizer.optimize_quadruples();

    fout << "Read expression: " << lexicalAnalyzer.get_expression() << endl;
    fout << delimiter_line << endl;
    fout << "Tokens: " << endl;
    for (const auto &token: lexicalAnalyzer.get_list()) {
      fout << "( " << token.first << ", " << token.second << " )" << endl;
    }
    fout << delimiter_line << endl;
    fout << "Parsed quadruples: " << endl;
    for (const auto &quad: intermediateCodeGenerator.get_quadruples()) {
      fout << "( " << (quad.op == '=' ? ":=" : string(1, quad.op)) << ", "
           << intermediate_code_generator::quadruple::item2str(quad.operand1)
           << ", "
           << intermediate_code_generator::quadruple::item2str(quad.operand2)
           << ", "
           << intermediate_code_generator::quadruple::item2str(quad.count)
           << " )" << endl;
    }
    fout << delimiter_line << endl;
    fout << "Optimized quadruples: " << endl;
    for (auto &quad: dagOptimizer.get_optimized()) {
      fout << "( " << (quad.op == '=' ? ":=" : string(1, quad.op)) << ", "
           << intermediate_code_generator::quadruple::item2str(quad.operand1)
           << ", "
           << intermediate_code_generator::quadruple::item2str(quad.operand2)
           << ", "
           << intermediate_code_generator::quadruple::item2str(quad.count)
           << " )" << endl;
    }
    fout << delimiter_line << endl;
    fout << "Expression result: " << semanticAnalyzer.evaluate() << endl;

    tokens.clear();
    fout.close();
    fin.close();
  }
#else
  for (const auto& p : regstrs) {
    cout << p.first << ":\n" << p.second << endl;
    cout << delimiter_line << endl;
  }
#endif
}
