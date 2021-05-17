//
// Created by Jelle Spijker on 25-04-21.
//

#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H

#include <vector>

#include "gcode/Lexer.h"
#include "gcode/AST/Element.h"

namespace gcode {
class Parser
{
public:
  friend Parser& operator<<(Parser& parser, Lexer& lexer);

  [[nodiscard]] const elem_vec_t& getAST() const;
  void setAST(const elem_vec_t& ast);

private:
  elem_vec_t m_ast;
};
}// namespace gcode

#endif// GCODE_PARSER_H
