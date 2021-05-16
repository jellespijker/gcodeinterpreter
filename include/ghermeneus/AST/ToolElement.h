//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GHERMENEUS_TOOLELEMENT_H
#define GHERMENEUS_TOOLELEMENT_H

#include "Element.h"

namespace ghermeneus {
class ToolElement : public Element
{
public:
  explicit ToolElement(const Token& token) : Element{ token }, m_tool_index{ 0 } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;

protected:
  [[maybe_unused]] size_t m_tool_index;
};

}// namespace ghermeneus

#endif// GHERMENEUS_TOOLELEMENT_H
