//
// Created by Jelle Spijker on 25-04-21.
//

#include <range/v3/view/split_when.hpp>
#include <range/v3/view/tail.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/all.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


#include "ghermeneus/Parser.h"
#include "ghermeneus/ElementFactory.h"

namespace rv = ranges::views;
namespace rg = ranges;
using namespace std::literals;

namespace ghermeneus {

Parser& operator<<(Parser& parser, Lexer& lexer)
{
  spdlog::info("Parsing the tokens of the lexer");
  auto lines = lexer.getTokens() | rv::tail | rv::split_when([](const auto& token) { return token.getType() == Token::LINE; });

  // Create the Abstract Syntax Tree
  elem_vec_t ast;
  // TODO: check if I need to reserve space

  // Create the Machine
  auto parent = ElementFactory::newElement(Token{ "Machine"sv, Token::MACHINE }).value();
  ast.emplace_back(parent);
  for (const auto& line : lines) {
    ast.emplace_back(ElementFactory::newElement(line | rg::to_vector, parent).value());
    if (ast.back()->isParent()) {
      parent = ast.back();
    }
  }

  parser.setAST(ast);
  return parser;
}

const elem_vec_t & Parser::getAST() const
{
  return m_ast;
}

void Parser::setAST(const elem_vec_t & ast)
{
  m_ast = ast;
}
}// namespace ghermeneus
