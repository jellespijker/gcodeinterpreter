//
// Created by Jelle Spijker on 25-04-21.
//

#ifndef GHERMENEUS_PARSER_H
#define GHERMENEUS_PARSER_H

#include <vector>

#include "ghermeneus/Lexer.h"
#include "ghermeneus/AST/Element.h"

namespace ghermeneus {
class Parser
{
public:
  friend Parser& operator<<(Parser& parser, Lexer& lexer);

  [[nodiscard]] const elem_vec_t & getAST() const;
  void setAST(const elem_vec_t & ast);

private:
  elem_vec_t m_ast;
};
}// namespace ghermeneus

#endif//GHERMENEUS_PARSER_H
