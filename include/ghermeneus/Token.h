//
// Created by Jelle Spijker on 25-04-21.
//

#ifndef GHERMENEUS_TOKEN_H
#define GHERMENEUS_TOKEN_H

#include <string_view>
#include <memory>
#include <ostream>

namespace ghermeneus {
class Token
{
public:
  enum Type { LINE, MACHINE, COMMAND, TOOL, VARIABLE, VALUE, COMMENT };

  Token(const std::string_view word, const Type token_type) : m_word(word), m_type(token_type){};

  friend std::ostream& operator<<(std::ostream& os, const Token& token);

  [[nodiscard]] const std::string_view& getWord() const;

  [[nodiscard]] Type getType() const;

private:
  std::string_view m_word;

  Type m_type;
};

}// namespace ghermeneus

#endif// GHERMENEUS_TOKEN_H
