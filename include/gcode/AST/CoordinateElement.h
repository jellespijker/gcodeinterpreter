//
// Created by Jelle Spijker on 02-05-21.
//

#include "gcode/AST/Element.h"

#ifndef GCODE_COORDINATEELEMENT_H
#define GCODE_COORDINATEELEMENT_H

namespace gcode {
class CoordinateElement : public Element
{
public:
  CoordinateElement(const Token& token, const shared_elem_t& variables) : Element{ token, variables } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace gcode

#endif// GCODE_COORDINATEELEMENT_H
