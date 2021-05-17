//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GCODE_NUMERICELEMENT_H
#define GCODE_NUMERICELEMENT_H

#include "gcode/AST/Element.h"

namespace gcode {
class NumericElement : public Element
{
public:
  explicit NumericElement(const Token& token) : Element{ token } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace gcode

#endif// GCODE_NUMERICELEMENT_H
