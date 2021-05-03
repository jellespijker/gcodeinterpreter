//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GHERMENEUS_CHANGEELEMENT_H
#define GHERMENEUS_CHANGEELEMENT_H

#include "Element.h"

namespace ghermeneus {
class ChangeElement : public Element
{
public:
  explicit ChangeElement(const Token& token) : Element(token){};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace ghermeneus

#endif//GHERMENEUS_CHANGEELEMENT_H
