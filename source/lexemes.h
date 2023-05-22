/**
 * @file lexemes.h
 * @author Yuan Liu (Liuyuan\@shu.edu.cn)
 * @brief Contains the maps for PL/0 key words
 * @date 2023-04-20
 */
#ifndef LIB_2CXX_LEXEMES_H
#define LIB_2CXX_LEXEMES_H

#include <string>
#include <unordered_map>
#include <utility>

using std::string;
using std::unordered_map;

typedef string Lexeme;
typedef string Token;
typedef std::pair<Token, Lexeme> lexical_pair;

// The reserved keywords of PL/0
const unordered_map<Lexeme, Token> reserved = {
        {"begin",     "beginsym"},
        {"call",      "callsym"},
        {"const",     "constsym"},
        {"do",        "dosym"},
        {"end",       "endsym"},
        {"if",        "ifsym"},
        {"odd",       "oddsym"},
        {"procedure", "proceduresym"},
        {"read",      "readsym"},
        {"then",      "thensym"},
        {"else",      "elsesym"},
        {"var",       "varsym"},
        {"while",     "whilesym"},
        {"write",     "writesym"}};

// The operators of PL/0
const unordered_map<Lexeme, Token> operators = {
        {"+",  "plus"},
        {"-",  "minus"},
        {"*",  "times"},
        {"/",  "slash"},
        {"=",  "eql"},
        {"#",  "neq"},
        {"<>", "neq"},
        {"<",  "lss"},
        {"<=", "leq"},
        {">",  "gtr"},
        {">=", "geq"},
        {":=", "becomes"}};

// The delimiters of PL/0
const unordered_map<Lexeme, Token> delimiters = {{"(", "lparen"},
                                                 {")", "rparen"},
                                                 {",", "comma"},
                                                 {";", "semicolon"},
                                                 {".", "period"}};

#endif // ! LIB_2CXX_LEXEMES_H
