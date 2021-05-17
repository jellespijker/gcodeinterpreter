//
// Created by Jelle Spijker on 16-05-21.
//

#ifndef GCODE_TEXTELEMENT_H
#define GCODE_TEXTELEMENT_H

#include "gcode/AST/Element.h"

namespace gcode {
class TextElement : public Element
{
public:
  explicit TextElement(const Token& token) : Element{ token } {};

  [[nodiscard]] row_t eval() const override;

  [[nodiscard]] bool isParent() const override;
};
}// namespace gcode
#endif// GCODE_TEXTELEMENT_H
