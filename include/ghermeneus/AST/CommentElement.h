//
// Created by Jelle Spijker on 02-05-21.
//

#ifndef GHERMENEUS_COMMENTELEMENT_H
#define GHERMENEUS_COMMENTELEMENT_H

#include "Element.h"

namespace ghermeneus {
class CommentElement : public Element
{
public:
  explicit CommentElement(const Token& token) : Element(token){};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace ghermeneus

#endif//GHERMENEUS_COMMENTELEMENT_H
