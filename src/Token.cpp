//
// Created by Jelle Spijker on 25-04-21.
//

#include "ghermeneus/Token.h"

namespace ghermeneus {

Token::Token(std::string_view word, Token::Type token_type) : m_word(word), m_type(token_type)
{
}

std::string_view Token::getWord() const
{
  return m_word;
}

Token::Type Token::getType() const
{
  return m_type;
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
  os << "m_word: " << token.m_word << " m_type: " << token.m_type;
  return os;
}

}// namespace ghermeneus
