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
  spdlog::info("Lexing the gcode file");
  const std::regex regword(R"(\b(\S+)\b|;)", std::regex_constants::ECMAScript);
  const auto lines = Lexer::split(gcode, "\n");// TODO: Check with benchmark if this function is indeed quicker the ranges
  constexpr size_t avg_tokens_per_line = 10;// Roughly 10 tokens per line
  std::vector<Token> tokens;
  tokens.reserve(lines.size() * avg_tokens_per_line);

  // Loop through all lines
  for (const auto& line : lines | ranges::views::enumerate) {// TODO: Check if line number is necesarry, now not used
    if (line.second.size() < 2) {// Early out for empty line
      continue;
    }
    tokens.emplace_back(Token{ line.second, Token::LINE });
    spdlog::debug("Line {} -> Lexing token<{}>", line.first, tokens.back());
    const auto words = line.second | rv::tokenize(regword);// Split each line up in words and the ; character
    const auto command_view = words | rv::take(1);// The first word is the command, ; is considerd a comment command
    const auto cmd = get_sv(*command_view.begin());

    // Construct the actually tokens for the line
    if (cmd.starts_with(';')) {// This is a full line comment
      const auto comment = std::string_view{ line.second.begin() + cmd.size(), line.second.size() - cmd.size() };
      tokens.emplace_back(Token{ comment, Token::COMMENT });
      spdlog::debug("Line {} -> Lexing token<{}>", line.first, tokens.back());
    } else {// This a command with/or without a comment or a Tool change
      if (cmd.starts_with('T')) {// Command is a tool change
        tokens.emplace_back(Token{ std::string_view{ cmd.begin(), 1 }, Token::TOOL });
        tokens.emplace_back(Token{ std::string_view{ cmd.begin() + 1, cmd.size() - 1 }, Token::VALUE });
        continue;
      }
      tokens.emplace_back(Token{ cmd, Token::COMMAND });
      spdlog::debug("Line {} -> Lexing token<{}>", line.first, tokens.back());
      // Loop through the arguments, all words after the command
      for (const auto& argument : words | rv::tail) {
        const auto atom = get_sv(argument);
        const auto arg = std::string_view{ atom.begin(), 1 };// This can either be a comment or a variable name
        if (arg.starts_with(';')) {// Construct a comment and skip the remaining words since these belong to the comment
          const auto comment = std::string_view{ atom.begin() + arg.size(), line.second.size() - line.second.find(';') - 1 };
          tokens.emplace_back(Token{ comment, Token::COMMENT });
          spdlog::debug("Line {} -> Lexing token<{}>", line.first, tokens.back());
          break;
        }
        // TODO: implement the T variable (no-prio since UM doesn't use that in such a way)
        tokens.emplace_back(Token{ arg, Token::VARIABLE });
        spdlog::debug("Line {} -> Lexing token<{}>", line.first, tokens.back());
        const auto value = std::string_view{ atom.begin() + 1, atom.size() - 1 };// This is the numeric value of the variable
        tokens.emplace_back(Token{ value, Token::VALUE });
        spdlog::debug("Line {} -> Lexing token<{}>", line.first, tokens.back());
      }
    }
  }
  lexer.setTokens(tokens);
  return lexer;
}

Lexer& operator<<(Lexer& lexer, std::ifstream& file)
{
  spdlog::info("Storing gcode file in memory");
  std::string raw_data;
  raw_data.assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
  lexer.setRawData(raw_data);
  std::string_view gcode{ lexer.getRawData() };
  lexer << gcode;
  return lexer;
}

std::vector<std::string_view> Lexer::split(std::string_view strv, std::string_view delims)
{
  spdlog::debug("Splitting the string_view in a vector of string_views with delimiter: {}", delims);
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

const std::vector<Token>& Lexer::getTokens() const
{
  return m_tokens;
}

void Lexer::setTokens(const std::vector<Token>& Tokens)
{
  m_tokens = Tokens;
}

const std::string& Lexer::getRawData() const
{
  return m_raw_data;
}

void Lexer::setRawData(const std::string& rawData)
{
  m_raw_data = rawData;
}

}// namespace ghermeneus
