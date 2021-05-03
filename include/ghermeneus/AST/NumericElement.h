//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GHERMENEUS_NUMERICELEMENT_H
#define GHERMENEUS_NUMERICELEMENT_H

#include "ghermeneus/AST/Element.h"

namespace ghermeneus {
class NumericElement : public Element {
public:
  explicit NumericElement(const Token& token) : Element(token) {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}

#endif//GHERMENEUS_NUMERICELEMENT_H
