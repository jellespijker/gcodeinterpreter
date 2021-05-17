//
// Created by Jelle Spijker on 25-04-21.
//

#ifndef GCODE_LEXER_H
#define GCODE_LEXER_H

#include <string_view>
#include <fstream>
#include <memory>
#include <vector>
#include <regex>

#include "gcode/Token.h"

namespace gcode {

class Lexer
{
public:
  friend Lexer& operator<<(Lexer& lexer, std::string_view gcode);

  friend Lexer& operator<<(Lexer& lexer, std::ifstream& file);

  [[nodiscard]] const std::vector<Token>& getTokens() const;
  void setTokens(const std::vector<Token>& Tokens);

  [[nodiscard]] const std::string& getRawData() const;
  void setRawData(const std::string& rawData);

protected:
  static std::vector<std::string_view> split(std::string_view strv, std::string_view delims = " ");

private:
  std::vector<Token> m_tokens;

  std::string m_raw_data;
};

using svsub_match = std::sub_match<std::string_view::const_iterator>;

[[nodiscard]] inline std::string_view get_sv(const svsub_match& m)
{
  return std::string_view(m.first, static_cast<size_t>(m.length()));
}

}// namespace gcode

#endif// GCODE_LEXER_H
