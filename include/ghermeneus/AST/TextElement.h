//
// Created by Jelle Spijker on 16-05-21.
//

#ifndef GHERMENEUS_TEXTELEMENT_H
#define GHERMENEUS_TEXTELEMENT_H

#include "ghermeneus/AST/Element.h"

namespace ghermeneus {
class TextElement : public Element
{
public:
  explicit TextElement(const Token& token) : Element{ token } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace ghermeneus
#endif// GHERMENEUS_TEXTELEMENT_H
