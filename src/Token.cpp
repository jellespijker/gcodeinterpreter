//
// Created by Jelle Spijker on 25-04-21.
//

#include "ghermeneus/Token.h"

namespace ghermeneus {

std::ostream& operator<<(std::ostream& os, const Token& token)
{
  os << "word: " << token.m_word << " type: ";
  switch (token.m_type) {
  case Token::LINE:
    os << "Line";
    break;
  case Token::MACHINE:
    os << "Machine";
    break;
  case Token::TOOL:
    os << "Tool";
    break;
  case Token::COMMAND:
    os << "Command";
    break;
  case Token::VARIABLE:
    os << "Variable";
    break;
  case Token::VALUE:
    os << "Value";
    break;
  case Token::COMMENT:
    os << "Comment";
    break;
  default:
    os << "Unknown";
  }
  return os;
}

const std::string_view& Token::getWord() const { return m_word; }

Token::Type Token::getType() const { return m_type; }

}// namespace ghermeneus
