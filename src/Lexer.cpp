//
// Created by Jelle Spijker on 25-04-21.
//

#include <range/v3/view/take.hpp>
#include <range/v3/view/tokenize.hpp>
#include <range/v3/view/tail.hpp>
#include <range/v3/view/enumerate.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "ghermeneus/Lexer.h"

namespace rg = ranges;
namespace rv = ranges::views;
using namespace std::literals;

namespace ghermeneus {

Lexer& operator<<(Lexer& lexer, std::string_view gcode)
{
  auto lines = Lexer::lex(gcode);
  for (const auto& l : lines) {
    spdlog::debug("Token: {}", l);
  }
  return lexer;
}

Lexer& operator<<(Lexer& lexer, std::ifstream& file)
{
  lexer.raw_data.assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
  std::string_view gcode{ lexer.raw_data };
  lexer << gcode;
  return lexer;
}

std::vector<Token> Lexer::lex(const std::string_view gcode)
{
  const std::regex regword(R"(\b(\S+)\b|;)", std::regex_constants::ECMAScript);
  const auto lines = Lexer::split(gcode, "\n");// TODO: Check with benchmark if this function is indeed quicker the ranges
  std::vector<Token> tokens;
  constexpr size_t avg_tokens_per_line = 10;// Roughly 10 tokens per line
  tokens.reserve(lines.size() * avg_tokens_per_line);

  // Loop through all lines
  for (const auto& line : lines | ranges::views::enumerate) {// TODO: Check if line number is necesarry, now not used
    if (line.second.size() < 2) {// Early out for empty line
      continue;
    }
    tokens.emplace_back(Token{ line.second, Token::LINE });
    const auto words = line.second | rv::tokenize(regword);// Split each line up in words and the ; character
    const auto command_view = words | rv::take(1);// The first word is the command, ; is considerd a comment command
    const auto cmd = get_sv(*command_view.begin());

    // Construct the actually tokens for the line
    if (cmd.starts_with(';')) {// This is a full line comment
      const auto comment = std::string_view{ line.second.begin() + cmd.size(), line.second.size() - cmd.size() };
      tokens.emplace_back(Token{ comment, Token::COMMENT });
    } else {// This a command with/or without a comment
      tokens.emplace_back(Token{ cmd, Token::COMMAND });
      // Loop through the arguments, all words after the command
      for (const auto& argument : words | rv::tail) {
        const auto atom = get_sv(argument);
        const auto arg = std::string_view(atom.begin(), 1);// This can either be a comment or a variable name
        if (arg.starts_with(';')) {// Construct a comment and skip the remaining words since these belong to the comment
          const auto comment = std::string_view{ atom.begin() + arg.size(), line.second.size() - line.second.find(';') - 1 };
          tokens.emplace_back(Token{ comment, Token::COMMENT });
          break;
        }
        tokens.emplace_back(Token{ arg, Token::VARIABLE });
        const auto value = std::string_view(atom.begin() + 1, atom.size() - 1);// This is the numeric value of the variable
        tokens.emplace_back(Token{ value, Token::VALUE });
      }
    }
  }
  return tokens;
}

std::vector<std::string_view> Lexer::split(std::string_view strv, std::string_view delims)
{
  std::vector<std::string_view> output;
  size_t first = 0;

  while (first < strv.size()) {
    const auto second = strv.find_first_of(delims, first);

    if (first != second) {
      output.emplace_back(strv.substr(first, second - first));
    }

    if (second == std::string_view::npos) {
      break;
    }
    first = second + 1;
  }

  return output;
}

}// namespace ghermeneus
