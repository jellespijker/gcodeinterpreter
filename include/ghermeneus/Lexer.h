//
// Created by Jelle Spijker on 25-04-21.
//

#ifndef GHERMENEUS_LEXER_H
#define GHERMENEUS_LEXER_H

#include <string_view>
#include <fstream>
#include <memory>
#include <vector>
#include <regex>

#include "ghermeneus/Token.h"

namespace ghermeneus {

class Lexer
{
public:
  friend Lexer& operator<<(Lexer& lexer, std::string_view gcode);

  friend Lexer& operator<<(Lexer& lexer, std::ifstream& file);

protected:
  std::string raw_data;

  static std::vector<Token> lex(std::string_view gcode);

  static std::vector<std::string_view> split(std::string_view strv, std::string_view delims = " ");
};

using svsub_match = std::sub_match<std::string_view::const_iterator>;

inline std::string_view get_sv(const svsub_match& m)
{
  return std::string_view(m.first, static_cast<size_t>(m.length()));
}

}// namespace ghermeneus

#endif//GHERMENEUS_LEXER_H