//
// Created by Jelle Spijker on 02-05-21.
//

#include "ghermeneus/AST/Element.h"

#ifndef GHERMENEUS_COORDINATEELEMENT_H
#define GHERMENEUS_COORDINATEELEMENT_H

namespace ghermeneus {
class CoordinateElement : public Element
{
public:
  CoordinateElement(const Token& token, const shared_elem_t& variables) : Element{ token, variables } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace ghermeneus

#endif// GHERMENEUS_COORDINATEELEMENT_H
